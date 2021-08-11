// ****************************************************************************
/// \file      frame_templates.h
///
/// \brief     Frame templates C Header File
///
/// \details   Templates for the frame.
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

// Define to prevent recursive inclusion **************************************
#ifndef __FRAME_TEMPLATES_H
#define __FRAME_TEMPLATES_H

// Include ********************************************************************
#include "nrf.h"
#include "stdbool.h"
#include "ws2812b.h"
#include "frame.h"

// Exported defines ***********************************************************

// Exported types *************************************************************

// Exported variables *********************************************************
#define LOADSIZE 63u
static const Frame_Pixel_t loadScreen[LOADSIZE] = {  // x,y,l,r,g,b
   { .x= 0, .y= 1, .r= 0, .g= 0, .b= 0 }, // L
   { .x= 0, .y= 2, .r= 0, .g= 0, .b= 0 }, // L 
   { .x= 0, .y= 3, .r= 0, .g= 0, .b= 0 }, // L
   { .x= 0, .y= 4, .r= 0, .g= 0, .b= 0 }, // L
   { .x= 1, .y= 4, .r= 0, .g= 0, .b= 0 }, // L
   { .x= 2, .y= 4, .r= 0, .g= 0, .b= 0 }, // L
   { .x= 4, .y= 1, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 4, .y= 2, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 4, .y= 3, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 4, .y= 4, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 5, .y= 1, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 5, .y= 4, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 6, .y= 1, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 6, .y= 2, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 6, .y= 3, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 6, .y= 4, .r= 0, .g= 0, .b= 0 }, // O
   { .x= 8, .y= 1, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 2, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 3, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 4, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 9, .y= 1, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 9, .y= 3, .r= 0, .g= 0, .b= 0 }, // A
   { .x=10, .y= 1, .r= 0, .g= 0, .b= 0 }, // A
   { .x=10, .y= 2, .r= 0, .g= 0, .b= 0 }, // A
   { .x=10, .y= 3, .r= 0, .g= 0, .b= 0 }, // A
   { .x=10, .y= 4, .r= 0, .g= 0, .b= 0 }, // A
   { .x=12, .y= 1, .r= 0, .g= 0, .b= 0 }, // D
   { .x=12, .y= 2, .r= 0, .g= 0, .b= 0 }, // D
   { .x=12, .y= 3, .r= 0, .g= 0, .b= 0 }, // D
   { .x=12, .y= 4, .r= 0, .g= 0, .b= 0 }, // D
   { .x=13, .y= 1, .r= 0, .g= 0, .b= 0 }, // D
   { .x=13, .y= 4, .r= 0, .g= 0, .b= 0 }, // D
   { .x=14, .y= 2, .r= 0, .g= 0, .b= 0 }, // D
   { .x=14, .y= 3, .r= 0, .g= 0, .b= 0 }, // D
   { .x= 6, .y= 6, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 6, .y= 7, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 6, .y= 8, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 6, .y= 9, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 7, .y= 6, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 7, .y= 8, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 6, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 7, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 8, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 8, .y= 9, .r= 0, .g= 0, .b= 0 }, // A
   { .x= 3, .y=11, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 3, .y=12, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 3, .y=13, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 3, .y=14, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 4, .y=11, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 4, .y=13, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 5, .y=12, .r= 0, .g= 0, .b= 0 }, // P
   { .x= 7, .y=11, .r= 0, .g= 0, .b= 0 }, // I
   { .x= 7, .y=12, .r= 0, .g= 0, .b= 0 }, // I
   { .x= 7, .y=13, .r= 0, .g= 0, .b= 0 }, // I
   { .x= 7, .y=14, .r= 0, .g= 0, .b= 0 }, // I
   { .x= 9, .y=11, .r= 0, .g= 0, .b= 0 }, // C
   { .x= 9, .y=12, .r= 0, .g= 0, .b= 0 }, // C
   { .x= 9, .y=13, .r= 0, .g= 0, .b= 0 }, // C
   { .x= 9, .y=14, .r= 0, .g= 0, .b= 0 }, // C
   { .x=10, .y=11, .r= 0, .g= 0, .b= 0 }, // C
   { .x=10, .y=14, .r= 0, .g= 0, .b= 0 }, // C
   { .x=11, .y=11, .r= 0, .g= 0, .b= 0 }, // C
   { .x=11, .y=14, .r= 0, .g= 0, .b= 0 }  // C
};

#define SMILESIZE 40u
static const Frame_Pixel_t smileScreen[SMILESIZE] = {  // x,y,l,r,g,b
   { .x= 6, .y= 1, .r= 255, .g= 255, .b= 0 },
   { .x= 7, .y= 1, .r= 255, .g= 255, .b= 0 },
   { .x= 8, .y= 1, .r= 255, .g= 255, .b= 0 },
   { .x= 4, .y= 2, .r= 255, .g= 255, .b= 0 },
   { .x= 5, .y= 2, .r= 255, .g= 255, .b= 0 },
   { .x= 9, .y= 2, .r= 255, .g= 255, .b= 0 },
   { .x=10, .y= 2, .r= 255, .g= 255, .b= 0 },
   { .x= 3, .y= 3, .r= 255, .g= 255, .b= 0 },
   { .x=11, .y= 3, .r= 255, .g= 255, .b= 0 },
   { .x= 2, .y= 4, .r= 255, .g= 255, .b= 0 },
   { .x=12, .y= 4, .r= 255, .g= 255, .b= 0 },
   { .x= 2, .y= 5, .r= 255, .g= 255, .b= 0 },
   { .x= 5, .y= 5, .r= 255, .g= 255, .b= 0 },
   { .x= 9, .y= 5, .r= 255, .g= 255, .b= 0 },
   { .x=12, .y= 5, .r= 255, .g= 255, .b= 0 },
   { .x= 1, .y= 6, .r= 255, .g= 255, .b= 0 },
   { .x=13, .y= 6, .r= 255, .g= 255, .b= 0 },
   { .x= 1, .y= 7, .r= 255, .g= 255, .b= 0 },
   { .x=13, .y= 7, .r= 255, .g= 255, .b= 0 },
   { .x= 1, .y= 8, .r= 255, .g= 255, .b= 0 },
   { .x=13, .y= 8, .r= 255, .g= 255, .b= 0 },
   { .x= 2, .y= 9, .r= 255, .g= 255, .b= 0 },
   { .x= 5, .y= 9, .r= 255, .g= 255, .b= 0 },
   { .x= 9, .y= 9, .r= 255, .g= 255, .b= 0 },
   { .x=12, .y= 9, .r= 255, .g= 255, .b= 0 },
   { .x= 2, .y= 9, .r= 255, .g= 255, .b= 0 },
   { .x= 2, .y=10, .r= 255, .g= 255, .b= 0 },
   { .x= 6, .y=10, .r= 255, .g= 255, .b= 0 },
   { .x= 7, .y=10, .r= 255, .g= 255, .b= 0 }, 
   { .x= 8, .y=10, .r= 255, .g= 255, .b= 0 },
   { .x=12, .y=10, .r= 255, .g= 255, .b= 0 },
   { .x= 3, .y=11, .r= 255, .g= 255, .b= 0 },
   { .x=11, .y=11, .r= 255, .g= 255, .b= 0 },
   { .x= 4, .y=12, .r= 255, .g= 255, .b= 0 },
   { .x= 5, .y=12, .r= 255, .g= 255, .b= 0 },
   { .x= 9, .y=12, .r= 255, .g= 255, .b= 0 },
   { .x=10, .y=12, .r= 255, .g= 255, .b= 0 },
   { .x= 6, .y=13, .r= 255, .g= 255, .b= 0 },
   { .x= 7, .y=13, .r= 255, .g= 255, .b= 0 },
   { .x= 8, .y=13, .r= 255, .g= 255, .b= 0 }
};
   
#endif // __FRAME_TEMPLATES_H