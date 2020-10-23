/*
   on s'amuse avec le temps...
   Ce programme gère une lED (interne) qui clignote à interval régulier, et
   un bouton qui allume une LED (externe) et compte puis imprime les secondes

   2020-10-13 RT Nettoyage
   2020-10-19 RT Exercices 1 et 3
*/
const int LEDInterne = 13;  //On utilise la LED Interne qui est sur la pin 13 pour les Arduino UNO
const int LEDPIN = 3;       //N'importe quelle pin. On écrit 0 et 1 seulement dans cette version
const int boutPIN = 7;      //N'importe quelle pin
const int potPIN = A0;      //Le potentiometre a bersoin d'une pin analogue

//Déclaration des variables
int boutonEnfonce = 0;      //Vérifier si le bouton est enfoncé
int boutonDejaEnfonce = 0;  //Indique qu'on a déjà enfoncé le bouton
int etatLEDExterne = 0;     //Abstraction pour l'état de la LED. Vaut 0 ou 1
int etatLEDInterne = 0;     //abstraction: vaut 0 si éteint et 1 si allumée
int valeurPot = 0;          //valeur lue de potentiometre
unsigned long compteur = 0; //unsigned long parce que c'est des milli secondes
unsigned long secondeMillisAvant = 0; //La milli seconde exacte où on calcule la seconde avant de l'imprimer
unsigned long LEDInterneMillisAvant = 0; //La milli seconde exacte quand on a allumé la LED la dernière fois
unsigned long boutonMillisAvant = 0; //La ms exacte quand on a enfoncé le bouton
const unsigned long monDelais = 50; //attente entre les actions du bouton (peut varier)
int vitesseClignote = 250; //Vitesse (fréquence) du clignetoment de la LED Interne

void setup() {
  pinMode(LEDInterne, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(boutPIN, INPUT);
  pinMode(potPIN, INPUT);

  Serial.begin(9600);//initialiser le port série pour utiliser la console

}

void loop() //20,000 itérations par seconde!
{
  //Nouvellel instruction: millis()
  compteur = millis();//On prend la valeur de millis() au début de la loop()

  //Cette partie du programme gère le bouton
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage

  boutonEnfonce = digitalRead(boutPIN);
  //On entre dans le IF seulement si le bouton est enfoncé ET
  // on fait seulement UNE itération après avoir enfoncé le bouton ET
  // qu'on a attendu le temps du monDelais pour laisser le temps à l'utilisateur
  // d'enlever son doigt du bouton (temps de réaction)

  if (boutonEnfonce == 1 && boutonDejaEnfonce == 0 && compteur - boutonMillisAvant > monDelais)
  {
    boutonDejaEnfonce = 1;
    boutonMillisAvant = compteur; //Instant précis où le bouton est enfoncé
    if (etatLEDExterne == 0)//la LED est éteinte
    {
      digitalWrite(LEDPIN, HIGH);//Action: Allumer la LED
      etatLEDExterne = 1;//Abstraction: doit être juste après digitalWrite(), l'action
    } else
    {
      digitalWrite(LEDPIN, LOW);
      etatLEDExterne = 0;
    }
  } //ATTENTION: ne pas utiliser ELSE avec IF multi-conditions
  if ( boutonEnfonce == 0) //s'assurer de remettre l'indicateur dès qu'on lâche le bouton
  {
    boutonDejaEnfonce = 0;
  }

  //Cette partie du programme fait clignoter la LED interne
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage
  valeurPot = analogRead(potPIN);// varie de 0 à 1023
  //Vitesse maximale de clignotement
  // 10 fois par secondes ==> 1000 / 10 = 100 ms
  //Vitesse minimale est une fois par seconde
  // ==> 1000 ms
  // DONC vitesseClignote doit varier de 100 à 1000
  //MAIS le potentiometre varie de 0 à 1023
  vitesseClignote = map(valeurPot, 0, 1023, 100, 1000);
  //Serial.println(vitesseClignote);
  //On entre dans le IF seulement si compteur est un multiple de la vitesse de clignotement ET
  // seulement si on attend la prochaine milli-seconde pour de pas répéter allume-éteint
  if (compteur - LEDInterneMillisAvant > vitesseClignote)
  {
    LEDInterneMillisAvant = compteur;//L'instant exactt où la LED s'est allumée (ou éteinte)
    if (etatLEDInterne == 0) //si la LED est éteinte, on l'allume
    {
      digitalWrite(LEDInterne, HIGH); //Action: Allumer la LED
      etatLEDInterne = 1; //Abstraction: toujours près de l'action
    } else //éteindre la LED si elle est allumée
    {
      digitalWrite(LEDInterne, LOW);
      etatLEDInterne = 0;
    }
  }



  //Cette partie du programme compte les secondes
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage

  //On entre dans le IF seulement lorsqu'une nouvelle seconde débute et on
  // s'assure qu'on attend à la prochaine milli-seconde.
  if (compteur % 1000 == 0  && compteur > secondeMillisAvant)
  {
    secondeMillisAvant = compteur;
    Serial.println(compteur / 1000);
  }
}
