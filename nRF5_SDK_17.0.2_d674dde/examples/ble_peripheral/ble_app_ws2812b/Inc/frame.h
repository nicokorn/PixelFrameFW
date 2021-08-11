// ****************************************************************************
/// \file      frame.h
///
/// \brief     Frame C Header File
///
/// \details   The frame source files abstracts a frame using the ws2812b library.
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
#ifndef __FRAME_H
#define __FRAME_H

// Include ********************************************************************
#include "nrf.h"
#include "stdbool.h"
#include "ws2812b.h"
#include "bleapp_services.h"

// Exported defines ***********************************************************
#define ROWS   15
#define COLS   15

// Exported types *************************************************************
typedef struct Frame_HandleTypeDef_s
{
   uint16_t                   rows;
   uint16_t                   cols;
   WS2812B_HandleTypeDef_t*   ws2812b;
   bool                       bleServices;
   bool                       sendBuffer;
   uint16_t*                  bleConnHandle;
   ble_ws2812b_service_t*     bleServicesObj;   
}Frame_HandleTypeDef_t;

typedef struct Frame_Pixel_s
{
   int16_t                    x;
   int16_t                    y;
   uint8_t                    r;
   uint8_t                    g;
   uint8_t                    b;
}Frame_Pixel_t;

// Exported functions *********************************************************
void     frame_init                 ( Frame_HandleTypeDef_t *frame_instance );
void     frame_sendBuffer           ( void );
void     frame_clearBuffer          ( void );
void     frame_setPixel             ( uint16_t col, uint16_t row, uint8_t red, uint8_t green, uint8_t blue );
uint16_t frame_getRowCount          ( void );
uint16_t frame_getColCount          ( void );
uint8_t* frame_getBuffer            ( void );
void     frame_task                 ( void );
void     frame_reqSendBuffer        ( void );
void     frame_loadPicture          ( void );
void     frame_storePicture         ( void );
void     frame_splashScreenMatrix   ( void );
void     frame_splashScreenSpiral   ( void );
void     frame_loadScreen           ( void );
void     frame_smileScreen          ( void );
void     frame_getPixel             ( uint16_t col, uint16_t row, uint8_t *red, uint8_t *green, uint8_t *blue );
void     frame_fadingOut            ( void );
#endif // __FRAME_H__FRAME_H