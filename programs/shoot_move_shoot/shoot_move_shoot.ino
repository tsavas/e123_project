
int DIR_PIN = 2;          //A variable for the stepper driver's DIR pin location
int STEP_PIN = 3;         //A variable for the stepper driver's STEP pin location
int ENABLE_PIN = 4;       //A variable for the stepper driver's EN pin location
int SHUTTER_PIN = 10;     //A variable for the camera's remote shutter pin location

//Here are values
int TIME_BETWEEN_SHOTS = 500; //A variable for the time (ms) in between camera shots, described below
int BULB = 200;               //A variable for the time (ms) the camera shutter is pressed, described below
int PAUSE = 300;              //A variable for the time (ms) between motor stop and camera shutter, desribed below
int SHOTS = 3;                //Number of shots to to take in the sequence
int STEPS = 500;              //Number of steps to turn in the sequence


//I am still working on making some conversions for the "STEPS" variable so that I can just enter an angle of rotation
//Code works without this for the time being
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//int STEPS_PER_ROTATION = 40; I tried
//int DEGREES = 360;
//int DEGREES_CONVERTED = (DEGREES*STEPS_PER_ROTATION)/360;
////int DEGREES = ;
////int INT = ;
//int TRAVEL = STEPS_PER_ROTATION/SHOTS;
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––


void setup() {               
  pinMode(DIR_PIN, OUTPUT);         //Set the stepper driver DIT pin as an output
  pinMode(STEP_PIN, OUTPUT);        //Set the stepper driver STEP pin as an output
  pinMode(ENABLE_PIN, OUTPUT);      //Set the stepper driver EN pin as an output
  pinMode(SHUTTER_PIN, OUTPUT);     //Set the camera shutter pin as an output
  digitalWrite(SHUTTER_PIN, HIGH);  //Start with the camera shutter high (it's active low)
  digitalWrite(ENABLE_PIN, LOW);    //Start with the EN pin low (it's active high)
  Serial.begin(9600);               //Set the baud rate for some serial communication,
                                    //I was reading to the monitor at one point so I needed this.
    }

void loop() {

for(int k = 0; k<SHOTS; k++){                 //A loop for how many shots. This is how many times the "move-shoot" sequence runs
                                              //If I want to create a 2-minute time lapse video at 24fps, I'll need 2880, for instance
      for(int i = 0; i<STEPS; i++){           //A loop for the high edges to send; this loop determines the angle of rotation per shot
            digitalWrite(STEP_PIN, HIGH);     //Send the STEP_PIN a high edge
            digitalWrite(STEP_PIN, LOW);      //Set it back low so it can get a high edge again when it returns
            delay(1);                         //A small amount of time between edges is necessary for the motor to operate properly
            }
        
       delay(PAUSE);                          //Pause between motor stop and camera shutter firing
       digitalWrite(SHUTTER_PIN, LOW);        //Fire the camera shutter through the remote cable
       delay(BULB);                           //Set the time the shutter is held (bulb)
       digitalWrite(SHUTTER_PIN, HIGH);       //Shutter is let go
       delay(TIME_BETWEEN_SHOTS);             //Some time delay between shots. This is important depending on subject.
                                              //If I'm shooting a plant growing, then I'll want a few minutes
                                              //If I'm shooting traffic moving, just a few seconds
    }
        
  digitalWrite(ENABLE_PIN, HIGH);             //Stop the motor after it's done with it's sequence. This is my favorite line in here.
 
}
