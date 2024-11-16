// Variables de configuration pour le contr�le de la vitesse du moteur en mode mobile
float minPower2 = 1;     // Puissance minimale pour faire tourner le moteur
float maxPower2 = 45;    // Puissance maximale atteignable par le moteur
float maxSpeed2 = 492;   // Vitesse maximale en degr�s par seconde

// Fonction pour lancer le moteur � une vitesse donn�e en utilisant les param�tres sp�cifiques au mode mobile
void launchMotorSpeed2(float speed) {
	// Limiter la vitesse pour qu'elle n'exc�de pas la vitesse maximale d�finie
	if (fabs(speed) > maxSpeed2) {
		speed = (speed > 0) ? maxSpeed2 : -maxSpeed2; // Si la vitesse est trop �lev�e, on la ram�ne � maxSpeed2 en pr�servant le signe
	}

	// Calcul de la puissance requise pour atteindre la vitesse demand�e
	float power2 = speed / pente;

	// Si la puissance calcul�e est inf�rieure � la puissance minimale, on applique minPower2 pour �viter de sous-alimenter le moteur
	if (fabs(power) < minPower2) {
		power2 = (power2 > 0) ? minPower2 : -minPower2; // Appliquer minPower2 dans la direction appropri�e
	}

	// Si la vitesse souhait�e est non nulle, on applique la puissance calcul�e
	if (abs(speed) > 0){
		setMotorSpeed(motorA, power2); // Mettre le moteur � la puissance calcul�e
		} else {
		setMotorSpeed(motorA, 0); // Sinon, arr�ter le moteur si la vitesse demand�e est nulle
	}
}
