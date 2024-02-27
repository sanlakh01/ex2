let pHtmlMsg;
let serialOptions = { baudRate: 9600  };
let serial;

let r = 0;
let g = 0;
let b = 0;
let bright = 0;

function setup() {
  createCanvas(windowWidth - 10, windowHeight -10);
  pHtmlMsg = createP("Click anywhere on this page to open the serial connection dialog");
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);

  serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);

}

function draw() {
  background(r,g,b);
}

function mouseClicked(){

  if (!serial.isOpen()) {
    serial.connectAndOpen(null, serialOptions);
  }
  r = (int(random(0,256)))*bright/100;
  g = (int(random(0,256)))*bright/100;
  b = (int(random(0,256)))*bright/100;

  serialWriteLEDColor(r,g,b); // send the red, green, blue information to Arduino through serial
}

/**
 * Called automatically by the browser through p5.js when data sent to the serial
 */
async function serialWriteLEDColor(red, green, blue){
  if(serial.isOpen()){
    let strData = red + "," + green + "," + blue;
    console.log(strData);
    serial.writeLine(strData);
  }
}

/**
 * Callback function by serial.js when there is an error on web serial
 * 
 * @param {} eventSender 
 */
function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  pHtmlMsg.html(error);
}

/**
 * Callback function by serial.js when web serial connection is opened
 * 
 * @param {} eventSender 
 */
function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  //pHtmlMsg.html("Serial connection opened successfully");
}

/**
 * Callback function by serial.js when web serial connection is closed
 * 
 * @param {} eventSender 
 */
function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  pHtmlMsg.html("onSerialConnectionClosed");
}

/**
 * Callback function serial.js when new web serial data is received
 * 
 * @param {*} eventSender 
 * @param {String} newData new data received over serial
 */
function onSerialDataReceived(eventSender, newData) {
  //console.log("onSerialDataReceived", newData);
  //pHtmlMsg.html("onSerialDataReceived: " + newData);
  // Parse the incoming value as a int
  bright = parseInt(newData);
}