// Fonction d'initialisation pour positionner manuellement le gyroscope avant de d�marrer le mode fixe ou mobile
void initialize()
{
	// Affiche les instructions d'initialisation � l'utilisateur
	eraseDisplay(); // Effacer l'�cran
	displayBigTextLine(3, "Initialize :"); // Titre
	displayTextLine(6, "Tourner a Gauche"); // Indication pour tourner � gauche
	displayCenteredTextLine(7, "-> Bouton Gauche"); // Indication pour tourner � droite
	displayTextLine(8, "Tourner a Droite"); // Indication pour tourner � gauche
	displayCenteredTextLine(9, "-> Bouton Droit"); // Indication pour tourner � droite
	displayCenteredTextLine(11, "Continuer-> Bouton Bas"); // Indication pour continuer
	displayCenteredTextLine(12, "Menu-> Bouton Centre"); // Indiquer que le bouton central revient au menu

	displayCenteredTextLine(14, "Quitter le programme");
	displayCenteredTextLine(15, "-> Bouton Rouge");

	int speed = 20; // Vitesse fix�e � 20 pour les mouvements de positionnement

	// Boucle pour attendre que l'utilisateur appuie sur le bouton bas pour continuer
	while(getButtonPress(buttonDown) == 0) {
		setMotorSpeed(motorA, 0); // S'assurer que le moteur est arr�t� au d�but

		// Si le bouton gauche est press�, tourner le moteur � gauche
		if(getButtonPress(buttonLeft) == 1) {
			setMotorSpeed(motorA, speed); // Tourner � gauche
			while(getButtonPress(buttonLeft) == 1){} // Attendre que le bouton gauche soit rel�ch�
		}
		// Si le bouton droit est press�, tourner le moteur � droite
		else if(getButtonPress(buttonRight) == 1) {
			setMotorSpeed(motorA, -speed); // Tourner � droite
			while(getButtonPress(buttonRight) == 1){} // Attendre que le bouton droit soit rel�ch�
		}
	}

	// Attendre que le bouton bas soit rel�ch� pour �viter toute interruption involontaire
	while(getButtonPress(buttonDown) == 1){}

	// S'assurer que le moteur est � l'arr�t une fois l'initialisation termin�e
	setMotorSpeed(motorA, 0);
}
