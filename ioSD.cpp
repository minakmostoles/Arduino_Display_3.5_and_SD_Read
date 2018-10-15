/***********************************************************************************************************************************/
/*                                                Modulo de lectura/escritura en la SD                                             */
/*                                                     Soporte SD V_181012                                                  */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#include "ioSD.h"

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

bool setupSD(){
  Serial.println(F("\nIniciando modulo SD..."));
    //Con arduino UNO SPI_HALF_SPEED
    #if defined UNO_MCU
      if (!card.init(SPI_HALF_SPEED, CHIPSELET)) {
        Serial.print(F("Inicializacion fallida."));
        //while (1);
      } else {
        SD.begin(CHIPSELET);
        Serial.print(F("SD inicializada correctamente."));
      }
    #endif
    #if defined WEMOS_MCU //Con WEMOS
    if (!SD.begin(CHIPSELET)) { 
      Serial.print(F("Inicializacion fallida."));
      return false;
    } 
    Serial.print(F("SD inicializada correctamente."));
    #endif
    
  #if defined(MODE_DEBUG_FES)          //Solo si esta activado el puerto serie y el debug funciones especiales
    if (infoSD()){getListFile();}
    //grabarTXTSD ("hola,me llamo mario");
    //leerTXTSD();
  #endif
  
  return true;
}

String leerTXTSD (){
  bool stringComplete = false;
  String inputString = "";
  File dataFile = SD.open(FILENAME, FILE_READ);// Reading the file
  if (dataFile) {
    //Serial.println("Read:");
    // Reading the whole file
    while (dataFile.available()) {
      char inChar = (char)dataFile.read();
      inputString += inChar; // add it to the inputString:
     }
    //while (dataFile.available()) {
      //result = dataFile.read();
      //Serial.write(dataFile.read());  
    //}
    //Serial.println(inputString); 
    dataFile.close();
    return inputString;
  }
  else {
    Serial.println(F("Error al abrir el fichero"));
    return "";
  }
} 

void grabarTXTSD (String dataString){
    File dataFile = SD.open(FILENAME, FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println(F("Error al abrir el fichero"));
    }
  }  

bool infoSD(){
  // print the type of card
  Serial.println();
  Serial.print(F("Tipo de tarjeta:         "));
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Desconocido"));
  }

  if (!volume.init(card)) {
    Serial.println(F("No se encuentra particion FAT16/FAT32. Tiene tabla de particiones la tarjeta?"));
    Serial.println(F("La tarjeta SD no se podra utilizar hasta que este formateada en FAT16/32."));
    return false;
  }
  
  Serial.print(F("Clusters:          "));
  Serial.println(volume.clusterCount());
  Serial.print(F("Bloques/Cluster:  "));
  Serial.println(volume.blocksPerCluster());

  Serial.print(F("Total Bloques:      "));
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println("---------------------------------------------");

  uint32_t volumesize;
  Serial.print(F("El tipo de formato es:    FAT"));
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // Los cluster por bloque
  volumesize *= volume.clusterCount();       
  volumesize /= 2;                           // Los cluster en KB
  //Serial.print(F("Tamagno (Kb):  "));
  //Serial.println(volumesize);
  //Serial.print(F("Tamagno (Mb):  "));
  //volumesize /= 1024;
  //Serial.println(volumesize);
  Serial.print(F("Volume size (Gb):  "));
  Serial.println((float)volumesize / 1024.0);
  return true;
}

void getListFile (){
  Serial.println("\nLos fichero sobre la SD: \n  (NOMBRE       , FECHA   Y   TAMAGNO EN BYTES) ");
  Serial.println("---------------------------------------------");
  root.openRoot(volume);
  // Listar todos los ficheros en la tarjeta con nombre fecha y tamagno
  root.ls(LS_R | LS_DATE | LS_SIZE);
  Serial.println("---------------------------------------------");
}



