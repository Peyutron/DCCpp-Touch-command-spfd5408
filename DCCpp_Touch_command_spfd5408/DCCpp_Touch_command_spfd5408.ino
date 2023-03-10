/*
  For a capacitive touch screen.
  Creates a grid of numbeROJO    s, each of
  which will trap touches and report its id.
  Any of the four screen rotations may be used.
*/

//#include <SPI.h>
#include <Wire.h>
#include <SPFD5408_Adafruit_GFX.h>    // NUCLEO LIBRERIA GRAFICA
#include <SPFD5408_Adafruit_TFTLCD.h> // LIBRERIA DE HARDWARE ESPECIFICO
#include <SPFD5408_TouchScreen.h>     // LIBRERIA DEL TOUCHSCREEN
#include <SoftwareSerial.h>
// SoftwareSerial Serie2 (11,  12); //RX-TX


// CALIBRACION SENSIBILIDAD TOUCH
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//PINES DE CONFIGURACION DEL TOUCHSCREEN
#define YP A2
#define XM A1
#define YM 6
#define XP 7

short TS_MINX = 197;
short TS_MINY = 96;
short TS_MAXX = 948;
short TS_MAXY = 820;

// INICIA EL TOUCHSCREEN:

TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);

// VALORES POR DEFECTO PARA Adafruit shield v2.
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // OPCIONAL

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// ASIGNAMOS NOMBRES A ALGUNOS COLORES DE 16BITS
#define NEGRO     0x0000
#define AZUL      0x001F
#define ROJO      0xF800
#define VERDE     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define AMARILLO  0xFFE0
#define BLANCO    0xFFFF
#define GRIS      0x7530

uint16_t barColor;

const int row = 4;  // FILAS TECLADO
const int col = 3;  // COLUMNAS TECLADO
const int colDir  =  3; // COLUMNAS BOTONES DIRECCCION
const int rowLocAdd = 4;
const int colLocAdd = 3;
const int rowSelLoc = 4;
const int colSelLoc = 1;
String dire[4];


String  btnInfo[4] = {">0", ">0", ">0", ">0"};
String btnInfo1[4];
String btnInfo2[4];
static String btnTitle[col * row] = {"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", " *", "F0", "#"};
static String btnTitleDir[colDir] = {"<<", "STOP", " >>"};
static String btnTitleLocAdd[colLocAdd * rowLocAdd] = {"LOC1",  "0001", ">0", //LOC1 NumLOC >
                                                       "LOC2",  "0001", ">0",
                                                       "LOC3",  "0001", ">0",
                                                       "LOC4",  "0001", ">0"
                                                      };
int newPercent[4] = {0, 0, 0, 0};
int LastPercent[4] = {0, 0, 0, 0};
int touchPercent[4] = {0, 0, 0, 0};

int vel = 0;
long MillisBajada = 0;
long MillisSubida = 0;
int nVel = 0;

TSPoint p;

//#include "Arduino.h"
#include<EEPROM.h>
byte key;   // ALMACENA LA TECLA PULSADA

// Array set for 4 Loco2 - change the 7 numbers in the next 7 declarations
byte maxLocos = 4;                     // NUMERO MAXIMO DE LOCOMOTORAS
int LocoAddress[4] = {1, 2, 3, 4};    // DIRECCIONES DE LAS MAQUINA POR DEFECTO
byte LocoDireccion[4] = {1, 1, 1, 1};  // SENTIDO DE LA MARCHA 1-0
byte LocoSpeed[4] = {0, 0, 0, 0};      // VELOCIDAD DE LA MAQUINA
byte LocoOldSpeed[4] = {0, 0, 0, 0};   // VARIABLE DE VELOCIDAD
byte LocoFN0to4[4];                   // FUNCIONES FN0 A FN4
byte LocoFN5to8[4];                   // FUNCIONES FN5 A FN8
byte FN[4];                            // ALMACENA LAS FUNCIONES DURANTE EL USO


byte FNActive[12][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte funcion = 0 ;
byte FNLastActive [12][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


//byte Locofn9to12[4];                // FUNCIONES FB9 A FN12 NO IMPLEMENTADAS
int ActiveAddress = 0;                // SELECCIONA LA LOCOMOTORA ACTIVA AL INICIO (0-3)

boolean alimentacion = false;         // VARIABLE PARA EL CAMBIO DE ESTADO ENCENDIDO-APAGADO (APAGADO EN EL INICIO)
byte newAlimentacion = 0;              // BOTON ALIMENTACION
byte lastAlimentacion = 0;             // BOTON ALIMENTACION
boolean tecladoNumerico = false;      // TECLADO NUMERICO ENCENDIDO/APAGADO (APAGADO EN EL INICIO)

//// COMUNICACION ENTRE TOUCH COMMAND Y DCC++
#define  MAX_COMMAND_LENGTH         30
char commandString[MAX_COMMAND_LENGTH + 1];
String inString = "";   // STRING QUE ALMACENA LA ENTRADA DE DATOS
//String saveString = "";


//byte debug = 0; // PON UN 1 PARA VER LA INFORMACION DE DEPURACION EN EL PUERTO SERIAL (PUEDE CAUSAR PROBLEMAS CON LA CENTRAL DCC++
#define DEBUG
////////////////////SETUP////////////////////////////////////////////
void setup()
{

  Serial.begin(115200);   // VELOCIDAD DE TRANSMISION ENTRE DCC TOUCH COMMAND Y MONITOR SERIAL
 // Serie2.begin(115200);  // VELOCIDAD DE TRANSMISION ENTRE DCC TOUCH COMMAND Y DCC++

#ifdef DEBUG
  // Serial.println("");
#endif  
  Serial.print(F("<0>"));// APAGA LA UNIDAD DCC++
  delay(1500);
  getAddresses();  // LEE LA EEPROM
  tft.reset();
  tft.begin(0x9341);

  drawBorder();       // BORDE
  showHeader();       // CABECERA
  showPowerButton();  // BOTON DE ENCENDIDO
  showGrid(NEGRO);    // TECLADO
  lblVel(0, BLANCO);  // LABEL VELOCIDAD
  showButtonsDir();   // BOTONES DE DIRECCION
  showLblLocAdd();    // LABEL LOCOMOTORAS
  drawScale();        // DIBUJA LA ESCALA DE VELOCIDADES
}
////////////////////LOOP////////////////////////////////////////////
void loop()
{
  //char c;
  //pulsacion();
  //DetectButtons();
  if (alimentacion == true) BarraVelocidad();
  Recepcion();

/*  while (Serial.available() > 0)  // Si llega un dato por el puerto bluetooth se envía al monitor serial
  {
    int inChar = Serial.read();
    inString += (char)inChar;
    if (inChar == '>') {
      Serial.println ("datos Recibidos: " + inString);<
      inString = "";
    }
  } */
}

TSPoint waitOneTouch() {

  TSPoint p;

  do {
    p = ts.getPoint();

    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));

  return p;
}

uint16_t mapXValue(TSPoint p) {
  //Serial.println(p.x);
  //Serial.println(p.y);
  //uint16_t x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  uint16_t x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);

  //Correct offset of touch. Manual calibration
  //x+=1;

  return x;

}
// Mapeo coordenada  Y

uint16_t mapYValue(TSPoint p) {

  uint16_t y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  //Correct offset of touch. Manual calibration
  //y-=2;
  return y;
}
void pulsacion() {

  digitalWrite(13, HIGH);

  p = waitOneTouch();

  digitalWrite(13, LOW);
  p.x = mapXValue(p);
  p.y = mapYValue(p);
  /*if (debug == 1) {
    Serial.println(F("Coordenadas X Y"));
    Serial.print("Coordenada Y ");
    Serial.print(p.y);
    Serial.print(" Coordenada X ");
    Serial.println(p.x);
    }*/
}
