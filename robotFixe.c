#include "LaunchMotorSpeed.c"; // Inclusion de la fonction pour contrôler la vitesse du moteur

// Coefficients du contrôleur PID
float P = 3;          // Coefficient proportionnel
float I = 0.001;      // Coefficient intégral
float D = -0.01;      // Coefficient dérivé

int motorTarget;      // Consigne de position angulaire du moteur
bool targetReached = true; // État indiquant si la consigne est atteinte
float integralError = 0;   // Erreur cumulée pour la composante intégrale
int errorHistory[10] = {0,0,0,0,0,0,0,0,0,0}; // Historique des erreurs pour la composante intégrale
int errorIndex = 0;   // Index circulaire pour gérer l'historique des erreurs

TSemaphore semMutex;  // Sémaphore pour gérer l'accès aux variables partagées

// Déclaration des tâches pour surveiller les boutons et gérer l'interface utilisateur
task watchButtons();
task IHM();

// Tâche principale de suivi de consigne pour le robot fixe avec un contrôleur PID
task keepHeadingPID() {
	motorTarget = getMotorEncoder(motorA); // Initialiser la consigne avec la position actuelle du moteur
	semaphoreInitialize(semMutex);         // Initialiser le sémaphore
	startTask(watchButtons);               // Lancer la tâche de surveillance des boutons
	startTask(IHM);                        // Lancer la tâche de l'interface utilisateur

	while (true) {
		int capActual = nMotorEncoder[motorA]; // Récupérer la position actuelle du moteur
		int error = motorTarget - capActual;    // Calculer l'erreur de position
		int vitesseAngulaire = getMotorSpeed(motorA); // Obtenir la vitesse angulaire du moteur

		// Mise à jour de l'erreur cumulée pour la composante intégrale
		integralError -= errorHistory[errorIndex];  // Retirer l'ancienne erreur de la somme
		errorHistory[errorIndex] = error;           // Stocker la nouvelle erreur
		integralError += error;                     // Ajouter la nouvelle erreur à la somme

		errorIndex = (errorIndex + 1) % 10;         // Boucler sur les 10 dernières erreurs

		// Calcul de la vitesse du moteur en fonction des coefficients PID
		float speed = P * error + I * integralError + D * vitesseAngulaire;

		// Vérifier si la consigne est atteinte
		if (abs(error) <= 1 && abs(vitesseAngulaire) < 2) {
			setMotorSpeed(motorA, 0);    // Arrêter le moteur si la consigne est atteinte
			targetReached = true;        // Indiquer que la cible est atteinte
			} else {
			targetReached = false;       // Indiquer que la cible n'est pas atteinte
			launchMotorSpeed(speed);     // Lancer le moteur à la vitesse calculée
		}

		wait1Msec(50); // Délai pour stabiliser le contrôle
	}
}

// Tâche pour surveiller les boutons et ajuster la consigne du moteur
task watchButtons() {
	while (true) {
		// Bouton droit pour diminuer la consigne de 10°
		if (getButtonPress(buttonRight)) {
			semaphoreLock(semMutex);
			motorTarget -= 10;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonRight)) {}
		}

		// Bouton gauche pour augmenter la consigne de 10°
		if (getButtonPress(buttonLeft)) {
			semaphoreLock(semMutex);
			motorTarget += 10;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonLeft)) {}
		}

		// Bouton haut pour diminuer la consigne de 90°
		if (getButtonPress(buttonUp)) {
			semaphoreLock(semMutex);
			motorTarget -= 90;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonUp)) {}
		}

		// Bouton bas pour augmenter la consigne de 90°
		if (getButtonPress(buttonDown)) {
			semaphoreLock(semMutex);
			motorTarget += 90;
			targetReached = false;
			semaphoreUnlock(semMutex);
			while (getButtonPress(buttonDown)) {}
		}

		wait1Msec(50); // Délai pour stabiliser les appuis sur les boutons
	}
}

// Tâche de l'interface utilisateur pour afficher les informations de commande sur l'écran
task IHM() {
	while (true) {
		eraseDisplay(); // Effacer l'écran
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

		wait1Msec(500); // Délai pour rafraîchir l'affichage
	}
}
