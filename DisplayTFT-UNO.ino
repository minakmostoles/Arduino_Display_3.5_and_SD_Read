// "TFT TEST UNO";         

#include <MCUFRIEND_kbv.h>

#include "Setting.h"
#include "ioSD.h"

MCUFRIEND_kbv tft;

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410

static uint8_t aspect = 1;
uint16_t version = MCUFRIEND_KBV_H_;

// work in line numbers.  Font height in ht
int16_t ht = 16, top = 3, line, lines = 15, scroll;

void setup() {
  uint16_t g_identifier;
  Serial.begin(SERIALBAUT);
  setupModular(); //Es una funcion especial del programa para facilitar la configuracion mediante el setting
  
// provide identification TFT controller to library 
   uint16_t ID = tft.readID(); // 
   //g_identifier = 0x9481;  // this if for the 3.5 inch display ILI9341 controller
   tft.begin(ID);
   aspect = 1;
   tft.setRotation(3);//"0.PORTRAIT", "1.LANDSCAPE", "2.PORTRAIT_REV", "3.LANDSCAPE_REV"  
}

void loop() {
  info ();
}

void info (){
    const char *colorname[] = { "BLUE", "GREEN", "RED", "GRAY" };
    uint16_t colormask[] = { BLUE, GREEN, RED, GRAY };
    tft.fillScreen(colormask[aspect]);
    int width = tft.width();
    int height = tft.height();
    tft.drawRect(0, 0, width, height, WHITE);             //Rectangulo blanco exterior
    tft.drawRect(10, 10, width - 20, height - 20, WHITE); //Rectangulo blanco a 31px del exterior tft.drawRect(32, 32, width - 64, height - 64, WHITE)
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor(20, 20);
    tft.print(F("LoveMakerIOT"));
    tft.setTextColor(WHITE);
    tft.setCursor(20, 40);
    tft.print(F("por Mario R."));
    tft.setTextColor(BLACK);
    tft.setCursor(20, 60);
    tft.print(F(VERSIONSKETCH));
    tft.setCursor(20, 80);
    tft.setTextColor(WHITE);    
    tft.print(F("Lectura SD :"));
    tft.setTextColor(BLACK);
    //tft.setCursor(20, 100);
    printListToString (20,100,leerTXTSD());
    if (++aspect > 3) aspect = 0;
    delay(5000);
  }

  void printListToString(int x, int y, String stringForPrint){
    char delimiter[] = "\n";
    int lenMaxString = 300;
    char stringInChar[lenMaxString];  
    stringForPrint.toCharArray(stringInChar, lenMaxString);
    char* ptr = strtok(stringInChar, delimiter);// initialize first part (string, delimiter)
    char lineString;
    while(ptr != NULL) {
        lineString += ptr;
        ptr = strtok(NULL, delimiter);
        tft.setCursor(x, y);
        tft.print(ptr);
        y += 20; 
    }
  }
