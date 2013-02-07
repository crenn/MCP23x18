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
 * @file MCP23018.cpp
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief The library allows easier interacting with the MCP23018 devices and
 *        offers the ability to use it similar to an internal microcontroller
 *        register
 */

#include "MCP23018.h"

MCP23018::MCP23018(WireBase& dev, unsigned char address) {
  mcptw = &dev;
  addr = ((MCP23x18_DEF_ADDR>>1)|(address&0x07));
}

void MCP23018::write(unsigned char reg, unsigned short data) {
  if((reg == IOCON_ADDR) && (data&0x80)) {
    data &= ~0x80;
  }
  mcptw->beginTransmission(addr);
  mcptw->send(reg);
  mcptw->send(data&0xFF);
  if((reg != IOCON_ADDR))
    mcptw->send((data>>8)&0xFF);
  mcptw->endTransmission();
}

unsigned short MCP23018::read(unsigned char reg) {
  unsigned char temp[2] ={0x00};
  mcptw->beginTransmission(addr);
  mcptw->send(reg);
  mcptw->endTransmission();
  mcptw->requestFrom(addr, 2);
  temp[0] = mcptw->receive();
  temp[1] = mcptw->receive();
  return ((temp[1]<<8)|temp[0]);
}