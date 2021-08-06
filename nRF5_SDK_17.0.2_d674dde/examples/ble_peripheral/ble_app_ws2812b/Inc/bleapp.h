// ****************************************************************************
/// \file      bleapp.h
///
/// \brief     Bleapp C Header File
///
/// \details   Bluetooth low energy application level file.
///
/// \author    Nico Korn
///
/// \version   0.1.0.0
///
/// \date      14042021
/// 
/// \copyright Copyright (C) 2021  by Nico Korn
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
#ifndef __BLEAPP_H
#define __BLEAPP_H

// Include ********************************************************************

// Exported defines ***********************************************************

// Exported types *************************************************************

// Exported functions *********************************************************
void                    bleapp_init          ( void );
uint16_t*               bleapp_getConnHandle ( void );
ble_ws2812b_service_t*  bleapp_getServiceObj ( void );
#endif // __BLEAPP_H