// Fonction d'initialisation pour positionner manuellement le gyroscope avant de démarrer le mode fixe ou mobile
void initialize()
{
	// Affiche les instructions d'initialisation à l'utilisateur
	eraseDisplay(); // Effacer l'écran
	displayBigTextLine(3, "Initialize :"); // Titre
	displayTextLine(6, "Tourner a Gauche"); // Indication pour tourner à gauche
	displayCenteredTextLine(7, "-> Bouton Gauche"); // Indication pour tourner à droite
	displayTextLine(8, "Tourner a Droite"); // Indication pour tourner à gauche
	displayCenteredTextLine(9, "-> Bouton Droit"); // Indication pour tourner à droite
	displayCenteredTextLine(11, "Continuer-> Bouton Bas"); // Indication pour continuer
	displayCenteredTextLine(12, "Menu-> Bouton Centre"); // Indiquer que le bouton central revient au menu

	displayCenteredTextLine(14, "Quitter le programme");
	displayCenteredTextLine(15, "-> Bouton Rouge");

	int speed = 20; // Vitesse fixée à 20 pour les mouvements de positionnement

	// Boucle pour attendre que l'utilisateur appuie sur le bouton bas pour continuer
	while(getButtonPress(buttonDown) == 0) {
		setMotorSpeed(motorA, 0); // S'assurer que le moteur est arrêté au début

		// Si le bouton gauche est pressé, tourner le moteur à gauche
		if(getButtonPress(buttonLeft) == 1) {
			setMotorSpeed(motorA, speed); // Tourner à gauche
			while(getButtonPress(buttonLeft) == 1){} // Attendre que le bouton gauche soit relâché
		}
		// Si le bouton droit est pressé, tourner le moteur à droite
		else if(getButtonPress(buttonRight) == 1) {
			setMotorSpeed(motorA, -speed); // Tourner à droite
			while(getButtonPress(buttonRight) == 1){} // Attendre que le bouton droit soit relâché
		}
	}

	// Attendre que le bouton bas soit relâché pour éviter toute interruption involontaire
	while(getButtonPress(buttonDown) == 1){}

	// S'assurer que le moteur est à l'arrêt une fois l'initialisation terminée
	setMotorSpeed(motorA, 0);
}
