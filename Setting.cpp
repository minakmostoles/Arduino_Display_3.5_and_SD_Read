/***********************************************************************************************************************************/
/*                                         FUNCIONES A USAR POR TODOS LAS LIBRERIAS                                                */
/*                                                      v181012                                                                    */
/***********************************************************************************************************************************/

#include "Setting.h"              //Activacion de los diferentes funciones
#if defined WEMOS_MCU //Con WEMOS
  #include <ESP8266WiFi.h>          //Libreria necesaria para el ESP8266
#endif
#if defined UNO_MCU
  #include <Arduino.h>
#endif

#ifdef SUPPORT_EEPROM_ENABLE
  #include "ioEEPROM.h"
#endif

#ifdef SUPPORT_WIFI
  #include "ioWIFI.h"
#endif

#ifdef SUPPORT_MQTT
  #include "ioMQTT.h"
#endif //FIN

#ifdef SUPPORT_SD_ENABLE
  #include "ioSD.h"
#endif //FIN

/**********************************************************************/
/*                          SETUP MODULAR                             */
/*   Esta funcion realiza la llamada a la configuraciones elegidas    */
/**********************************************************************/
void setupModular(){
  mostrarTituloSerial(F(NOMBRESKETCH));
  #ifdef SUPPORT_EEPROM_ENABLE
    mostrarTituloSerial(F("SUPPORT_EEPROM ENABLE"));
    //Serial.println("SUPPORT_EEPROM ENABLE");
    //setupEEPROM();                  //Configura la EEPROM
  #endif

  #ifdef SUPPORT_WIFI
    mostrarTituloSerial(F("SUPPORT_WIFI ENABLE"));
    //Serial.println("WIFI ENABLE");
    inicioWifi();                     //Configuracion ModoWifi
  #endif
  
  #if defined(SUPPORT_WIFI) && defined(SUPPORT_MQTT) //Solo si esta activado el wifi y la opcion MQTT
    Serial.println(F("SUPPORT_MQTT ENABLE"));
    conectarMQTT();
    //publicame();
  #endif
  
  #if defined(SUPPORT_SD_ENABLE)
    mostrarTituloSerial(F("SUPPORT_SD_ENABLE"));
    setupSD();
  #endif
  
}



/**********************************************************************/
/*                             RESET                                  */
/*          Realizamo un reset por software del dispositivo           */
/**********************************************************************/
#if defined WEMOS_MCU //Con WEMOS
  extern void kernelPanic(){        
      ESP.restart(); 
      //ESP.reset();
  }
#endif
/**********************************************************************/
/*                     Programador de evento                          */
/*             Programamos eventos en un tiempo determinado           */
/**********************************************************************/
bool eventoCADAxSEG (int seg, bool flagEVENTO){
 
  long segRUN = (millis()/1000); //Convierto el tiempo en segundos
  
  if((segRUN%seg == 0) and (flagEVENTO == 0)){//Si los que lleva arrancado el sistema es modulo es multiplo de seg ejecuto el evento
    flagEVENTO = 1;
  }
  
  if((segRUN%seg != 0) and (flagEVENTO == 1)){
    flagEVENTO = 0;
  }
  
  return flagEVENTO;
}  //FIN FUNCION
/**********************************************************************/
/*                     Generador de titulos                           */
/*           Funcion para mostra un titulo por puerto serie           */
/**********************************************************************/
//#if defined WEMOS_MCU && defined(UNO_MCU)//Con WEMOS
bool mostrarTituloSerial(String titulo){
    String marco = "";
    for (uint8_t x=0 ; x < (titulo.length()+2); x++){marco= marco + "-";}
    Serial.println(" ");
    Serial.println("#" + marco + "#");
    Serial.println("# " + titulo + " #");
    Serial.println("#" + marco + "#");
    Serial.println(" ");
    return true;
}
//#endif

/**********************************************************************/
/*                              freeRam                               */
/*           Develve la cantidad de Memoria RAM Libre                 */
/**********************************************************************/
int freeRam (){
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

