//Coded by Ege Kemahlıoğlu

#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial1(3,2);
#define LOG_PERIOD 15000    
#define MAX_PERIOD 60000   
unsigned long counts;            
unsigned long cpm;             
unsigned int multiplier;             
unsigned long previousMillis;     
 
void tube_impulse(){              
  counts++;
}

void setup(){                                             
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;      
  Serial1.begin(9600);                                   
  pinMode(2, INPUT);                                  
  digitalWrite(2, HIGH);                                
  attachInterrupt(0, tube_impulse, FALLING);  
}

void loop(){                                               
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){
    previousMillis = currentMillis;
    cpm = counts * multiplier;
  
        Serial1.write("CPM: ");
        Serial1.print(cpm);                              
        Serial1.write("\n");            
    counts = 0;
  }
}
