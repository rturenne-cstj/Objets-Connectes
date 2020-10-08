/*
   on s'amuse avec le temps
*/
const int LEDInterne = 13;
const int LEDPIN = 3;
const int boutPIN = 7;

//Déclaration des variables
int boutonEnfonce = 0;
int etatLED = 0;

unsigned long compteur = 0;//unsigned long parce que c'est des milli secondes
int etatLEDInterne = 0;//abstarction: vaut 0 si éteint et 1 si allumée
unsigned long millisAvant = 0;
unsigned long boutonMillisAvant = 0;
unsigned long monDelais = 500;//attente entre les actions du bouton

void setup() {
  pinMode(LEDInterne, OUTPUT);

  Serial.begin(9600);//initialiser le port série pour utiliser la console

}

void loop() //20,000 itérations par seconde
{
  //Cette partie du programme fait clignoter la LED interne
  //Nouvellel instruction: millis()
  compteur = millis();

  if (compteur % 250 == 0 && compteur > millisAvant)
  {
    millisAvant = compteur;
    if (etatLEDInterne == 0)
    {
      digitalWrite(LEDInterne, HIGH);
      etatLEDInterne = 1;
    } else
    {
      digitalWrite(LEDInterne, LOW);
      etatLEDInterne = 0;
    }
  }

  //Cette partie du programme gère le bouton
  boutonEnfonce = digitalRead(boutPIN);
  if (boutonEnfonce == 1 && millis() - boutonMillisAvant > monDelais)
  {
    boutonMillisAvant = compteur;
    if (etatLED == 0)//la LED est déjà éteinte
    {
      digitalWrite(LEDPIN, HIGH);//Action
      etatLED = 1;//Abstraction//doit être juste après digitalWrite()
    } else
    {
      digitalWrite(LEDPIN, LOW);
      etatLED = 0;
    }
   // delay(500);
  }
}
