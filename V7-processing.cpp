/**
\brief Processing of GPS-strings from the LX V7 variometer.
\author Bernt Hustad Hembre
\see V7 dataport specification http://max.kellermann.name/download/xcsoar/devel/lxnav/V7%20dataport%20specification%202.01.pdf

**/

#include <SD.h>
/*
From the dataport specification:

Basic description of NMEA sentences
There are three different sentences:
 PLXVF: Output data from V7 (fast data)
 PLXVS: Output data from V7 (slow data)
 PLXV0: Data to V7 (settings)
*/



void process_PLXVF(char **sstr, File f){  
//$PLXVF,time ,AccX,AccY,AccZ,Vario,IAS,PressAlt,mode *CS<CR><LF>

  f.print("V7_F;");
  f.print(sstr[1]); // time, ms from last fix
  f.print(";");
  f.print(sstr[5]); // Vario
  f.print(";");
  f.print(sstr[6]); // IAS
  f.print(";");
  f.println(sstr[7]); // Press Alt.
}


void process_PLXVS(char **sstr, File f){
  f.print("V7_S;");
  f.print(sstr[1]); // temperature centigrade
  f.print(";");
  f.println(sstr[3]); // Altitude [m] from FR
}
