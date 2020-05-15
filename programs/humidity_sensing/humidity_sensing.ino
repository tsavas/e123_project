
//Pin connections for Sensor:
// pin 1 : VCC
// pin 2 : DATA
// pin 3 : NC
// PIN 4 : GND

#include <dhtnew.h>                   //include the DHT11 sensor library

int DHT11_PIN = 8;                    //Create a variable for the sensor's pin
int FAN_PIN = 7;                      //Create a variable for the fan's pin
int MAX_TEMP = 22;                    //Create a varaible for the maximum temperature limit

DHTNEW mySensor(DHT11_PIN);           //Create a DHT11 instance and assign it to the pin

void setup(){
  
  Serial.begin(115200);               //Initialize serial comms and set the baud rate
  mySensor.setHumOffset(10);          //Some boiler plate setup for the DHT11 sensor
  mySensor.setTempOffset(-1.5);       //Some boiler plate setup for the DHT11 sensor
  pinMode(FAN_PIN, OUTPUT);           //Set the fan's pin as an output pin
  digitalWrite(FAN_PIN, HIGH);        //Set it high, in off position, at start
  
  }

void loop(){

    mySensor.read();                                //Read the sensor
    int temp = mySensor.getTemperature();           //Create a variable and put the temp value in it
    Serial.print(mySensor.getHumidity(), 1);        //Print the humidity value with one decimal place
    Serial.print("\t");                             //Text break
    Serial.println(temp, 1);                        //Print the temperature value
    
    if(temp > MAX_TEMP){                            //If temp is higher than 22C
        digitalWrite(FAN_PIN, LOW);                 //Turn on the fan
    }
    else if(temp <= MAX_TEMP){                      //If temp is lower or eq to 22C
        digitalWrite(FAN_PIN, HIGH);                //Turn off the fan
    }
    delay(2000);                                    //Wait two seconds until next reading

  } 

// END OF FILE
