// ****************************************************************************
/// \file      bleapp_services.c
///
/// \brief     BLE uv curer services C Source File
///
/// \details   BLE uv curer services C Source File
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

// Include ********************************************************************
#include <stdbool.h>
#include "nrf.h"
#include "bleapp_services.h"
#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "sdk_common.h"
#include "frame.h"
#include "ws2812b.h"

// Private define *************************************************************

// Private types     **********************************************************

// Private variables **********************************************************
static uint8_t blePicBuffer[MAX_BLE_SIZE];

// Private function prototypes ************************************************
static void on_write( ble_ws2812b_service_t * p_lbs, ble_evt_t const * p_ble_evt );

// Functions ******************************************************************
// ----------------------------------------------------------------------------
/// \brief     Init the uv curer services and characteristics
///
/// \param     none
///
/// \return    none
void bleapp_services_init( void )
{

}

void bleapp_services_ws2812b_evt( ble_evt_t const * p_ble_evt, void * p_context )
{
    ble_ws2812b_service_t * p_lbs = (ble_ws2812b_service_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTS_EVT_WRITE:
            on_write( p_lbs, p_ble_evt );
            break;

        default:
            // No implementation needed.
            break;
    }
}

// ----------------------------------------------------------------------------
/// \brief     Function for handling the Write event.
///
/// \param     [in] p_lbs      Service structure.
/// \param     [in] p_ble_evt  Event received from the BLE stack.
///
/// \return    none
static void on_write( ble_ws2812b_service_t * p_lbs, ble_evt_t const * p_ble_evt )
{
   ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

   if(   (p_evt_write->handle == p_lbs->cmd_char_handles.value_handle)
      && (p_evt_write->len == 1))
   {
      
   }
   else if( (p_evt_write->handle == p_lbs->pixel_char_handles.value_handle)
      && (p_evt_write->len == 7) )
   {
      uint16_t col = *(uint16_t*)&p_evt_write->data[0];
      uint16_t row = *(uint16_t*)&p_evt_write->data[2];
      uint8_t r = p_evt_write->data[4];
      uint8_t g = p_evt_write->data[5];
      uint8_t b = p_evt_write->data[6];
      frame_setPixel( col, row, r, g, b );
      frame_reqSendBuffer();
   }
   else if( (p_evt_write->handle == p_lbs->picture_char_handles.value_handle) )
   {
      on_char_picture( p_evt_write->data );
   }
}

// ----------------------------------------------------------------------------
/// \brief     Function for handling the picture write event.
///
/// \param     [in] uint8_t *dPointer
///
/// \return    none
void on_char_picture( const uint8_t *dPointer )
{
   // get offset and size
   //uint16_t offset = *(uint16_t*)&blePicBuffer[0];
   //uint16_t size = *(uint16_t*)&blePicBuffer[2];
   uint16_t i,j;
   uint16_t offset = *(uint16_t*)&dPointer[0];
   uint16_t size = *(uint16_t*)&dPointer[2];
   uint16_t col = 0;
   uint16_t row = 0;
   uint16_t pixelPacketSize = size/3;
   uint16_t pixelOffset = offset/3;
   uint8_t  cmdField = dPointer[4];
   
   for( uint16_t pixel = 0; pixel < pixelPacketSize; pixel++ )
   {
      // calculate coordinates
      row = ( pixel + pixelOffset )/frame_getRowCount();
      col = ( pixel +  pixelOffset )%frame_getRowCount();
      
      // write rgb at coordinates
      if(row<=frame_getRowCount())
      {
         //frame_setPixel( col, row, blePicBuffer[i+PICTURE_HEADER_OFFSET], blePicBuffer[i+PICTURE_HEADER_OFFSET+1], blePicBuffer[i+PICTURE_HEADER_OFFSET+2] );
         frame_setPixel( col, row, dPointer[(pixel*3)+PICTURE_HEADER_OFFSET], dPointer[(pixel*3)+PICTURE_HEADER_OFFSET+1], dPointer[(pixel*3)+PICTURE_HEADER_OFFSET+2] );
      }
   }
   
   if( (cmdField & CMD_BIT_REFRESH) == CMD_BIT_REFRESH )
   {
      frame_reqSendBuffer();
   }
}

// ----------------------------------------------------------------------------
/// \brief     Function to add service and characteristics
///
/// \param     [in] p_lbs        Service structure.
/// \param     [in] p_lbs_init 
///
/// \return    err_code
uint32_t bleapp_services_ws2812b( ble_ws2812b_service_t * p_lbs )
{
   uint32_t              err_code;
   ble_uuid_t            ble_uuid;
   ble_add_char_params_t add_char_params;

   // Add service.
   ble_uuid128_t base_uuid      = UUID_BASE;
   err_code                     = sd_ble_uuid_vs_add( &base_uuid, &p_lbs->uuid_type );
   VERIFY_SUCCESS(err_code);
   
   ble_uuid.type                = p_lbs->uuid_type;
   ble_uuid.uuid                = UUID_WS2812B_SERVICE;
   
   err_code = sd_ble_gatts_service_add( BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_lbs->service_handle );
   VERIFY_SUCCESS(err_code);
   
   // Add command characteristic.
   memset(&add_char_params, 0, sizeof(add_char_params));
   add_char_params.uuid             = UUID_WS2812B_CMD_CHAR;
   add_char_params.uuid_type        = p_lbs->uuid_type;
   add_char_params.init_len         = sizeof(uint8_t);
   add_char_params.max_len          = sizeof(uint8_t);
   add_char_params.char_props.read  = 1;
   add_char_params.char_props.write = 1;
   
   add_char_params.read_access      = SEC_OPEN;
   add_char_params.write_access     = SEC_OPEN;
   
   err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->cmd_char_handles);
   
   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }
   
   // Add row characteristic.
   memset(&add_char_params, 0, sizeof(add_char_params));
   add_char_params.uuid                = UUID_WS2812B_ROW_CHAR;
   add_char_params.uuid_type           = p_lbs->uuid_type;
   add_char_params.init_len            = sizeof(uint16_t);
   add_char_params.max_len             = sizeof(uint16_t);
   add_char_params.char_props.read     = 1;
   add_char_params.char_props.notify   = 1;
   
   add_char_params.read_access         = SEC_OPEN;
   add_char_params.cccd_write_access   = SEC_OPEN;
   
   err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->row_char_handles);
   
   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }
   
   // Add col characteristic.
   memset(&add_char_params, 0, sizeof(add_char_params));
   add_char_params.uuid                = UUID_WS2812B_COL_CHAR;
   add_char_params.uuid_type           = p_lbs->uuid_type;
   add_char_params.init_len            = sizeof(uint16_t);
   add_char_params.max_len             = sizeof(uint16_t);
   add_char_params.char_props.read     = 1;
   add_char_params.char_props.notify   = 1;
   
   add_char_params.read_access         = SEC_OPEN;
   add_char_params.cccd_write_access   = SEC_OPEN;
   
   err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->col_char_handles);
   
   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }
   
   // Add pixel characteristic.
   memset(&add_char_params, 0, sizeof(add_char_params));
   add_char_params.uuid                = UUID_WS2812B_PIXEL_CHAR;
   add_char_params.uuid_type           = p_lbs->uuid_type;
   add_char_params.init_len            = 7; // 2(row), 2(col), 3(rgb)
   add_char_params.max_len             = 7;
   add_char_params.char_props.read     = 1;
   add_char_params.char_props.write    = 1;
   
   add_char_params.read_access         = SEC_OPEN;
   add_char_params.write_access        = SEC_OPEN;
   
   err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->pixel_char_handles);
   
   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }
   
   // Add pixel characteristic.
   memset(&add_char_params, 0, sizeof(add_char_params));
   add_char_params.uuid                = UUID_WS2812B_PICTURE_CHAR;
   add_char_params.uuid_type           = p_lbs->uuid_type;
   add_char_params.init_len            = 510;
   add_char_params.max_len             = 510;
   add_char_params.char_props.read     = 1;
   add_char_params.char_props.write    = 1;
   
   add_char_params.read_access         = SEC_OPEN;
   add_char_params.write_access        = SEC_OPEN;
   
   err_code = characteristic_add(p_lbs->service_handle, &add_char_params, &p_lbs->picture_char_handles);
   
   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }

   if (err_code != NRF_SUCCESS)
   {
      return err_code;
   }

   return err_code;
}

uint32_t bleapp_services_setCharNotify( uint16_t conn_handle, uint16_t value_handle, uint8_t* data, uint16_t len )
{
    ble_gatts_hvx_params_t params;

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = value_handle;
    params.p_data = data;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}

uint32_t bleapp_services_setChar( uint16_t conn_handle, uint16_t value_handle, uint8_t* data, uint16_t len )
{
    ble_gatts_hvx_params_t params;

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_INDICATION;
    params.handle = value_handle;
    params.p_data = data;
    params.p_len  = &len;

    return sd_ble_gatts_hvx(conn_handle, &params);
}