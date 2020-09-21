/*
   Nom: Bouton LED Externe Potentiometre - Solution

   Fonctionnement général: Ce programme fait clignoter une LED externe lorsqu'on appuie
   sur un bouton. La vitesse du clignotement varie en fonction de de la position du potentiometre,
   c'est à dire en fonction de la résistance variable lue par la pin A0

   Ajouter les commentaires à chaque ligne

   Ajouter les instructions nécessaires pour que le programme affiche valeurDelay juste
   avant le IF du bouton

   2020-9-20 RT Version initiale 1.0
*/
// Déclaration des pins
const int LEDPIN = 2;// LED externe sur connecteur GROVE
const int boutonPIN = 7; // Bouton sur connecteur GROVE
const int potPIN = A0;// Potentiometre (résistance variable) sur une puin analogue

//Déclaration des variables
int boutonEnfonce = 0;// vaudra 0 ou 1 selon l'état du bouton
int valeurDelay = 0;// delais variable


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
  valeurDelay = analogRead(potPIN) / 10; // Indique la valeur du potentiometre divisé par 10
  // Valeur Delay variera donc de 0 à 102 car la valeur de potPIN variera de 0 à 1023

  if (valeurDelay < 20) // vérifie si la valeur lue sur le potentiometre est < 20
  {
    //valeurDelay ne peut aller plus bas que 20, sinon la LED clignote trop vite
    valeurDelay = 20;
  }

  Serial.println(valeurDelay);//Imprimer la valeur ajustée du potentiometre sur la console

  if (boutonEnfonce == 1) //Est-ce que le bouton est enfoncé
  {
    //Cette partie du programme sera exécutée en boucle tant que le bouton est enfoncé
    //Donc la LED va clignoter plus ou moins rapidement selon la valeur de valeurDelay
    //Il y a une limite inférieure pour la vitesse de clignotement sino ça va trop vite!
    delay(valeurDelay); // Attendre valeurDelay milli-secondes
    digitalWrite(LEDPIN, HIGH); // Allumer la LED en mettant la pin à HIGH (même chose que 1)
    delay(valeurDelay); // Attendre valeurDelay millis-secondes
    digitalWrite(LEDPIN, LOW); //Éteindre la LED en mettant la pin à LOW (0)
  } else
  {
    //Cette instruction sera exécutée en boucle lorsque le bouton n'est pas enfoncé
    //Donc la LED restera éteinte
    digitalWrite(LEDPIN, LOW); //Étiendre la LED en mettant la pin à LOW (0)
  }
}
