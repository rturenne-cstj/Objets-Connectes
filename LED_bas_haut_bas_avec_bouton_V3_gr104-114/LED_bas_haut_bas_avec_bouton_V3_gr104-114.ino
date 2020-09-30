/**
   Allumer LED de 0 à maximum et recommencer en boucle
*/
//declaration des PINS
const int LEDPIN = 3; //pin PWM obligatoire
const int boutPIN = 7;

//Déclaration de variables
//int intensiteLED = 0; //intensité de la LED à tout moment
//int plusMoins = 1; //Dans quel sens va le compteur intensiteLED
int boutonEnfonce = 0;//Initialiser pas enfoncé
int etatLED = 0;//Dans quel état est la LED: allumée ou éteinte

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(boutPIN, INPUT);

  Serial.begin(9600); //Initialiser le port séri pour utiliser la console
  //9600 bauds (bits / sec) 9600 /10 (bits par charactere) = 960 char/sec

}

void loop() //comme un gros FOR
{
  boutonEnfonce = digitalRead(boutPIN);
  if (boutonEnfonce == 1)// ATTENTION au "bounce" et la logique
  {
    if (etatLED == 0) //si la LED est éteinte
    {
      digitalWrite(LEDPIN, HIGH);
      etatLED = 1;//indique que la LED est allumée
    } else
    {
      digitalWrite(LEDPIN, LOW);
      etatLED = 0;
    }
  }
}
