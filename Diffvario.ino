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

#define GPS_STR_LENGTH 100

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

void  process_analog()
{


  
}

void process_I2C(){

  
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

  // Example struture;
  if(strcmp(Substr[0],"$GPSXXX"))
    process_gpsxxx(Substr);
  //dataFile.println(str);
  
}

void process_gpsxxx(char **sstr){
  dataFile.println("GPS Dummy example");


  
}

