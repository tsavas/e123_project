
int CO2; //create a variable for incoming CO2 data

void setup() {

  Serial.begin(19200); //initialize serial comms and match baud rate to sensor
  Serial.println("Program Start");  //writing to the console is just fun


}

void loop() {

if (Serial.available() > 0){    //only do this if there's something coming onto the serial
  CO2 = Serial.read();          //move whatever's on the serial over to the CO2 var
  Serial.print(CO2);            //print the CO2 reading
  delay(100);                   //wait one second until the next reading
  }
}
