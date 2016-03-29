
#include "SD.h"
#include "parser.h"
#include "V7-processing.h"
#include "Nano-processing.h"
#include "process_gpsstr.h"

void process_gpsstr(char *str, File f){
  char *Substr[15];
  
  int errorcode = parsecsv( str, ',', Substr, 15, GPS_STR_LENGTH);
  if(errorcode){
    f.print("Parsing Error code: ");
    f.print(String(errorcode));
    f.print(" String: \"");
    f.print(str);
  }

  // High freq, should be among the first tests.
  if(strcmp(Substr[0],"$PLXVF")){
    process_PLXVF(Substr, f);
    return;
  }

  if(strcmp(&Substr[0][3],"GGA")){  // Hack to include all GPS-sources. Not sure it's needed.
    process_GPGGA(Substr, f);
  return;
  }  
  
  // Low freq, can be left at the end.
  if(strcmp(Substr[0],"$PLXVS")){
    process_PLXVS(Substr, f);
  return;
  }  
}

