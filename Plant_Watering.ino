int pumpPin = A0; // pin that turns on the motor
int moisturePin = A1; //pin A1 that reads moisture sensor
int moisturePower = 7; //pin D7 that turns on the moisture sensor

int waterTime = 10; // how long to water (run the pump) in seconds
int waitTime = 1440; // how long to wait between reading moisture sensor in minutes
int threshold = 250; //moisture content threshold (set this value for your plant after calibrating moisture sensor)
int moistureValue; //variable for moisture value read by moisture sensor

//run setup function to configure pins on startup
void setup() {
  pinMode(pumpPin, OUTPUT); // set A0 to an output so we can use it to turn on the MOSFET
  digitalWrite(pumpPin, LOW); //set A0 to LOW so pump is not powered on start up
  pinMode(moisturePower, OUTPUT); //set D7 as an output
  digitalWrite(moisturePower, LOW); //set to LOW so sensor is not powered on start up
}

//create the loop that the arduino will run indefinitely
void loop() {
  
  readMoisture();

  // Now we are going to check if the water level is below the threashold we set earlier, and if it is run the waterPlant function which controls the pump to water the plant
  if (moistureValue <= threshold) {
    waterPlant();
  }

  delay(waitTime*60000); //wait to take the next moisture sensor reading. Multiply by 60,000 to convert minutes to milliseconds
}

//This is a function used to get the soil moisture content
int readMoisture() {
  digitalWrite(moisturePower, HIGH); //turn D7 ON
  delay(1000); //wait one second
  moistureValue = analogRead(moisturePin); //Read the SIG (signal) value from the sensor
  digitalWrite(moisturePower, LOW); //turn D7 OFF
  return moistureValue; //send current moisture value
}

//This is a function used to run the pump
int waterPlant() {
  digitalWrite(pumpPin, HIGH); // turn on the pump
  delay(waterTime * 1000);      //delay turning pump off for a certain length of time defined by waterTime. Multiply by 1000 to translate seconds to milliseconds
  digitalWrite(pumpPin, LOW);  // turn off the pump
}

