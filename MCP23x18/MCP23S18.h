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
 * @file MCP23S18.h
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief The library allows easier interacting with the MCP23S18 devices and
 *        offers the ability to use it similar to an internal microcontroller
 *        register
 */

#ifndef _MCP23S18_H_
#define _MCP23S18_H_

#include "MCP23x18.h"
#include "WProgram.h"
#include "HardwareSPI.h"

class MCP23S18 : public MCP23x18 {
  public:
    /*
     * Sets the MCP23x18 class to use a SPI interface and sets the chip select
     * pin to engauge the MCP23S18.
     */
    MCP23S18(HardwareSPI& dev, unsigned char cspin);
    /*
     * Writes the value to the selected register, ensuring if IOCON is written
     * to, that BANK cannot be selected.
     */
    void write(unsigned char reg, unsigned short data);

    /*
     * Reads and returns the value from the selected register
     */
    unsigned short read(unsigned char reg);
  private:
    HardwareSPI* mcpspi;
    unsigned char cs;
};

#endif