/***********************************************************************************************************************************/
/*                                            Modulo de lectura/escritura en la SD                                                 */
/*                                                     Soporte SD V_v181012                                                       */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#ifndef ioSD_H
#define ioSD_H

/* The WeMos Micro SD Shield uses:
 * D5, D6, D7, D8, 3V3 and G
 *
 * The shield uses SPI bus pins:
 * 13 = CLK
 * 12 = MISO
 * 11 = MOSI
 * 10 = CS
 * 
  */

  #include <SPI.h>
  #include <SD.h>
  #define SUPPORT_EEPROM_ENABLE
  #include "Board.h"
  #include "Setting.h"

  #define FILENAME "datalog.txt"
  
  //ARDUINO UNO
  #if defined UNO_MCU
    #define CHIPSELET 10
  #endif
  #if defined WEMOS_MCU//ARDUINO WEMOS
    #define CHIPSELET D8 //Shield de wemos D1 Mini
  #endif
  #if defined OTHER_MCU//ARDUINO Diferente
    #error Not ADAPTED
  #endif
  
  bool setupSD();
  String leerTXTSD ();
  void grabarTXTSD (String dataString);
  bool infoSD();                          //Muestra la info de la tarjera
  void getListFile ();                    //Obtiene la lista de ficheros de la tarjeta


  #endif //__SoporteioSD_H
