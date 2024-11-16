#include "LaunchMotorSpeed2.c"; // Inclusion de la fonction pour contr�ler la vitesse en mode mobile

// Coefficients du contr�leur PID pour le mode mobile
float P2 = -3.5;         // Coefficient proportionnel
float I2 = -0.001;     // Coefficient int�gral
float D2 = 0.01;      // Coefficient d�riv�

int motorTarget2 ;  // Consigne de cap en degr�s
bool targetReached2 = true; // �tat indiquant si la consigne est atteinte
float integralError2 = 0;   // Erreur cumul�e pour la composante int�grale
int errorHistory2[10] = {0,0,0,0,0,0,0,0,0,0}; // Tableau pour stocker les 10 derni�res erreurs
int errorIndex2 = 0;   // Index circulaire pour g�rer l'historique des erreurs

TSemaphore semMutex2;  // S�maphore pour g�rer l'acc�s aux variables partag�es

// D�claration des t�ches pour surveiller les boutons et g�rer l'interface utilisateur en mode mobile
task watchButtons2();
task IHM2();

// T�che principale de suivi de cap pour le robot mobile avec un contr�leur PID
task keepHeadingPID2() {
	semaphoreInitialize(semMutex2);     // Initialiser le s�maphore
	startTask(watchButtons2);           // Lancer la t�che de surveillance des boutons
	startTask(IHM2);                    // Lancer la t�che de l'interface utilisateur
	motorTarget2 = getGyroDegrees(S2);  // Consigne de cap en degr�s

	while (true) {
		int capActual = getGyroDegrees(S2); // Obtenir le cap actuel en degr�s via le gyroscope

		int error2 = motorTarget2 - capActual; // Calculer l'erreur de cap

		int vitesseAngulaire = getGyroRate(S2); // Obtenir la vitesse angulaire du robot

		// Mise � jour de l'erreur cumul�e pour la composante int�grale
		integralError2 -= errorHistory2[errorIndex2];  // Retirer l'ancienne erreur de la somme
		errorHistory2[errorIndex2] = error2;           // Stocker la nouvelle erreur
		integralError2 += error2;                      // Ajouter la nouvelle erreur � la somme

		errorIndex2 = (errorIndex2 + 1) % 10;          // Boucler sur les 10 derni�res erreurs

		// Calcul de la vitesse en fonction des coefficients PID
		float speed = P2 * error2 + I2 * integralError2 + D2 * vitesseAngulaire;

		// V�rifier si la consigne est atteinte
		if (abs(error2) <= 1) {
			setMotorSpeed(motorA, 0);      // Arr�ter le moteur si la consigne est atteinte
			targetReached2 = true;         // Indiquer que la cible est atteinte
			} else {
			targetReached2 = false;        // Indiquer que la cible n'est pas atteinte
			launchMotorSpeed2(speed);      // Lancer le moteur � la vitesse calcul�e
		}

		displayTextLine(7, "Cap reel : %.2f", capActual); // Afficher le cap r�el sur l'�cran

		wait1Msec(50); // D�lai pour stabiliser le contr�le
	}
}

// T�che pour surveiller les boutons et arr�ter le programme si le bouton central est press�
task watchButtons2() {
	while (true) {

		// Bouton central pour arr�ter toutes les t�ches
		if (getButtonPress(buttonEnter)) {
			semaphoreLock(semMutex2);    // Verrouiller le s�maphore pour arr�ter en toute s�curit�
			stopAllTasks();              // Arr�ter toutes les t�ches
			semaphoreUnlock(semMutex2);  // D�verrouiller le s�maphore
			while (getButtonPress(buttonEnter)){} // Attendre que le bouton soit rel�ch�
		}

		wait1Msec(50); // D�lai pour stabiliser les appuis sur les boutons
	}
}

// T�che de l'interface utilisateur pour afficher les informations de commande en mode mobile
task IHM2() {
	while (true) {
		eraseDisplay(); // Effacer l'�cran
		displayBigTextLine(3, "Robot Mobile"); // Titre
		displayTextLine(6, "Consigne : %.2f", motorTarget2); // Afficher la consigne de cap

		displayTextLine(12, "Bouton Centre: Menu"); // Indiquer que le bouton central revient au menu


		displayCenteredTextLine(14, "Quitter le programme");
		displayCenteredTextLine(15, "-> Bouton Rouge");

		wait1Msec(500); // D�lai pour rafra�chir l'affichage
	}
}
