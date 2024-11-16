// Tableau pour stocker les valeurs de vitesse du gyroscope pour chaque niveau de puissance
float tabGyro[101];
// Sensibilit� minimale du gyroscope (initialis�e � une valeur �lev�e pour �tre ajust�e plus tard)
float sensibiliteGyro = 200;

// Fonction de caract�risation de la vitesse du gyroscope en fonction de la puissance appliqu�e au moteur
void gyroRateCharacterization(){

	int sens = 1; // Variable pour alterner le sens de rotation du moteur
	resetGyro(S2); // R�initialiser le gyroscope pour assurer des mesures pr�cises

	// Boucle de 0 � 100 pour tester toutes les puissances
	for(int i = 0; i <= 100; i = i + 1){

		setMotorSpeed(motorA, sens * i); // Appliquer la puissance actuelle au moteur dans le sens choisi
		delay(500); // Attendre un moment pour que le gyroscope stabilise sa mesure
		tabGyro[i] = getGyroRate(S2); // Stocker la vitesse mesur�e par le gyroscope pour la puissance actuelle

		// Inverser le sens de rotation pour �viter l'enroulement du c�ble du gyroscope
		sens = -sens;
		setMotorSpeed(motorA, sens * i); // Appliquer la m�me puissance dans l'autre sens
		delay(500); // Attendre de nouveau pour stabiliser la mesure
		sens = -sens; // Revenir au sens d'origine pour la prochaine it�ration

		// Mise � jour de la sensibilit� minimale du gyroscope si une vitesse plus basse est mesur�e
		if(sensibiliteGyro > tabGyro[i] && tabGyro[i] > 0){
			sensibiliteGyro = tabGyro[i];
		}
	}

	setMotorSpeed(motorA, 0); // Arr�ter le moteur apr�s la fin de la boucle
}
