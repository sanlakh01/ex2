int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int bright;
const int rgb_red = 11;
const int rgb_blue = 3;
const int rgb_green = 5;

int redVal = 0;
int greenVal = 0;
int blueVal = 0;

void setup() {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  pinMode(photocellPin, INPUT); // Sets the red pin as an Output
  pinMode(rgb_red, OUTPUT); // Sets the red pin as an Output
  pinMode(rgb_green, OUTPUT); // Sets the green pin as an Output
  pinMode(rgb_blue, OUTPUT); // Sets the blue pin as an Output
}

void setRGBLedColor(int red, int green, int blue){
  analogWrite(rgb_red, red);
  analogWrite(rgb_green, green);
  analogWrite(rgb_blue, blue);
}

void loop() {
  
  photocellReading = analogRead(photocellPin);
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  bright = map(photocellReading, 0, 1000, 0, 100); 
  Serial.println(bright);

  // Read color data from the serial
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
  delay(1000);
}