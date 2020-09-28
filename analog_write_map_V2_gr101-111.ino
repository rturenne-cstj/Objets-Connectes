/*
   Nom: Bouton LED Externe Potentiometre et analogWrite


   ***************************


   2020-9-22 RT Version initiale V1.0
*/
// Déclaration des pins
const int LEDPIN = 3;// LED externe sur connecteur GROVE
//PWM disponible sur les pins 3,5,6,9,10 et 11
const int boutonPIN = 7; // Bouton sur connecteur GROVE
const int potPIN = A0;// Potentiometre (résistance variable) sur une pin analogue

//Déclaration des variables
int boutonEnfonce = 0;// vaudra 0 ou 1 selon l'état du bouton
int valeurLED = 0;// valeur de la luminosité


// Cette section est exécutée une seule fois au début du programme
void setup()
{
  pinMode(LEDPIN, OUTPUT); // Pin de la LED initialisée en OUTPUT car on désire y écrire
  pinMode(boutonPIN, INPUT); // Pin pour lire la valeur du bouton donc en INPUT
  pinMode(potPIN, INPUT); // Pin pour lire la valeur de la résistance

  Serial.begin(9600); //Initialiser le port série pour utiliser la console
  // 9600 représente la vitesse de communication avec la console par défaut
}

// Cette section est exécutée en boucle, à l'infini
void loop()
{
  // Faire la lecture des pins en input
  boutonEnfonce = digitalRead(boutonPIN); // Indique si le bouton est enfoncé
  // boutonEnfonce vaudra 1 si on appui sur le bouton, et 0 autrement
  valeurLED = analogRead(potPIN) ; // Indique la valeur du potentiometre


  Serial.println(valeurLED);//Imprimer la valeur ajustée du potentiometre sur la console

  if (boutonEnfonce == 1) //Est-ce que le bouton est enfoncé
  {
    //Cette partie du programme sera exécutée en boucle tant que le bouton est enfoncé

    //Nouvelle instruction: analogWrite()
    //valeurLED représente la valeur pour le Duty Cycle de la pin PWM
    //TOUJOURS se souvenir que la valeur maximum à écrire sur une pin est 255
    //Nouvelle instruction: map()
    //map() transforme  un nombre dans un autre selon les parametres
    analogWrite(LEDPIN, map(valeurLED, 0 , 750, 255 , 0));

  } else
  {
    //Cette instruction sera exécutée en boucle lorsque le bouton n'est pas enfoncé
    //Donc la LED restera éteinte
    digitalWrite(LEDPIN, LOW); //Étiendre la LED en mettant la pin à LOW (0)
  }
}
