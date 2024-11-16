// Tableau pour stocker les valeurs de vitesse du gyroscope pour chaque niveau de puissance
float tabGyro[101];
// Sensibilité minimale du gyroscope (initialisée à une valeur élevée pour être ajustée plus tard)
float sensibiliteGyro = 200;

// Fonction de caractérisation de la vitesse du gyroscope en fonction de la puissance appliquée au moteur
void gyroRateCharacterization(){

	int sens = 1; // Variable pour alterner le sens de rotation du moteur
	resetGyro(S2); // Réinitialiser le gyroscope pour assurer des mesures précises

	// Boucle de 0 à 100 pour tester toutes les puissances
	for(int i = 0; i <= 100; i = i + 1){

		setMotorSpeed(motorA, sens * i); // Appliquer la puissance actuelle au moteur dans le sens choisi
		delay(500); // Attendre un moment pour que le gyroscope stabilise sa mesure
		tabGyro[i] = getGyroRate(S2); // Stocker la vitesse mesurée par le gyroscope pour la puissance actuelle

		// Inverser le sens de rotation pour éviter l'enroulement du câble du gyroscope
		sens = -sens;
		setMotorSpeed(motorA, sens * i); // Appliquer la même puissance dans l'autre sens
		delay(500); // Attendre de nouveau pour stabiliser la mesure
		sens = -sens; // Revenir au sens d'origine pour la prochaine itération

		// Mise à jour de la sensibilité minimale du gyroscope si une vitesse plus basse est mesurée
		if(sensibiliteGyro > tabGyro[i] && tabGyro[i] > 0){
			sensibiliteGyro = tabGyro[i];
		}
	}

	setMotorSpeed(motorA, 0); // Arrêter le moteur après la fin de la boucle
}
