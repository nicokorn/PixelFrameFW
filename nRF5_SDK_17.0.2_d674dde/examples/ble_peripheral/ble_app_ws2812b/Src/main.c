// ****************************************************************************
/// \file      main.c
///
/// \brief     MAIN C Source File
///
/// \details   to do
///
/// \author    Nico Korn
///
/// \version   1.0.0.0
///
/// \date      24032021
/// 
/// \copyright Copyright (c) 2021 Nico Korn
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///
/// \pre       
///
/// \bug       
///
/// \warning   
///
/// \todo      
///
// ****************************************************************************

// Include ********************************************************************
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "bleapp.h"
#include "ws2812b.h"
#include "nrf_delay.h"

// Private define *************************************************************

// Private types     **********************************************************

// Private variables **********************************************************

// Private function prototypes ************************************************

// Global variables ***********************************************************

// Functions ******************************************************************
// ----------------------------------------------------------------------------
/// \brief     Entry point of the application.
///
/// \param     none
///
/// \return    none
 int main(void)
{
   bool erase_bonds;
    
   static uint32_t i;

   WS2812B_init();
   bleapp_init();
   
   WS2812B_clearBuffer();
   WS2812B_sendBuffer();
   
   // Enter main loop.
   for (;;)
   {
      WS2812B_sendBuffer();
      nrf_delay_ms(100); 
   }
}