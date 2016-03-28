/**
@brief Glider vario addon - diff sign. 
@author Bernt Hustad Hembre


**/

static char gpsstr[200];
static int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // Check serial port and process
  if(Serial.available() > 0)
    process_serial();
    
  // Check Analog values and update if needed
  process_analog();
  
  // Check I2C and update if needed
  process_I2C();
}


void process_serial(void)
{
  gpsstr[i++] = Serial.read();
  while(Serial.available() && (gpsstr[i-1] != NULL))
    gpsstr[i++] = Serial.read();
  if(gpsstr[i-1] == NULL){
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

  
  
}


