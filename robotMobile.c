#include "LaunchMotorSpeed2.c"; // Inclusion de la fonction pour contrôler la vitesse en mode mobile

// Coefficients du contrôleur PID pour le mode mobile
float P2 = -3.5;         // Coefficient proportionnel
float I2 = -0.001;     // Coefficient intégral
float D2 = 0.01;      // Coefficient dérivé

int motorTarget2 ;  // Consigne de cap en degrés
bool targetReached2 = true; // État indiquant si la consigne est atteinte
float integralError2 = 0;   // Erreur cumulée pour la composante intégrale
int errorHistory2[10] = {0,0,0,0,0,0,0,0,0,0}; // Tableau pour stocker les 10 dernières erreurs
int errorIndex2 = 0;   // Index circulaire pour gérer l'historique des erreurs

TSemaphore semMutex2;  // Sémaphore pour gérer l'accès aux variables partagées

// Déclaration des tâches pour surveiller les boutons et gérer l'interface utilisateur en mode mobile
task watchButtons2();
task IHM2();

// Tâche principale de suivi de cap pour le robot mobile avec un contrôleur PID
task keepHeadingPID2() {
	semaphoreInitialize(semMutex2);     // Initialiser le sémaphore
	startTask(watchButtons2);           // Lancer la tâche de surveillance des boutons
	startTask(IHM2);                    // Lancer la tâche de l'interface utilisateur
	motorTarget2 = getGyroDegrees(S2);  // Consigne de cap en degrés

	while (true) {
		int capActual = getGyroDegrees(S2); // Obtenir le cap actuel en degrés via le gyroscope

		int error2 = motorTarget2 - capActual; // Calculer l'erreur de cap

		int vitesseAngulaire = getGyroRate(S2); // Obtenir la vitesse angulaire du robot

		// Mise à jour de l'erreur cumulée pour la composante intégrale
		integralError2 -= errorHistory2[errorIndex2];  // Retirer l'ancienne erreur de la somme
		errorHistory2[errorIndex2] = error2;           // Stocker la nouvelle erreur
		integralError2 += error2;                      // Ajouter la nouvelle erreur à la somme

		errorIndex2 = (errorIndex2 + 1) % 10;          // Boucler sur les 10 dernières erreurs

		// Calcul de la vitesse en fonction des coefficients PID
		float speed = P2 * error2 + I2 * integralError2 + D2 * vitesseAngulaire;

		// Vérifier si la consigne est atteinte
		if (abs(error2) <= 1) {
			setMotorSpeed(motorA, 0);      // Arrêter le moteur si la consigne est atteinte
			targetReached2 = true;         // Indiquer que la cible est atteinte
			} else {
			targetReached2 = false;        // Indiquer que la cible n'est pas atteinte
			launchMotorSpeed2(speed);      // Lancer le moteur à la vitesse calculée
		}

		displayTextLine(7, "Cap reel : %.2f", capActual); // Afficher le cap réel sur l'écran

		wait1Msec(50); // Délai pour stabiliser le contrôle
	}
}

// Tâche pour surveiller les boutons et arrêter le programme si le bouton central est pressé
task watchButtons2() {
	while (true) {

		// Bouton central pour arrêter toutes les tâches
		if (getButtonPress(buttonEnter)) {
			semaphoreLock(semMutex2);    // Verrouiller le sémaphore pour arrêter en toute sécurité
			stopAllTasks();              // Arrêter toutes les tâches
			semaphoreUnlock(semMutex2);  // Déverrouiller le sémaphore
			while (getButtonPress(buttonEnter)){} // Attendre que le bouton soit relâché
		}

		wait1Msec(50); // Délai pour stabiliser les appuis sur les boutons
	}
}

// Tâche de l'interface utilisateur pour afficher les informations de commande en mode mobile
task IHM2() {
	while (true) {
		eraseDisplay(); // Effacer l'écran
		displayBigTextLine(3, "Robot Mobile"); // Titre
		displayTextLine(6, "Consigne : %.2f", motorTarget2); // Afficher la consigne de cap

		displayTextLine(12, "Bouton Centre: Menu"); // Indiquer que le bouton central revient au menu


		displayCenteredTextLine(14, "Quitter le programme");
		displayCenteredTextLine(15, "-> Bouton Rouge");

		wait1Msec(500); // Délai pour rafraîchir l'affichage
	}
}
