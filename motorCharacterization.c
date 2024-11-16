// Tableau pour stocker les vitesses mesur�es du moteur pour chaque niveau de puissance
float tabValeur[101];
// Variables pour suivre la puissance maximale et la vitesse maximale atteinte
float maxPowerI = 200; // Puissance maximale initialement �lev�e pour �tre mise � jour
float maxSpeedI = 0;   // Vitesse maximale enregistr�e
int minPowerI;         // Puissance minimale pour faire tourner le moteur

// Fonction de caract�risation du moteur en fonction de la puissance appliqu�e
void motorCharacterization()
{
	// Boucle pour tester toutes les puissances de 0 � 100
	for(int i = 0; i <= 100; i = i + 1){

		displayCenteredTextLine(6, "%d %%", i); // Afficher la puissance actuelle sur l'�cran

		setMotorSpeed(motorA, i); // Appliquer la puissance au moteur
		sleep(500); // Attendre un moment pour stabiliser la vitesse
		tabValeur[i] = getMotorRPM(motorA) * 6; // Enregistrer la vitesse en RPM, multipli�e par 6 pour l'�chelle en degr�s par seconde

		// Mise � jour de la puissance maximale effective si la vitesse mesur�e est plus basse que maxPowerI
		if(maxPowerI > tabValeur[i] && tabValeur[i] > 0){
			maxPowerI = tabValeur[i];
		}

		// Mise � jour de la vitesse maximale atteinte
		if(maxSpeedI < tabValeur[i]){
			maxSpeedI = tabValeur[i];
		}
	}

	// Boucle pour d�terminer la puissance minimale `minPowerI` � laquelle la vitesse maximale est atteinte
	for(int i = 0; i <= 100; i = i + 1){

		// Si la vitesse actuelle correspond � la vitesse maximale, enregistrer la puissance et sortir
		if(maxSpeedI == tabValeur[i]){
			minPowerI = i;
			return;
		}
	}

	// Afficher les r�sultats de la caract�risation sur l'�cran
	displayCenteredTextLine(9, "Max Power : %.2f", maxPowerI);
	displayCenteredTextLine(11, "Max Speed : %.2f", maxSpeedI);
	displayCenteredTextLine(12, "Min Power : %d", minPowerI);

	setMotorSpeed(motorA, 0); // Arr�ter le moteur apr�s la fin de la caract�risation
}
