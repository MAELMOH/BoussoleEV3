#include "LaunchMotorSpeed.c"; // Inclusion de la fonction pour contr�ler la vitesse du moteur

// Coefficients du contr�leur PID
float P = 3;          // Coefficient proportionnel
float I = 0.001;      // Coefficient int�gral
float D = -0.01;      // Coefficient d�riv�

int motorTarget;      // Consigne de position angulaire du moteur
bool targetReached = true; // �tat indiquant si la consigne est atteinte
float integralError = 0;   // Erreur cumul�e pour la composante int�grale
int errorHistory[10] = {0,0,0,0,0,0,0,0,0,0}; // Historique des erreurs pour la composante int�grale
int errorIndex = 0;   // Index circulaire pour g�rer l'historique des erreurs

TSemaphore semMutex;  // S�maphore pour g�rer l'acc�s aux variables partag�es

// D�claration des t�ches pour surveiller les boutons et g�rer l'interface utilisateur
task watchButtons();
task IHM();

// T�che principale de suivi de consigne pour le robot fixe avec un contr�leur PID
task keepHeadingPID() {
	motorTarget = getMotorEncoder(motorA); // Initialiser la consigne avec la position actuelle du moteur
	semaphoreInitialize(semMutex);         // Initialiser le s�maphore
	startTask(watchButtons);               // Lancer la t�che de surveillance des boutons
	startTask(IHM);                        // Lancer la t�che de l'interface utilisateur

	while (true) {
		int capActual = nMotorEncoder[motorA]; // R�cup�rer la position actuelle du moteur
		int error = motorTarget - capActual;    // Calculer l'erreur de position
		int vitesseAngulaire = getMotorSpeed(motorA); // Obtenir la vitesse angulaire du moteur

		// Mise � jour de l'erreur cumul�e pour la composante int�grale
		integralError -= errorHistory[errorIndex];  // Retirer l'ancienne erreur de la somme
		errorHistory[errorIndex] = error;           // Stocker la nouvelle erreur
		integralError += error;                     // Ajouter la nouvelle erreur � la somme

		errorIndex = (errorIndex + 1) % 10;         // Boucler sur les 10 derni�res erreurs

		// Calcul de la vitesse du moteur en fonction des coefficients PID
		float speed = P * error + I * integralError + D * vitesseAngulaire;

		// V�rifier si la consigne est atteinte
		if (abs(error) <= 1 && abs(vitesseAngulaire) < 2) {
			setMotorSpeed(motorA, 0);    // Arr�ter le moteur si la consigne est atteinte
			targetReached = true;        // Indiquer que la cible est atteinte
			} else {
			targetReached = false;       // Indiquer que la cible n'est pas atteinte
			launchMotorSpeed(speed);     // Lancer le moteur � la vitesse calcul�e
		}

		wait1Msec(50); // D�lai pour stabiliser le contr�le
	}
}

// T�che pour surveiller les boutons et ajuster la consigne du moteur
task watchButtons() {
	while (true) {
		// Bouton droit pour diminuer la consigne de 10�
		if (getButtonPress(buttonRight)) {
			semaphoreLock(semMutex);
			motorTarget -= 10;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonRight)) {}
		}

		// Bouton gauche pour augmenter la consigne de 10�
		if (getButtonPress(buttonLeft)) {
			semaphoreLock(semMutex);
			motorTarget += 10;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonLeft)) {}
		}

		// Bouton haut pour diminuer la consigne de 90�
		if (getButtonPress(buttonUp)) {
			semaphoreLock(semMutex);
			motorTarget -= 90;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonUp)) {}
		}

		// Bouton bas pour augmenter la consigne de 90�
		if (getButtonPress(buttonDown)) {
			semaphoreLock(semMutex);
			motorTarget += 90;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonDown)) {}
		}

		wait1Msec(50); // D�lai pour stabiliser les appuis sur les boutons
	}
}

// T�che de l'interface utilisateur pour afficher les informations de commande sur l'�cran
task IHM() {
	while (true) {
		eraseDisplay(); // Effacer l'�cran
		displayBigTextLine(3, "Robot Fixe");
		displayCenteredTextLine(5, "Bouton Droite: +10 deg");
		displayCenteredTextLine(6, "Bouton Gauche: -10 deg");
		displayCenteredTextLine(7, "Bouton Haut: +90 deg");
		displayCenteredTextLine(8, "Bouton Bas: -90 deg");
		displayTextLine(9, "Bouton Centre: Menu");
		displayTextLine(11, "Cible: %d", -motorTarget); // Afficher la consigne
		displayTextLine(12, "Position Moteur: %d", -nMotorEncoder[motorA]); // Afficher la position actuelle

		displayCenteredTextLine(14, "Quitter le programme");
		displayCenteredTextLine(15, "-> Bouton Rouge");

		wait1Msec(500); // D�lai pour rafra�chir l'affichage
	}
}
