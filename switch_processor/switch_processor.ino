#include <mcp_can.h>
#include <SPI.h>

int buttonPin = 0;
int previousValue = 0;

MCP_CAN CAN0(10);

void setup() {
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   

  // Using analog pin 0 for left hand switch cluster input.
  pinMode(A0, INPUT_PULLUP);

  // Using analog pin 1 for right hand switch cluster input.
  pinMode(A1, INPUT_PULLUP);
 
  Serial.println("Ready.");
}

// Switch on
byte ondata[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Switch off
byte switchdata[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void loop() {
  int buttonValue = analogRead(buttonPin);
  // In here we are going to read an array map of values and switches/states 
  // The maximum number of switches on at once is 2, if the values changes we
  // send the appropriate on/off message for the message id with the message id indicating to the 
  // relay controller which thing to switch.

    // Testing with single switch value in cluster.
    if (buttonValue > 1020) {
      Serial.println(buttonValue);
      byte state = CAN0.sendMsgBuf(0x102, 0, 8, ondata);
      if(state == CAN_OK){
        Serial.println("Message Sent Successfully!");
      } else {
        Serial.println("Error Sending Message...");
      }

      previousValue = buttonValue;
    }
  
  // Allow 25 ms delay to prevent bad reads.
  delay(25);
}
