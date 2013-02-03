/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2013 Trystan Jones
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file MCP23x18.cpp
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief Wire library, uses the WireBase to create the primary interface
 *        while keeping low level interactions invisible to the user.
 */
 
#include "MCP23x18.h"

MCP23x18::MCP23x18(HardwareSPI& dev, unsigned char cspin) {
  mcpspi = &dev;
  cs = cspin;
  porttype = false;
  addr = MCP23x18_DEF_ADDR;
#if defined(useregs)
  initReg();
#endif
}

MCP23x18::MCP23x18(WireBase& dev, unsigned char address) {
  mcptw = &dev;
  porttype = true;
  addr = ((MCP23x18_DEF_ADDR>>1)|(address&0x07));
#if defined(useregs)
  initReg();
#endif
}

void MCP23x18::write(unsigned char reg, unsigned short data) {
  if((reg == IOCON_ADDR) && (data&0x80)) {
    data &= ~0x80;
  }
  if (porttype == false) {
    digitalWrite(cs, LOW);
    mcpspi->transfer(addr);
    mcpspi->transfer(reg);
    mcpspi->transfer(data&0xFF);
    if((reg != IOCON_ADDR))
      mcpspi->transfer((data>>8)&0xFF);
    digitalWrite(cs, HIGH);
  }
  if (porttype == true) {
    mcptw->beginTransmission(addr);
    mcptw->send(reg);
    mcptw->send(data&0xFF);
    mcptw->send((data>>8)&0xFF);
    mcptw->endTransmission();
  }
}

unsigned short MCP23x18::read(unsigned char reg) {
  unsigned char temp[2] ={0x00};
  if (porttype == false) {
    digitalWrite(cs, LOW);
    mcpspi->transfer(addr|0x01);
    mcpspi->transfer(reg);
    temp[0] = mcpspi->transfer(0x00);
    temp[1] = mcpspi->transfer(0x00);
    digitalWrite(cs, HIGH);
  }
  if (porttype == true) {
    mcptw->beginTransmission(addr);
    mcptw->send(reg);
    mcptw->endTransmission();
    mcptw->requestFrom(addr, 2);
    temp[0] = mcptw->receive();
    temp[1] = mcptw->receive();
  }
  return ((temp[1]<<8)|temp[0]);
}

#if defined(useregs)
void MCP23x18::initReg(void) {
  IODIR.setAddr(IODIR_ADDR);
  IODIR.setMCP(*this);
  IPOL.setAddr(IPOL_ADDR);
  IPOL.setMCP(*this);
  GPINTEN.setAddr(GPINTEN_ADDR);
  GPINTEN.setMCP(*this);
  DEFVAL.setAddr(DEFVAL_ADDR);
  DEFVAL.setMCP(*this);
  INTCON.setAddr(INTCON_ADDR);
  INTCON.setMCP(*this);
  IOCON.setAddr(IOCON_ADDR);
  IOCON.setMCP(*this);
  GPPU.setAddr(GPPU_ADDR);
  GPPU.setMCP(*this);
  INTF.setAddr(INTF_ADDR);
  INTF.setMCP(*this);
  INTCAP.setAddr(INTCAP_ADDR);
  INTCAP.setMCP(*this);
  GPIO.setAddr(GPIO_ADDR);
  GPIO.setMCP(*this);
  OLAT.setAddr(OLAT_ADDR);
  OLAT.setMCP(*this);
}
#endif

MCP23x18::MCPreg::MCPreg(unsigned char add) {
  setAddr(add);
}

void MCP23x18::MCPreg::setAddr(unsigned char add) {
  regAddr = add;
}

void MCP23x18::MCPreg::setMCP(MCP23x18& device) {
  dev = &device;
}

MCP23x18::MCPreg::operator short() {
  return dev->read(regAddr);
}

unsigned short MCP23x18::MCPreg::operator= (unsigned short value) {
  dev->write(regAddr, value);
  return value;
}