// ****************************************************************************
/// \file      storage.c
///
/// \brief     Storage C Header File
///
/// \details   Using nordic fds module to store pictures on the internal flash.
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
#ifndef __STORAGE_H
#define __STORAGE_H

// Include ********************************************************************
#include "nrf.h"
#include "frame.h"

// Exported defines ***********************************************************
#define PICTURE_FILE     (0x8010)
#define PICTURE_REC_KEY  (0x7010)

// Exported types *************************************************************
/* A dummy structure to save in flash. */
typedef struct
{
    uint32_t boot_count;
    char     device_name[16];
    bool     config1_on;
    bool     config2_on;
} configuration_t;

/* The frame picture to save in flash. */
typedef struct
{
   uint8_t  data[ROWS*COLS*3];
   uint16_t length;
} picture_t;

typedef enum
{
   STORAGE_OK       = 0x00U,
   STORAGE_ERROR    = 0x01U
} Storage_StatusTypeDef;

// Exported functions *********************************************************
void storage_init          ( void );
Storage_StatusTypeDef storage_loadPicture   ( uint8_t* picture, uint16_t length );
Storage_StatusTypeDef storage_storePicture  ( uint8_t* picture, uint16_t length );

#endif // __STORAGE_H