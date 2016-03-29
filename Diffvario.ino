/**
\brief Glider vario addon - diff sign. 
\author Bernt Hustad Hembre

\todo: extract / rearrange SD-card writing to a seperate file/class
\todo pwrdown Pin logic and definition update vs schematics.

**/

/*
 The SD card circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 */

#include <SPI.h>
#include <SD.h>
#include "parser.h"
#include "V7-processing.h"
#include "Nano-processing.h"

// Various defines for measurement setup:
#define GPS_STR_LENGTH 100
const int ANALOG_MEAS_FREQ = 10;

const int chipSelect = 10;
static char gpsstr[GPS_STR_LENGTH];
static int i;
static File dataFile;
static int maxstr_error = 0; // Counter for string overflow "exeptions"
const int pwrdwnPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  if (!SD.begin(chipSelect)) {
    return; // Nothing to do if SD fails.
  }
  dataFile = SD.open("datalog.txt", FILE_WRITE); /// \todo replace with function for unique filename
}

void loop() {
  // Check serial port and process
  if(Serial.available() > 0)
    process_serial();
    
  // Check Analog values and update if needed
  process_analog();
  
  // Check I2C and update if needed
  process_I2C();
  
  if(digitalRead(pwrdwnPin) == LOW){
    dataFile.println("END");
    dataFile.close();
  }

}


void process_serial(void)
{
  gpsstr[i++] = Serial.read();
  while(Serial.available() && (gpsstr[i-1] != 0)){
    gpsstr[i++] = Serial.read();
    if(i>=GPS_STR_LENGTH){
      gpsstr[i-1] = 0; // End of buffer, terminating the string.  
      maxstr_error++;
    }
  }
  if(gpsstr[i-1] == 0){
    process_gpsstr(gpsstr);
    i=0;
  }
}

/**
\brief reads and logs analog io-pins to the SD-card
\todo Update with valid and usable pins. 4 pins used as an example.
**/
void  process_analog()
{
  static long nextmeas = 0; // To keep track of our measurements
  const int interval = 1000/ANALOG_MEAS_FREQ;

  if(millis()>nextmeas){
    nextmeas += interval;
    dataFile.print("Analog;");
    dataFile.print(analogRead(0)); 
    dataFile.print(";");
    dataFile.print(analogRead(1)); 
    dataFile.print(";");
    dataFile.print(analogRead(2)); 
    dataFile.print(";");
    dataFile.println(analogRead(3)); 
  }
}

void process_I2C(){
  static long nextmeas = 0; // To keep track of our measurements
  const int interval = 1000; // [ms]

  if(millis()>nextmeas){
    nextmeas += interval;

  }  
}

void process_gpsstr(char *str){
  char *Substr[15];
  
  int errorcode = parsecsv( str, ',', Substr, 15, GPS_STR_LENGTH);
  if(errorcode){
    dataFile.print("Parsing Error code: ");
    dataFile.print(String(errorcode));
    dataFile.print(" String: \"");
    dataFile.print(str);
  }

  // High freq, should be among the first tests.
  if(strcmp(Substr[0],"$PLXVF")){
    process_PLXVF(Substr, dataFile);
    return;
  }


  if(strcmp(&Substr[0][3],"GGA")){  // Hack to include all GPS-sources. Not sure it's needed.
    process_GPGGA(Substr, dataFile);
  return;
  }  
  // Low freq, can be left at the end.
  if(strcmp(Substr[0],"$PLXVS")){
    process_PLXVS(Substr, dataFile);
  return;
  }  
}

void process_gpsxxx(char **sstr){
  dataFile.println("GPS Dummy example");
}

