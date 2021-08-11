// ****************************************************************************
/// \file      ws2812b.h
///
/// \brief     WS2812B C HeaderFile
///
/// \details   Driver Module for WS2812B leds.
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
#ifndef __WS2812B_H
#define __WS2812B_H

// Include ********************************************************************
#include "nrf.h"

// Exported defines ***********************************************************
#define PIXEL_COUNTMAX           ( 1024u )
#define PIXEL_BIT_SIZE           ( 24u )

//#define ONBOARD_LED   // used if a ws2812b led stripe is attached to GPIO Port 0, Pin 16
#define STRIPE_LED   // used if a ws2812b led stripe is attached to GPIO Port 0, Pin 4

#ifdef STRIPE_LED
#define PIXEL_COUNT              ( 225u )
#define WS2812B_PIN              ( 4u )
#define WS2812B_PORT             ( 0u )
#endif

#ifdef ONBOARD_LED
#define PIXEL_COUNT              ( 1u )
#define WS2812B_PIN              ( 16u )
#define WS2812B_PORT             ( 0u )
#endif

// Exported types *************************************************************
typedef enum
{
   WS2812B_OK       = 0x00U,
   WS2812B_ERROR    = 0x01U,
   WS2812B_BUSY     = 0x02U,
   WS2812B_TIMEOUT  = 0x03U,
   WS2812B_READY    = 0x04U,
   WS2812B_RESET    = 0x05U
} WS2812B_StatusTypeDef;

typedef struct WS2812B_HandleTypeDef_s
{
   uint16_t                pixelcount;
   uint8_t*                pixelbuffer;
   WS2812B_StatusTypeDef   state;
}WS2812B_HandleTypeDef_t;

typedef struct WS2812B_Pixel_s
{
   uint16_t                   pixelnr;
   uint8_t                    r;
   uint8_t                    g;
   uint8_t                    b;
}WS2812B_Pixel_t;

// Exported functions *********************************************************
WS2812B_StatusTypeDef   WS2812B_init            ( WS2812B_HandleTypeDef_t *ws2812b_instance );
void                    WS2812B_sendBuffer      ( WS2812B_HandleTypeDef_t *ws2812b_instance );
void                    WS2812B_clearBuffer     ( WS2812B_HandleTypeDef_t *ws2812b_instance );
void                    WS2812B_setPixel        ( WS2812B_HandleTypeDef_t *ws2812b_instance, uint16_t pixel_pos, uint8_t red, uint8_t green, uint8_t blue );
void                    WS2812B_getPixel        ( WS2812B_HandleTypeDef_t *ws2812b_instance, uint16_t *pixel_pos, uint8_t *red, uint8_t *green, uint8_t *blue );
#endif // __WS2812B_H