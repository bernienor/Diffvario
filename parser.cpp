
/**
@author Bernt Hustad Hembre, bernienor@github
See headerfile for more documentation.
**/


int parsecsv( char *s, char sep, char **subs, int maxsub, int maxbuf)
{
  int i = 0;
  int j = 0;
  subs[j++] = &s[i];
  while((s[i]!= 0) && (i<maxbuf) && (j<maxsub)){
    if(s[i] == sep){
      s[i++] = 0;
      subs[j++] = &s[i];
    }
  }
  if(i>=maxbuf)
    return 1;
  if(j>=maxsub)
    return 2;
  return 0;
}

/*
 * Sources of example strings: 
 * http://www.gpsinformation.org/dale/nmea.htm#stream
 * 
 */


int test_parsecsv(void)
{

  //                $PLXVF,time ,AccX,AccY,AccZ,Vario,IAS,PressAlt,mode *CS<CR><LF>"
  char gpsstr1[] = "$PLXVF,1.00,0.87,-0.12,-0.25,1.2,90.2,244.3,1,*CS\r\n";
  //               "$PLXVS,OAT,mode,voltage,IGC FR press altitude *CS<CR><LF>
  char gpsstr2[] = "$PLXVS,23.1,0,12.3,*CS\r\n"; 
  char gpsstr3[] = "$PLXVC,GPS,A,INFO,A,NANO,2.05,May 12 2012 21:38:28,d129,4.25,2.78,258.18,1,8,0*08\r\n";
  char gpsstr4[] = "$GPRMC,183729,A,3907.356,N,12102.482,W,000.0,360.0,080301,015.5,E*6F";

  char *Substr[25];

//  Serial.println("\nTest for parsecsv.c");

  
  parsecsv( gpsstr1, ',', Substr, 25, 80);
  
  
}

