// ****************************************************************************
/// \file      bleapp_services.h
///
/// \brief     BLE uv curer services C Header File
///
/// \details   BLE uv curer services C Header File
///
/// \author    Nico Korn
///
/// \version   0.1.0.0
///
/// \date      14042021
/// 
/// \copyright Copyright (C) 2021  by "Reichle & De-Massari AG", 
///            all rights reserved.
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
#ifndef __BLEAPP_SERVICES_H
#define __BLEAPP_SERVICES_H

// Include ********************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

// Exported defines ***********************************************************
/**@brief   Macro for defining a ble_lbs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_WS2812B_DEF(_name)                     \
static ble_ws2812b_service_t _name;                \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                \
                     BLE_LBS_BLE_OBSERVER_PRIO,    \
                     bleapp_services_ws2812b_evt, &_name)

#define UUID_BASE                   {0xbc, 0x51, 0xcc, 0xb1, 0xa3, 0x1e, 0xd9, 0xa3, \
                                    0x40, 0xbc, 0x36, 0x79, 0xc3, 0x7d, 0xbf, 0xa2} // 128-bit base UUID

#define UUID_WS2812B_SERVICE        0x1001
#define UUID_WS2812B_CMD_CHAR       0x1002
#define UUID_WS2812B_ROW_CHAR       0x1003
#define UUID_WS2812B_COL_CHAR       0x1004
#define UUID_WS2812B_PIXEL_CHAR     0x1005
#define UUID_WS2812B_PICTURE_CHAR   0x1006

#define UUID_UC_SERVICE             0x2001
#define UUID_UC_VOLTAGE_CHAR        0x2002
#define UUID_UC_TEMPERATURE_CHAR    0x2003

// Exported types *************************************************************

// Exported functions *********************************************************
void bleapp_services_init ( void );

// Forward declaration of the ble_lbs_t type.
typedef struct ble_ws2812b_service_s ble_ws2812b_service_t;

typedef void (*ble_ws2812b_evt_handler_t) (uint16_t conn_handle, ble_ws2812b_service_t * p_lbs, uint8_t new_state);

/** @brief LED Button Service init structure. This structure contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_ws2812b_evt_handler_t ws2812b_evt_handler; /**< Event handler to be called when the LED Characteristic is written. */
} ble_ws2812b_init_t;

/**@brief UV Service structure. This structure contains various status information for the uv service. */
struct ble_ws2812b_service_s
{
   uint16_t                      service_handle;         /**< Handle of Device Service (as provided by the BLE stack). */
   ble_gatts_char_handles_t      cmd_char_handles;       /**< Handles related to command Characteristic. */
   ble_gatts_char_handles_t      row_char_handles;       /**< Handles related to led row Characteristic. */
   ble_gatts_char_handles_t      col_char_handles;       /**< Handles related to column Characteristic. */
   ble_gatts_char_handles_t      pixel_char_handles;     /**< Handles related to column Characteristic. */
   ble_gatts_char_handles_t      picture_char_handles;   /**< Handles related to data Characteristic. */
   uint8_t                       uuid_type;              /**< UUID type for the ws2812b controller Service. */
   ble_ws2812b_evt_handler_t     ws2812b_evt_handler;    /**< Event handler to be called when the UV LED Characteristic is written. */
};


/**@brief Function for initializing the LED Button Service.
 *
 * @param[out] p_lbs      LED Button Service structure. This structure must be supplied by
 *                        the application. It is initialized by this function and will later
 *                        be used to identify this particular service instance.
 * @param[in] p_lbs_init  Information needed to initialize the service.
 *
 * @retval NRF_SUCCESS If the service was initialized successfully. Otherwise, an error code is returned.
 */
uint32_t bleapp_services_ws2812b( ble_ws2812b_service_t * p_lbs, const ble_ws2812b_init_t * p_lbs_init );


/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the LED Button Service.
 *
 * @param[in] p_ble_evt  Event received from the BLE stack.
 * @param[in] p_context  LED Button Service structure.
 */
void bleapp_services_ws2812b_evt( ble_evt_t const * p_ble_evt, void * p_context );


/**@brief Function for sending a button state notification.
 *
 ' @param[in] conn_handle   Handle of the peripheral connection to which the button state notification will be sent.
 * @param[in] p_lbs         LED Button Service structure.
 * @param[in] button_state  New button state.
 *
 * @retval NRF_SUCCESS If the notification was sent successfully. Otherwise, an error code is returned.
 */
uint32_t bleapp_services_on_button_change (uint16_t conn_handle, ble_ws2812b_service_t * p_lbs, uint8_t button_state);
uint32_t bleapp_services_setCharNotify    (uint16_t conn_handle, uint16_t value_handle, uint8_t* data, uint16_t len );
uint32_t bleapp_services_setChar          (uint16_t conn_handle, uint16_t value_handle, uint8_t* data, uint16_t len );

#endif // __BLEAPP_SERVICES_H