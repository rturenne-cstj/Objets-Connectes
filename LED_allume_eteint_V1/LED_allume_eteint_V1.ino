/*
   apuuyer sur le bouton pour allumer la LED et appuyer à nouveau pour éteindre ainsi de suite
*/
//Déclaration des pins
const int LEDPIN = 3;
const int boutPIN = 7;

//Déclaration des variables
int boutonEnfonce = 0;
int etatLED = 0;

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  pinMode(boutPIN, INPUT);

  Serial.begin(9600);

}

void loop()
{
  boutonEnfonce = digitalRead(boutPIN);
  if (boutonEnfonce == 1)
  {
    if (etatLED == 0)
    {
      digitalWrite(LEDPIN, HIGH);
      etatLED = 1;
    } else
    {
      digitalWrite(LEDPIN, LOW);
      etatLED = 0;
    }

  }

}
