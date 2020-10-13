/*
   on s'amuse avec le temps...
   Ce programme gère une lED (interne) qui clignote à interval régulier, et
   un bouton qui allume une LED (externe) et compte puis imprime les secondes

   2020-10-13 RT Nettoyage
*/
const int LEDInterne = 13;  //On utilise la LED Interne qui est sur la pin 13 pour les Arduino UNO
const int LEDPIN = 3;       //N'importe quelle pin. On écrit 0 et 1 seulement dans cette version
const int boutPIN = 7;      //N'importe quelle pin

//Déclaration des variables
int boutonEnfonce = 0;      //Vérifier si le bouton est enfoncé
int etatLED = 0;            //Abstraction pour l'état de la LED. Vaut 0 ou 1

unsigned long compteur = 0; //unsigned long parce que c'est des milli secondes
int etatLEDInterne = 0;     //abstraction: vaut 0 si éteint et 1 si allumée
unsigned long millisAvant = 0; //La milli seconde exacte où on calcule la seconde avant de l'imprimer
unsigned long LEDInterneMillisAvant = 0; //La milli seconde exacte quand on a allumé la LED la dernière fois
unsigned long boutonMillisAvant = 0; //La ms exacte quand on a enfoncé le bouton
unsigned long monDelais = 500; //attente entre les actions du bouton (peut varier)
unsigned long vitesseClignote = 250; //Vitesse (fréquence) du clignetoment de la LED Interne

void setup() {
  pinMode(LEDInterne, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(boutPIN, INPUT);

  Serial.begin(9600);//initialiser le port série pour utiliser la console

}

void loop() //20,000 itérations par seconde!
{
  //Nouvellel instruction: millis()
  compteur = millis();//On prend la valeur de millis() au début de la loop()

  //Cette partie du programme fait clignoter la LED interne
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage

  //On entre dans le IF seulement si compteur est un multiple de la vitesse de clignotement ET
  // seulement si on attend la prochaine milli-seconde pour de pas répéter allume-éteint
  if (compteur % vitesseClignote == 0 && compteur > LEDInterneMillisAvant)
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

  //Cette partie du programme gère le bouton
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage

  boutonEnfonce = digitalRead(boutPIN);
  //On entre dans le IF seulement si le bouton est enfoncé ET
  // qu'on a attendu le temps du monDelais pour laisser le temps à l'utilisateur
  // d'enlever son doigt du bouton (temps de réaction)
  if (boutonEnfonce == 1 && compteur - boutonMillisAvant > monDelais)
  {
    boutonMillisAvant = compteur; //Instant précis où le bouton est enfoncé
    if (etatLED == 0)//la LED est éteinte
    {
      digitalWrite(LEDPIN, HIGH);//Action: Allumer la LED
      etatLED = 1;//Abstraction: doit être juste après digitalWrite(), l'action
    } else
    {
      digitalWrite(LEDPIN, LOW);
      etatLED = 0;
    }
  }

  //Cette partie du programme compte les secondes
  // de façon tout à fait indépendante du reste du programme
  //Donc il s'agit d'un découplage

  //On entre dans le IF seulement lorsqu'une nouvelle seconde débute et on
  // s'assure qu'on attend à la prochaine milli-seconde.
  if (compteur % 1000 == 0  && compteur > millisAvant)
  {
    millisAvant = compteur;
    Serial.println(compteur / 1000);
  }
}
