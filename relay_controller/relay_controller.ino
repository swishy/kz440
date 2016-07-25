#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                               // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
 
  // Initialize MCP2515 running at 16MHz with a baudrate of 1000kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");
 
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  pinMode(6, OUTPUT);                           // Setting pin 6 to relay int 1
  Serial.println("Kawasaki canbus relay controller initialized.");
}

void loop()
{
    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&rxId, &len, rxBuf);

      Serial.println(rxId);

      // Read data: len = data length, buf = data byte(s)
      
      /**if(rxId == 0x102) {
        Serial.print("ID: ");                     // Print the message ID.
        Serial.print(rxId, HEX);
        digitalWrite(6,LOW);
        delay(2000);                                      // Wait 2 seconds
        digitalWrite(6,HIGH);
      }*/
    }
}
