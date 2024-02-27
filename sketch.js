let pHtmlMsg; //variable for on-screen messaging
let serialOptions = { baudRate: 9600  };
let serial; //variable to call the web serial functions

let r = 0; //red value for the RGB LED
let g = 0; //green value for the RGB LED
let b = 0; //blue value for the RGB LED
let bright = 0; //"brightness ratio" factor, from the photoresistor

function setup() {
  createCanvas(windowWidth, windowHeight); //takes up the full width of the screen
  
  //taken directly from "UltraRipple" demo code
  pHtmlMsg = createP("Click anywhere on this page to open the serial connection dialog");
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);
  serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
}

function draw() {
  background(r,g,b); //changes the page color to match the LED
}

function mouseClicked(){
//called when mouse click is recorded
  if (!serial.isOpen()) {
    serial.connectAndOpen(null, serialOptions);
  }
  //generates random values for r, g, b and modifies their "brightness" based on photoresistor input
  r = (int(random(0,256)))*bright/100;
  g = (int(random(0,256)))*bright/100;
  b = (int(random(0,256)))*bright/100;

  serialWriteLEDColor(r,g,b); // send the red, green, blue information to Arduino through serial
}

//following functions are taken from "UltraRipple" demo code and modified to fit this project
async function serialWriteLEDColor(red, green, blue){
  if(serial.isOpen()){
    let strData = red + "," + green + "," + blue;
    console.log(strData);
    serial.writeLine(strData);
  }
}

function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  pHtmlMsg.html(error);
}

function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  //pHtmlMsg.html("Serial connection opened successfully");
}

function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  pHtmlMsg.html("onSerialConnectionClosed");
}

function onSerialDataReceived(eventSender, newData) {
  //console.log("onSerialDataReceived", newData);
  //pHtmlMsg.html("onSerialDataReceived: " + newData);
  // Parse the incoming value as a int
  bright = parseInt(newData);
}