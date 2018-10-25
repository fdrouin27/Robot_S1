/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/******************************************************************************
Inclure les librairies de functions que vous voulez utiliser
******************************************************************************/

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <math.h>
#include <ADJDS311.h>


/******************************************************************************
Variables globales et defines
******************************************************************************/
// -> defines...
// L'ensemble des fonctions y ont accès
const float DIAMETRE_ROBOT = 18.7; // Distance d'une roue à l'autre GARDIENNNNNNNN
const float DIAMETRE_ROUE  = (7.7); //Diamètre d'une roue en cm
const int ENCOCHES_TOTALES = 3200;
const float DISTANCE_ENCOCHE = (DIAMETRE_ROUE * M_PI)/ENCOCHES_TOTALES;
const float speedTourner = 0.35;


void setup()
{
  //
}

void ReculeUTurn();
void UnTrack();
void DeuxBumpers();
void Tourner(float theta, float speed0, float speed1);
void UTurn();



void loop()
{
    if (ROBUS_IsBumper(3))
    {
        MOTOR_SetSpeed(0,0.75);
        MOTOR_SetSpeed(1,0.75);
    }

    UnTrack();
    DeuxBumpers();


}
void ReculeUTurn(){
    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0);    
    delay(100);
    MOTOR_SetSpeed(0,-0.25);
    MOTOR_SetSpeed(1,-0.25);
    delay(1000);
    MOTOR_SetSpeed(0,0);
    MOTOR_SetSpeed(1,0);
    delay(100);
    UTurn();
}
//Fonction qui va faire tourner le robot de bord si il recontre une couleur ou si son parechoc avant est activé.
void UnTrack(){
    /*string untrackcolor = GetColor();
    string newcolor;*/
    if (ROBUS_IsBumper(2) /*|| color == "Yellow" || color == "Blue" || color == "Red" || color == "Green"*/)
        {
            ReculeUTurn();
        }
    
}



void DeuxBumpers()
{
    float speed0;
    float speed1;
    // Arrêter le robot en premier
    MOTOR_SetSpeed (0,0);
    MOTOR_SetSpeed (1,0);
    delay(100);
    //Toutes les combinaisons de bumpers
    if (ROBUS_IsBumper(2) && ROBUS_IsBumper(0))
    {
        MOTOR_SetSpeed (0,0);
        MOTOR_SetSpeed (1,0);
        delay(100);
        speed0 = -speedTourner;
        speed1 = 0;
    }
    if (ROBUS_IsBumper(2) && ROBUS_IsBumper(1))
    {
        MOTOR_SetSpeed (0,0);
        MOTOR_SetSpeed (1,0);
        delay(100);
        speed0 = 0;
        speed1 = -speedTourner;
    }
    if (ROBUS_IsBumper(3) && ROBUS_IsBumper(0))
    {
        MOTOR_SetSpeed (0,0);
        MOTOR_SetSpeed (1,0);
        delay(100);
        speed0 = speedTourner;
        speed1 = 0;
    }
    if (ROBUS_IsBumper(3) && ROBUS_IsBumper(1))
    {
        MOTOR_SetSpeed (0,0);
        MOTOR_SetSpeed (1,0);
        delay(100);
        speed0 = 0;
        speed1 = speedTourner;
    }
    Tourner(90, speed0, speed1);
}



void Tourner(float theta, float speed0, float speed1)
{
    //Tourner en avançant/reculant une roue ou l'autre selon le cas
    float encoches_max = theta * M_PI * DIAMETRE_ROBOT / (180*2*DISTANCE_ENCOCHE);
    int coches; 
    for (;coches < encoches_max;)
    {
        coches = ENCODER_Read(0);
        MOTOR_SetSpeed (0,speed0);
        MOTOR_SetSpeed (1,speed1);
        delay(100);
    }
    MOTOR_SetSpeed (0,0);
    MOTOR_SetSpeed (1,0);
    delay(100);
}


void UTurn()
{
  int encochesToDo = (M_PI * 39.15 * 88.5 / 360) / DISTANCE_ENCOCHE;
  while(encochesToDo > 0)
  {
    ENCODER_Reset(0);
    ENCODER_Reset(1);
    MOTOR_SetSpeed(0, speedTourner);
    MOTOR_SetSpeed(1, -speedTourner);
    delay(100);
    float distTemp = ENCODER_Read(0);
    encochesToDo = encochesToDo - distTemp;
  }
  // Arrêter les moteurs pour ne pas qu'il continue à tourner
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}


