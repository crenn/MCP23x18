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
 * @file MCP23x18.h
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief The library allows easier interacting with the MCP23x18 devices and
 *        offers the ability to use it similar to an internal microcontroller
 *        register
 */

#ifndef _MCP23x18_H_
#define _MCP23x18_H_

#include "WProgram.h"

// Default opcode address of the MCP23x18
#define MCP23x18_DEF_ADDR   0x40

// MCP23x18 Register Addresses
#define IODIR_ADDR          0x00
#define IPOL_ADDR           0x02
#define GPINTEN_ADDR        0x04
#define DEFVAL_ADDR         0x06
#define INTCON_ADDR         0x08
#define IOCON_ADDR          0x0A
#define GPPU_ADDR           0x0C
#define INTF_ADDR           0x0E
#define INTCAP_ADDR         0x10
#define GPIO_ADDR           0x12
#define OLAT_ADDR           0x14

/*
 * Comment out this line if you do not wish to access the MCP23x18 device
 * registers automatically
 * E.g. mcp.write(GPIO_ADDR, 0xFFFF); instead of mcp.GPIO = 0xFFFF;
 */
#define useregs

class MCP23x18 {
  public:
    
    /*
     * Default constructor
     */
    MCP23x18(void);

#if defined(useregs)
    /*
     * To enable easy access to the registers, a sub-class is used to implement
     * easy access
     */
    class MCPreg {
    public:
      /*
       * Initialises the register interface
       */
      MCPreg(unsigned char add = 0x00);
      
      /*
       * Sets the class' register address
       */
      void setAddr(unsigned char add = 0x00);
      
      /*
       * Sets the MCP23x18 class needed to access the register
       */
      void setMCP(MCP23x18& device);
      
      /*
       * Accessing the register will trigger a read of the MCP register
       */
      operator short();
      
      /*
       * Setting a value for the register will trigger a write to the MCP
       * register
       */
      unsigned short operator= (unsigned short value);
    private:
      MCP23x18 *dev;
      unsigned char regAddr;
    };
    MCPreg IODIR;
    MCPreg IPOL;
    MCPreg GPINTEN;
    MCPreg DEFVAL;
    MCPreg INTCON;
    MCPreg IOCON;
    MCPreg GPPU;
    MCPreg INTF;
    MCPreg INTCAP;
    MCPreg GPIO;
    MCPreg OLAT;
#endif

    /*
     * Writes the value to the selected register, ensuring if IOCON is written
     * to, that BANK cannot be selected. Abstract to ensure must be defined by
     * sub class.
     */
    virtual void write(unsigned char reg, unsigned short data) = 0;
    
    /*
     * Reads and returns the value from the selected register. Abstract to
     * ensure must be defined by sub class.
     */
    virtual unsigned short read(unsigned char reg) = 0;
  private:
#if defined(useregs)
    /*
     * Initialises the register classes to allow access
     */
    void initReg(void);
#endif
  protected:
    unsigned char addr;
};

#endif