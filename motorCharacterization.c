// Tableau pour stocker les vitesses mesurées du moteur pour chaque niveau de puissance
float tabValeur[101];
// Variables pour suivre la puissance maximale et la vitesse maximale atteinte
float maxPowerI = 200; // Puissance maximale initialement élevée pour être mise à jour
float maxSpeedI = 0;   // Vitesse maximale enregistrée
int minPowerI;         // Puissance minimale pour faire tourner le moteur

// Fonction de caractérisation du moteur en fonction de la puissance appliquée
void motorCharacterization()
{
	// Boucle pour tester toutes les puissances de 0 à 100
	for(int i = 0; i <= 100; i = i + 1){

		displayCenteredTextLine(6, "%d %%", i); // Afficher la puissance actuelle sur l'écran

		setMotorSpeed(motorA, i); // Appliquer la puissance au moteur
		sleep(500); // Attendre un moment pour stabiliser la vitesse
		tabValeur[i] = getMotorRPM(motorA) * 6; // Enregistrer la vitesse en RPM, multipliée par 6 pour l'échelle en degrés par seconde

		// Mise à jour de la puissance maximale effective si la vitesse mesurée est plus basse que maxPowerI
		if(maxPowerI > tabValeur[i] && tabValeur[i] > 0){
			maxPowerI = tabValeur[i];
		}

		// Mise à jour de la vitesse maximale atteinte
		if(maxSpeedI < tabValeur[i]){
			maxSpeedI = tabValeur[i];
		}
	}

	// Boucle pour déterminer la puissance minimale `minPowerI` à laquelle la vitesse maximale est atteinte
	for(int i = 0; i <= 100; i = i + 1){

		// Si la vitesse actuelle correspond à la vitesse maximale, enregistrer la puissance et sortir
		if(maxSpeedI == tabValeur[i]){
			minPowerI = i;
			return;
		}
	}

	// Afficher les résultats de la caractérisation sur l'écran
	displayCenteredTextLine(9, "Max Power : %.2f", maxPowerI);
	displayCenteredTextLine(11, "Max Speed : %.2f", maxSpeedI);
	displayCenteredTextLine(12, "Min Power : %d", minPowerI);

	setMotorSpeed(motorA, 0); // Arrêter le moteur après la fin de la caractérisation
}
