/**
   Allumer LED de 0 à maximum et recommencer en boucle
*/
//declaration des PINS
const int LEDPIN = 3; //pin PWM obligatoire
const int boutPIN = 7;

//Déclaration de variables
int intensiteLED = 0; //intensité de la LED à tout moment
int plusMoins = 1; //Dans quel sens va le compteur intensiteLED
int boutonEnfonce = 0;//Initialiser pas enfoncé

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(boutPIN, INPUT);

  Serial.begin(9600); //Initialiser le port séri pour utiliser la console
  //9600 bauds (bits / sec) 9600 /10 (bits par charactere) = 960 char/sec

}

void loop() //comme un gros FOR
{
  boutonEnfonce = digitalRead(boutPIN);
  if (boutonEnfonce == 1)
  {
    intensiteLED = intensiteLED + plusMoins;//
    if (intensiteLED >= 255)
    {
      plusMoins = -1;// INVERSER l'addition
    }
    if (intensiteLED <= 0)
    {
      plusMoins = 1;
    }
    //Serial.println(intensiteLED);//ATTENTION: ralentit l'exécution
    delay(5);//ATTENTION : Ralentit l'exécution
    analogWrite(LEDPIN, intensiteLED);//MAX 255
  } else
  {
    intensiteLED = 0;
    analogWrite(LEDPIN, intensiteLED);//prendere habitude d'écrire 0

  }
}
