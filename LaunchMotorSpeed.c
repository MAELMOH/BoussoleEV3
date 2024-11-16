// Variables de configuration pour contr�ler la vitesse du moteur
float minPower = 2;      // Puissance minimale pour faire tourner le moteur
float maxPower = 89;     // Puissance maximale atteignable par le moteur
float maxSpeed = 846;    // Vitesse maximale en degr�s par seconde
float pente = maxSpeed / maxPower; // Pente pour calculer la puissance en fonction de la vitesse souhait�e

// Fonction pour lancer le moteur � une vitesse donn�e
void launchMotorSpeed(float speed) {
	// Limiter la vitesse pour qu'elle n'exc�de pas la vitesse maximale
	if (fabs(speed) > maxSpeed) {
		speed = (speed > 0) ? maxSpeed : -maxSpeed; // Si la vitesse est trop �lev�e, on la ram�ne � maxSpeed en pr�servant le signe
	}

	// Calcul de la puissance requise en fonction de la vitesse demand�e
	float power = speed / pente;

	// Si la puissance calcul�e est inf�rieure � la puissance minimale, on applique minPower pour �viter de sous-alimenter le moteur
	if (fabs(power) < minPower) {
		power = (power > 0) ? minPower : -minPower; // Appliquer minPower dans la direction appropri�e
	}

	// Si la vitesse souhait�e est non nulle, on applique la puissance calcul�e
	if (abs(speed) > 0) {
		setMotorSpeed(motorA, power); // Mettre le moteur � la puissance calcul�e
		} else {
		setMotorSpeed(motorA, 0); // Sinon, arr�ter le moteur si la vitesse demand�e est nulle
	}
}

float minPower = 1;
float maxPower = 89;
float maxSpeed = 941;
float pente = maxSpeed / maxPower;

void launchMotorSpeed(float speed){
	if(fabs(speed) > maxSpeed){
		speed = (speed > 0) ? maxSpeed : -maxSpeed;
	}

	float power = speed / pente;
	if (fabs(power) < minPower)
	{
		power = (power < 0) ? minPower : -minPower;
	}

	if (abs(speed) > 0)
	{
		setMotorSpeed(motorA, power);
	}else
	{
		setMotorSpeed(motorA,0);
	}
}













void launchMotorSpeed(float speed){
	if (fabs(speed) > maxSpeed)
	{
		speed = (speed > 0) ? maxSpeed : -maxSpeed;
	}

	float power = speed / pente;
	if (fabs(power) < minPower)
	{
		speed = (power < minPower) ? minPower : -minPower;
	}

	if (abs(speed) > 0)
	{
		setMotorSpeed(motorA, speed);
	}else
	{
		setMotorSpeed(motorA, 0);
	}
	
	
	
	
}