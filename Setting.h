/***********************************************************************************************************************************/
/*                                        CONFIGURACION GENERAL DEL PROYECTO                                                       */
/*                                             Setting V_v181012                                                           */
/***********************************************************************************************************************************/

#ifndef Setting_H
#define Setting_H

#include "Board.h"
#if defined WEMOS_MCU //Con WEMOS
  #include <ESP8266WiFi.h>          //Libreria necesaria para el ESP8266
#endif
#if defined UNO_MCU
  #include <Arduino.h>
#endif

/*********CONSTANTES DEL PROYECTO********/

#define NOMBRESKETCH "TFT TEST UNO"            //Indica el proyecto
#define VERSIONSKETCH "V:180923_0.01"       //Indica la version del sketch



/******CONFIGURACION PUERTO SERIAL******/
#define SERIAL_ENABLE                          // HABILITAR PUERTO SERIE *ACTUALMENTE DESABILITARLO DARIA PROBLEMAS

#ifdef SERIAL_ENABLE                           // ¿Puerto serie habilitado?
  #define SERIALBAUT 9600                         // 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
#endif

/******MODOS DE DEBUG******/
#define MODE_DEBUG                             // HABILITAR MODO DEBUG INFORMACION BASICA
#define MODE_DEBUG_FES                         // HABILITAR EL MODO DEBUG FUNCIONALIDADES MUY ESPECIALES
//#define MODE_DEBUG_TOOLS_FES                 // HABILITA LAS HERRAMIENTAS ESPECIFICAS DE DEBUG
//#define MODE_DEBUG_SEC                       // HABILITAR EL MODO DEBUG EN FUNCIONES MUY CICLICAS QUE PROVOCAN UNA GRAN CANTIDAD DE LINEAS SOBRE TERMINAL POR EJEMPLO BUFFER PANTALLA

/******HERRAMIENTAS PARA ANALISIS DE SISTEMAS******/
//#define TOOLS-I2C_ENABLE                     // HABILITA EL ESCANEO DE PUERTOS I2C (inestable)

/******FUNCIONES CONEXION Y INTERNET******/
//#define SUPPORT_WIFI                           //  ACTIVAMOS WIFI
//#define SUPPORT_UPDATE_OTA                     //  HABILITA LA UPDATE OTA (***NO ESTA PROBADO***)
//#define NEEDCONECTION                        //  SI SE NECESITA IMPRESCINDIBLEMENTE CONEXION USAR ESTA OPCION, SI NO CONECTA ENTRA EN MODO CONFIGURACION AUTOMATICAMENTE

//#define SUPPORT_MQTT                           //  ACTIVAMOS EL SOPORTE PARA MQTT ES OBLIGATORIO TENER SUPORT_WIFI ACTIVADO (SU FUNCIONAMIENTO ESTA DENTRO DE SUPPORT WIFI)
//const String clientId ="TestWemos";
//#define SUBSCRIBE_MQTT                         //  ACTIVAMOS LAS SUBCRIPCIONES
//const String subcripcionTOPIC = "#";           //  TEMA AL QUE NOS SUBCRIBIMOS

//#define TIME_WEATHER                           //  ACTIVAMOS FUNCION PARA OPTENER EL HORA FECHA Y TIEMPO DE LA ZONA DADA

//#define SUPPORT_EEPROM_ENABLE                  // HABILITAR LA EEPROM GRABAR Y LEER UNA POSICION DE MEMORIA (SE USA PARA MODULO COMUNICACION WIFI)
#define SUPPORT_SD_ENABLE                      // HABILITAR LA SD

/******FUNCIONES DE DISPOSITIVOS DISPLAYS******/
//#define  DISPLAY_OLED_ENABLE                   // HABILITAR DISPLAY OLED SHIELD 0.66" inch 64X48 IIC I2C Oled shield (TEST WEMOS)
//#define  DISPLAY_MATRIZ_LED                    // HABILITAR DISPLAY MATRIZ LED                                       (TEST ARDUINO UNO, WEMOS)
//#define  DISPLAY_LCD3.5TFT                     // HABILITAR DISPLAY LCD 3.5                                          (TEST ARDUINO UNO)

/******FUNCIONES DE SENSORES******/
//#define  SENSOR_HUMD-TEMP_ENABLE               // HABILITAR SENSOR TEMP & HUMEDAD

/******RUTINA DE RESET DEL SISTEMA******/
void setupModular();                             // CONFIGURAMOS EL SISTEMA COMO HEMOS DECLARADO ARRIBA

#if defined WEMOS_MCU //Con WEMOS
  extern void kernelPanic();                     // PROVOCAMOS EL RESET DEL SISTEMA POR SOFTWARE (SOLO WEMOS)
#endif

bool eventoCADAxSEG (int , bool);                // SIRVE PARA PROGRAMAR EVENTOS NO CRITICOS EJECUTADOS POR TIEMPO MAXIMO 49,71 dias DEVUELVE UN FLAG QUE ES EL RESPONSABLE DE EJECUTAR O NO LAS TAREAS
//#if defined WEMOS_MCU && defined(UNO_MCU) //Con WEMOS
  bool mostrarTituloSerial(String titulo);       // SIRVE PARA IMPRIMIR POR PUERTO SERIE UN TITULO Y REALIZAR UNA SEPARCION EN LO QUE SE MUESTRA
//#endif
#if defined MODE_DEBUG_TOOLS_FES
  int freeRam ();                              // DEVUELVE LA CANTIDAD DE MEMORIA RAM LIBRE EN UN MOMENTO
#endif
#endif //__Setting_H
