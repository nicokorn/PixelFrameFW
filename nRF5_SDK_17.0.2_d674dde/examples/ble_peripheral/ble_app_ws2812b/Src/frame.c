// ****************************************************************************
/// \file      frame.c
///
/// \brief     Frame C Source File
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

// Include ********************************************************************
#include <stdio.h>
#include <string.h>
#include "frame.h"
#include "nrf_drv_pwm.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "bleapp.h"
#include "ws2812b.h"
#include "storage.h"


// Private define *************************************************************

// Private types     **********************************************************

// Private variables **********************************************************
static Frame_HandleTypeDef_t     *frame_core;

// Private function prototypes ************************************************

// Global variables ***********************************************************

// Functions ******************************************************************

// ----------------------------------------------------------------------------
/// \brief     Initialisation of the frame.
///
/// \param     [in]  WS2812B_HandleTypeDef_t *ws2812b_instance
/// \param     [in]  Frame_HandleTypeDef_t *frame_instance
///
/// \return    none
void frame_init( Frame_HandleTypeDef_t *frame_instance )
{
   // check for led consistency
   if( frame_instance->ws2812b->pixelcount != frame_instance->rows * frame_instance->cols )
   {
     // error: stay here, implement an error handler
     // pixelcount is not inline with the amount of columns and rows
     while(1);
   } 

   frame_core = frame_instance;
   frame_core->sendBuffer = false;
   
   if( frame_core->bleServices == true )
   {
      bleapp_init();
      frame_core->bleConnHandle = bleapp_getConnHandle();
      frame_core->bleServicesObj = bleapp_getServiceObj();
   }
   
   // initialise the fds module
   storage_init();
}

// ----------------------------------------------------------------------------
/// \brief     Send buffer to the frame.
///
/// \param     none
///
/// \return    none
void frame_sendBuffer( void )
{
   WS2812B_sendBuffer( frame_core->ws2812b );
}

// ----------------------------------------------------------------------------
/// \brief     Clear frame buffer. All pixels are black after sending.
///
/// \param     none
///
/// \return    none
void frame_clearBuffer( void )
{
   for( uint16_t y=0; y<frame_core->rows; y++ )
   {
      for( uint16_t x=0; x<frame_core->cols; x++ )
      {
         frame_setPixel( x, y, 0x00, 0x00, 0x00 );
      }
   }
   frame_storePicture();
}

// ----------------------------------------------------------------------------
/// \brief     Set a pixel in the buffer. Note you need to send the buffer
///            so the buffer is visible on the frame.
///
/// \param     [in]  uint16_t col
/// \param     [in]  uint16_t row
/// \param     [in]  uint8_t red
/// \param     [in]  uint8_t green
/// \param     [in]  uint8_t blue
///
/// \return    none
void frame_setPixel( uint16_t col, uint16_t row, uint8_t red, uint8_t green, uint8_t blue )
{
   // check for led consistency
   if( col >= frame_core->cols || row >= frame_core->rows )
   {
      // error: stay here, implement an error handler
      return;
   }
   
   // calculate the pixelnumber on the stream with col and row coordinates
   uint16_t pixelnumber=0;
   if(row%2==0)
   {
     pixelnumber = (row*frame_core->cols) + col;
   }
   else
   {
     pixelnumber = (row*frame_core->cols) + (frame_core->cols-col);
     pixelnumber--;
   }
   
   // set the pixel in the ws2812b pixel buffer
   WS2812B_setPixel( frame_core->ws2812b, pixelnumber, red, green, blue );
   
  // if ble service has been loaded write pixel data also into the service
  if( frame_core->bleServices != false )
  {
     bleapp_services_setPagePixel( frame_core->bleConnHandle, frame_core->bleServicesObj, (row*frame_core->cols) + col, red, green, blue );
  }
}

// ----------------------------------------------------------------------------
/// \brief     Returns number of rows.
///
/// \param     none
///
/// \return    uint16_t rows
uint16_t frame_getRowCount( void )
{
  return frame_core->rows;
}

// ----------------------------------------------------------------------------
/// \brief     Returns number of cols.
///
/// \param     none
///
/// \return    uint16_t cols
uint16_t frame_getColCount( void )
{
  return frame_core->cols;
}

// ----------------------------------------------------------------------------
/// \brief     Returns pointer to ws2812b buffer.
///
/// \param     none
///
/// \return    uint8_t* pixelbuffer
uint8_t* frame_getBuffer( void )
{
  return frame_core->ws2812b->pixelbuffer;
}

// ----------------------------------------------------------------------------
/// \brief     Frame task used to send the buffer to the frame triggered by
///            a flag.
///
/// \param     none
///
/// \return    none
void frame_task( void )
{
   if( frame_core->sendBuffer != false )
   {
      frame_sendBuffer();
      frame_core->sendBuffer = false;
   }
}

// ----------------------------------------------------------------------------
/// \brief     Set buffer flag to send the buffer to the frame in the frame_task
///            function.
///
/// \param     none
///
/// \return    none
void frame_reqSendBuffer( void )
{
   frame_core->sendBuffer = true;
}

// ----------------------------------------------------------------------------
/// \brief     Checks internal flash storage for stored pictures for last
///            boot cycles.
///
/// \param     none
///
/// \return    none
void frame_loadPicture( void )
{
   uint8_t buffer[ROWS*COLS*3];
   uint16_t counter = 0;
   if( storage_loadPicture( buffer, ROWS*COLS*3 ) != STORAGE_ERROR )
   {
      for( uint16_t y=0; y<frame_core->rows; y++ )
      {
         for( uint16_t x=0; x<frame_core->cols; x++ )
         {
            frame_setPixel( x, y, buffer[counter], buffer[counter+1], buffer[counter+2] );
            counter += 3;
            if( counter > ROWS*COLS*3 )
            {
               frame_clearBuffer();
               frame_reqSendBuffer();
               return;
            }
         }
      }
   }
   else
   {
      frame_clearBuffer();
      frame_reqSendBuffer();
   }
   frame_reqSendBuffer();
}

// ----------------------------------------------------------------------------
/// \brief     Stores current picture on the frame into the internal flash
///
/// \param     none
///
/// \return    none
void frame_storePicture( void )
{
   uint8_t buffer[ROWS*COLS*3];
   uint8_t counter = 0;
   
   // get the picture stored in the ble service
   bleapp_services_getPicture( frame_core->bleConnHandle, frame_core->bleServicesObj, buffer, ROWS*COLS*3 );
   
   // store the picture into internal flash
   storage_storePicture( buffer, ROWS*COLS*3 );
}