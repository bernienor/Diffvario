
/**
\brief Processing of GPS-strings from the Nano logger (Via the V7)
\author Bernt Hustad Hembre
\see Nano dataport specification http://max.kellermann.name/download/xcsoar/devel/lxnav/nano%20dataport%20specification.pdf

**/

#include <SD.h>

void process_NANO(char **sstr, File f){  
//$PLXVF,time ,AccX,AccY,AccZ,Vario,IAS,PressAlt,mode *CS<CR><LF>

  f.println("Nano Loggin!");
}


// http://aprs.gids.nl/nmea/#gga $GPGGA
void process_GPGGA(char **sstr, File f){  
  
  f.print("GPS;");
  f.print(sstr[1]); // Time in UTC
  f.print(";");

  f.print(sstr[2]); // Lattitude
  f.print(sstr[3]); // Lattitude N/S
  f.print(";");

  f.print(sstr[4]); // Longitude
  f.print(sstr[5]); // Longitude E/W
  f.print(";");

  f.println(sstr[10]); // GPS Altitude
}

