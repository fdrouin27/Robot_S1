/*
Projet: Projet de robot S-1
Equipe: P-08
Auteurs: Julien Lavoie, Guillaume Frenette
Description: Script général du robot, il contient toute les fonctions utilisées dans la loop()
Date: 2018-10-27
*/

/******************************************************************************
Inclure les librairies de functions que vous voulez utiliser
******************************************************************************/

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <math.h> // Librairie qui permet d'utiliser des fonctions mathématique
#include <ADJDS311.h> // Librairie pour utiliser le capteur de couleur
#include <string.h> // Librairie qui permet d'utiliser la variable string


/******************************************************************************
Variables globales et defines
******************************************************************************/
// L'ensemble des fonctions y ont accès
const float DIAMETRE_ROBOT = 18.7; // Distance d'une roue à l'autre GARDIENNNNNNNN
const float DIAMETRE_ROUE  = (7.7); //Diamètre d'une roue en cm
const int ENCOCHES_TOTALES = 3200;
const float DISTANCE_ENCOCHE = (DIAMETRE_ROUE * M_PI)/ENCOCHES_TOTALES;
const float speedTourner = 0.35;

// Variable pour le capteur de couleur
uint8_t ledPin = 39; // Numéro de la Pin dans laquelle il faut brancher le fil du capteur de couleur, si vous changer le fil de place, changer le numéro ici
ADJDS311 color(ledPin);

void Guardien()
{
       // string color = GetColor();
        loop();
}

// Enum qui contient une liste de couleur
enum Color 
{ 
    Red, 
    Green,
    Blue,
    Yellow,
    White
};

// Fonction qui vérifie les valeurs retourné par le capteur de couleur et la défini
void checkColor()
{
    // Instancie une variable de l'enum afin de pouvoir utiliser les valeurs de celles-ci
    Color enumColor;

    // Si la lecture de la couleur rouge par le capteur est plus grande que les autre alors la couleur est rouge
    if(color.readRed() > color.readGreen() && color.readRed() > color.readBlue() && color.readRed() > color.readClear())
    {
        enumColor = Red;
    }
    // Si la lecture de la couleur verte par le capteur est plus grande que les autre alors la couleur est verte
    else if(color.readGreen() > color.readRed() && color.readGreen() > color.readBlue() && color.readGreen() > color.readClear())
    {
        enumColor = Green;
    }
    // Si les valeurs de lecture du capteur sont au dessus de 1000 pour rouge, vert et transparent alors la couleur est jaune
    else if(color.readRed() > 1000 && color.readGreen() > 1000 && color.readClear() > 1000)
    {
        enumColor = Yellow;
    }
    // Si toutes les lecture de couleur du capteur sont au dessus de 1000 alors la couleur est blanche
    else if(color.readRed() > 1000 && color.readGreen() > 1000 && color.readBlue() > 1000 && color.readClear() > 900)
    {
        enumColor = White;
    }

    // Code à faire en fonction de la couleur détecter par le capteur
    switch(enumColor) 
    {
        case Red :
        {
            //
        } 
        break;  

        case Green :
        {
            //
        } 
        break;

        case Blue :
        {
            //
        } 
        break;

        case Yellow :
        {
            //
        } 
        break;

        case White :
        {
            //
        } 
        break;

        default :
        {
            // Fonction pour que le robot avance 
        }
        
    }
}

// Fonction qui permet de calibrer le capteur de couleur
void calibrateColorSensor()
{
    if(ROBUS_IsBumper(3))
    {
        Serial.println("Capteur en cours de calibration...");
        color.calibrate();
        delay(15000);
        Serial.print("Capteur calibré !");
    }
    
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


/*void loop()
{

    UnTrack();
    DeuxBumpers();
    MOTOR_SetSpeed(0,0.75);
    MOTOR_SetSpeed(1,0.75);
}*/

//Fonction qui va faire tourner le robot de bord si il recontre une couleur ou si son parechoc avant est activé.
void UnTrack(){
    /*string untrackcolor = GetColor();
    string newcolor;
    if (ROBUS_IsBumper(2) || color == "Yellow" || color == "Blue" || color == "Red" || color == "Green")
        {
            ReculeUTurn();
        }
    */
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

void setup()
{
    Serial.begin(9600);
    color.init();
    color.ledOn();
}

void loop(){
    
    /*if (ROBUS_IsBumper(2))
    {
        ReculeUTurn();
    }
   /* while (color == GetColor){
        //Insérer la fonction de ligne droite
        MOTOR_SetSpeed(0,0.5);
        MOTOR_SetSpeed(1,0.5);
    }*/
    /*ReculeUTurn();
    
    MOTOR_SetSpeed(0,0.5);
    MOTOR_SetSpeed(1,0.5); 
   /* if (color != GetColor)
    {
        loop();
        //Fonction que si il 
    }*/
    calibrateColorSensor();
    if(ROBUS_IsBumper(2))
    {
        Serial.print("R: "); Serial.print(color.readRed());Serial.print(", ");
        Serial.print("G: "); Serial.print(color.readGreen());Serial.print(", ");
        Serial.print("B: "); Serial.print(color.readBlue());Serial.print(", ");
        Serial.print("C: "); Serial.print(color.readClear());
        Serial.println();
  
        delay(500);
    }
}

