/**
   Allumer LED de 0 à maximum et recommencer en boucle avec un bouton
*/
//declaration des PINS
const int LEDPIN = 3; //pin PWM obligatoire
const int boutPIN = 7;

//Déclaration de variables
int intensiteLED = 0; //intensité de la LED à tout moment
int plusMoins = 1; //Dans quel sens va le compteur intensiteLED
int boutonEnfonce = 0;//Initialiser pas enfoncé

void setup() {
  pinMode(LEDPIN, OUTPUT);//la LED est éteinte
  pinMode(boutPIN, INPUT);

  Serial.begin(9600); //Initialiser le port séri pour utiliser la console
  //9600 bauds (bits / sec) 9600 /10 (bits par charactere) = 960 char/sec

}

void loop() //comme un gros FOR(1 == 1)
{
  boutonEnfonce = digitalRead(boutPIN);
  if (boutonEnfonce == 1)
  {
    intensiteLED = intensiteLED + plusMoins;//
    if (intensiteLED >= 255)//borne supérieure: intensité maximale peermise par analogWrite()
    {
      plusMoins = -1;// INVERSER l'addition
    }
    if (intensiteLED <= 0)//borne inférieure
    {
      plusMoins = 1;
    }
    Serial.println(intensiteLED);//ATTENTION: ralentit l'exécution
    delay(5);//ATTENTION : Ralentit l'exécution
    analogWrite(LEDPIN, intensiteLED);//MAX 255
  } else
  {
    plusMoins = 1;//pour être ceertain de repartir en montant l'intensité
    intensiteLED = 0;//pour être certain que la LED est éteinte (voir définition analogWrite())
    analogWrite(LEDPIN, intensiteLED);//prendere habitude d'écrire 0

  }
}
