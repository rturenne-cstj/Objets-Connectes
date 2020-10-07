/*
   Utilisation des milli secondes

*/
//déclaration des variables
unsigned long compteur = 0;//unsigned long pout utiliser des nombres plus gros

void setup()
{

  Serial.begin(9600);

}

void loop()//20000 itérations par seconde
{
  compteur ++;
  if (compteur % 100000 == 0) {
    Serial.println(compteur);
  }
}
