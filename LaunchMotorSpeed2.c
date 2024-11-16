// Variables de configuration pour le contrôle de la vitesse du moteur en mode mobile
float minPower2 = 1;     // Puissance minimale pour faire tourner le moteur
float maxPower2 = 45;    // Puissance maximale atteignable par le moteur
float maxSpeed2 = 492;   // Vitesse maximale en degrés par seconde

// Fonction pour lancer le moteur à une vitesse donnée en utilisant les paramètres spécifiques au mode mobile
void launchMotorSpeed2(float speed) {
	// Limiter la vitesse pour qu'elle n'excède pas la vitesse maximale définie
	if (fabs(speed) > maxSpeed2) {
		speed = (speed > 0) ? maxSpeed2 : -maxSpeed2; // Si la vitesse est trop élevée, on la ramène à maxSpeed2 en préservant le signe
	}

	// Calcul de la puissance requise pour atteindre la vitesse demandée
	float power2 = speed / pente;

	// Si la puissance calculée est inférieure à la puissance minimale, on applique minPower2 pour éviter de sous-alimenter le moteur
	if (fabs(power) < minPower2) {
		power2 = (power2 > 0) ? minPower2 : -minPower2; // Appliquer minPower2 dans la direction appropriée
	}

	// Si la vitesse souhaitée est non nulle, on applique la puissance calculée
	if (abs(speed) > 0){
		setMotorSpeed(motorA, power2); // Mettre le moteur à la puissance calculée
		} else {
		setMotorSpeed(motorA, 0); // Sinon, arrêter le moteur si la vitesse demandée est nulle
	}
}
