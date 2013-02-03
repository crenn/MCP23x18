#include <HardWire.h>
#include <MCP23x18.h>

HardWire port(1);
MCP23x18 mcp(port, 0);


void setup(void) {
  port.begin();
  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);
  digitalWrite(21, HIGH);
  delayMicroseconds(500);
  mcp.IOCON = 0x0020;
  mcp.IODIR = 0x0000;
  mcp.GPPU = 0xFFFF;
}

void loop(void) {
  static unsigned short val = 0x0001;
  mcp.GPIO = (~val);
  delay(100);
  val <<= 1;
  if((val & 0x20) != 0) {
    val |= 0x01;
  }
}

