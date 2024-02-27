int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int bright;               //the brightness value mapped from photoresistor input
const int rgb_red = 11;   //RGB LED output pin
const int rgb_blue = 3;   //RGB LED output pin
const int rgb_green = 5;   //RGB LED output pin

int redVal = 0;     //value to be sent to serial monitor
int greenVal = 0;   //value to be sent to serial monitor
int blueVal = 0;    //value to be sent to serial monitor

void setup() {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  pinMode(photocellPin, INPUT); // Sets the red pin as an Output
  pinMode(rgb_red, OUTPUT); // Sets the red pin as an Output
  pinMode(rgb_green, OUTPUT); // Sets the green pin as an Output
  pinMode(rgb_blue, OUTPUT); // Sets the blue pin as an Output
}

//this function sets the RGB LED color from Web Serial
void setRGBLedColor(int red, int green, int blue){
  analogWrite(rgb_red, red);
  analogWrite(rgb_green, green);
  analogWrite(rgb_blue, blue);
}

void loop() {
  
  photocellReading = analogRead(photocellPin);  //input from photoresistor
  photocellReading = 1023 - photocellReading;   //reversing it, since higher the reading, the dimmer the LED
  bright = map(photocellReading, 0, 1000, 0, 100); //mapping the reading to a "brightness ratio" --> see document for explanation
  Serial.println(bright); //to the serial it goes! (so that the webpage can also "dim" or "brighten" accordingly)

  // Read color data from the serial - following code taken directly from "UltraRipple Sensor" Demo files
  if(Serial.available() > 0){
    // If we are here, then serial data has been received
    // Read data off the serial port until we get ot the endline delimeter ('\n')
    String rcvdSerialData = Serial.readStringUntil('\n');

    // Parse the comma separated string
    int startIndex = 0;
    int endIndex = rcvdSerialData.indexOf(','); // find first index of comma in the string

    if(endIndex != -1){

      // Parse out the first color value - red
      String strRedVal = rcvdSerialData.substring(startIndex, endIndex);
      redVal = strRedVal.toInt();

      // Parse out the second color value - green
      startIndex = endIndex + 1;
      endIndex = rcvdSerialData.indexOf(',', startIndex);
      String strGreenVal = rcvdSerialData.substring(startIndex, endIndex);
      greenVal = strGreenVal.toInt();

      // Parse out the third color value - blue
      startIndex = endIndex + 1;
      endIndex = rcvdSerialData.indexOf(',', startIndex);
      String strBlueVal = rcvdSerialData.substring(startIndex, endIndex);
      blueVal = strBlueVal.toInt();

      // Set the RGB led with the read red, green, and blue color
      setRGBLedColor(redVal, greenVal, blueVal);
    }
  }
  delay(1000); //setting delay to slow down the rapid changes in LED color
}
//Code sourced from in-class example code and from Arduino Stack Exchange. 
//https://arduino.stackexchange.com/questions/86427/how-to-change-brightness-of-led-light