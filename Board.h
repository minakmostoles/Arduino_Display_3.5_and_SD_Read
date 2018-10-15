/***********************************************************************************************************************************/
/*                                     PARA ADAPTAR MIS FUNCIONES A LAS PLACAS USADAS                                              */
/*                                                      v181012                                                                    */
/***********************************************************************************************************************************/

#ifndef Board_H
#define Board_H
  //#warning Board 
  #ifdef defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) //Arduino MEGA
    #define MEGA_MCU
    #warning MEGA_MCU
  #elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega88__) //Arduino UNO
    #define UNO_MCU
    #warning UNO_MCU
  #elif defined(ESP8266)  // DISPOSITIVO BASADO EN ESP 8266 WEMOS D1
  /*****PINES DEL DISPOSITIVO ES WEMOS D1***/
  /* PINES SONOFF PIN12 RELE PLACA
   *              PIN13 LED PLACA
   *              PIN14 SALIDA/ENTRADA EN PINES*/
  /*****DEFINICION DE PUERTOS WEMOS MINI D3(NO ES NECESARIO DEFIRLOS TODOS)*****/
  //#define D0 16
  //#define D1 5 // I2C Bus SCL (clock)
  //#define D2 4 // I2C Bus SDA (data)
  //#define D3 0
  //#define D4 2 // LED_BUILTIN, led interno azul con lÃ³gica invertida.
  //#define D5 14 // SPI Bus SCK (clock)
  //#define D6 12 // SPI Bus MISO
  //#define D7 13 // SPI Bus MOSI
  //#define D8 15 // SPI Bus SS (CS)
  //#define D9 3 // RX0 (Serial console)
  //#define D10 1 // TX0 (Serial console)
  
    #define WEMOS_MCU
    #warning WEMOS_MCU
  #else
    #define OTHER_MCU
    #warning OTHER_MCU
  #endif

#endif //__SoporteioSD_H
