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
 * @brief The library allows easier interacting with the MCP23x18 devices and
 *        offers the ability to use it similar to an internal microcontroller
 *        register
 */
 
#include "MCP23x18.h"

MCP23x18::MCP23x18(void) {
#if defined(useregs)
  initReg();
#endif
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