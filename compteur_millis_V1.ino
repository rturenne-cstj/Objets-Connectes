/*
   Utilisation des milli secondes

*/
//déclaration des variables
unsigned long compteur = 0;//unsigned long pout utiliser des nombres plus gros

void setup()
{

  Serial.begin(9600);
//ne pas oublier d'avoir la même chose dans la console
Serial.println("Début du programme compteur millis V1");
}

void loop()//20000 itérations par seconde
{
  //millis() retourne le nombre de milli-secondes depuis le début de l'exécution
  compteur = millis();//nouvelle instruction: millis()
  if (compteur % 1000 == 0)
  {
    Serial.println(compteur);
  }
}
