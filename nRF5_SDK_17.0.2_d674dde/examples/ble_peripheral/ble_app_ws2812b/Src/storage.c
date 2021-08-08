// ****************************************************************************
/// \file      storage.c
///
/// \brief     Storage C Source File
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

// Include ********************************************************************
#include <stdio.h>
#include <string.h>
#include "fds.h"
#include "storage.h"

// Private define *************************************************************

// Private types     **********************************************************

// Private variables **********************************************************
/* Array to map FDS events to strings. */
static char const * fds_evt_str[] =
{
    "FDS_EVT_INIT",
    "FDS_EVT_WRITE",
    "FDS_EVT_UPDATE",
    "FDS_EVT_DEL_RECORD",
    "FDS_EVT_DEL_FILE",
    "FDS_EVT_GC",
};

// Keep track of the progress of a delete_all operation.
static struct
{
    bool delete_next;   //!< Delete next record.
    bool pending;       //!< Waiting for an fds FDS_EVT_DEL_RECORD event, to delete the next record.
} m_delete_all;

// Flag to check fds initialization.
static bool volatile m_fds_initialized;

// picture flash descriptor holding array and length
static picture_t pictureObj;

// A record containing dummy configuration data. 
static fds_record_t const m_picure_record =
{
    .file_id           = PICTURE_FILE,
    .key               = PICTURE_REC_KEY,
    .data.p_data       = &pictureObj,
    // The length of a record is always expressed in 4-byte units (words).
    .data.length_words = (sizeof(picture_t) + 3) / sizeof(uint32_t),
};

// Private function prototypes ************************************************
static   const char  *fds_err_str         ( ret_code_t ret );
static   void        fds_evt_handler      ( fds_evt_t const * p_evt );
static   void        delete_all_begin     ( void );
static   bool        record_delete_next   ( void );
static   void        delete_all_process   ( void );
static   void        wait_for_fds_ready   ( void );

// Global variables ***********************************************************

// Functions ******************************************************************
// ----------------------------------------------------------------------------
/// \brief     ...
///
/// \param     none
///
/// \return    none
static const char *fds_err_str(ret_code_t ret)
{
    /* Array to map FDS return values to strings. */
    static char const * err_str[] =
    {
        "FDS_ERR_OPERATION_TIMEOUT",
        "FDS_ERR_NOT_INITIALIZED",
        "FDS_ERR_UNALIGNED_ADDR",
        "FDS_ERR_INVALID_ARG",
        "FDS_ERR_NULL_ARG",
        "FDS_ERR_NO_OPEN_RECORDS",
        "FDS_ERR_NO_SPACE_IN_FLASH",
        "FDS_ERR_NO_SPACE_IN_QUEUES",
        "FDS_ERR_RECORD_TOO_LARGE",
        "FDS_ERR_NOT_FOUND",
        "FDS_ERR_NO_PAGES",
        "FDS_ERR_USER_LIMIT_REACHED",
        "FDS_ERR_CRC_CHECK_FAILED",
        "FDS_ERR_BUSY",
        "FDS_ERR_INTERNAL",
    };

    return err_str[ret - NRF_ERROR_FDS_ERR_BASE];
}

// ----------------------------------------------------------------------------
/// \brief     ...
///
/// \param     none
///
/// \return    none
static void fds_evt_handler(fds_evt_t const * p_evt)
{
    if (p_evt->result == NRF_SUCCESS)
    {

    }
    else
    {

    }

    switch (p_evt->id)
    {
        case FDS_EVT_INIT:
            if (p_evt->result == NRF_SUCCESS)
            {
                m_fds_initialized = true;
            }
            break;

        case FDS_EVT_WRITE:
        {
            if (p_evt->result == NRF_SUCCESS)
            {

            }
        } break;

        case FDS_EVT_DEL_RECORD:
        {
            if (p_evt->result == NRF_SUCCESS)
            {

            }
            m_delete_all.pending = false;
        } break;

        default:
            break;
    }
}

// ----------------------------------------------------------------------------
/// \brief     Begin deleting all records, one by one. 
///
/// \param     none
///
/// \return    none
static void delete_all_begin( void )
{
    m_delete_all.delete_next = true;
}

// ----------------------------------------------------------------------------
/// \brief     ...
///
/// \param     none
///
/// \return    none
static bool record_delete_next( void )
{
    fds_find_token_t  tok   = {0};
    fds_record_desc_t desc  = {0};

    if (fds_record_iterate(&desc, &tok) == NRF_SUCCESS)
    {
        ret_code_t rc = fds_record_delete(&desc);
        if (rc != NRF_SUCCESS)
        {
            return false;
        }

        return true;
    }
    else
    {
        /* No records left to delete. */
        return false;
    }
}

// ----------------------------------------------------------------------------
/// \brief     Wait for fds to be ready
///
/// \param     none
///
/// \return    none
static void wait_for_fds_ready( void )
{
    while (!m_fds_initialized)
    {
    }
}

// ----------------------------------------------------------------------------
/// \brief     Delete records, one by one, until no records are left.
///
/// \param     none
///
/// \return    none
void delete_all_process( void )
{
    if (   m_delete_all.delete_next
        & !m_delete_all.pending)
    {
        //Deleting next record
        m_delete_all.delete_next = record_delete_next();
        if (!m_delete_all.delete_next)
        {
            // No records left to delete.
        }
    }
}

// ----------------------------------------------------------------------------
/// \brief     Init storage.
///
/// \param     none
///
/// \return    none
void storage_init( void )
{
   ret_code_t rc;
   
    /* Register first to receive an event when initialization is complete. */
    ( void ) fds_register(fds_evt_handler);

    rc = fds_init();
    APP_ERROR_CHECK(rc);

    /* Wait for fds to initialize. */
    wait_for_fds_ready();
}

// ----------------------------------------------------------------------------
/// \brief     Load picture.
///
/// \param     [in]  uint8_t* picture
/// \param     [in]  uint16_t length
///
/// \return    Storage_StatusTypeDef
Storage_StatusTypeDef storage_loadPicture( uint8_t* picture, uint16_t length )
{
   ret_code_t rc;
   
   fds_stat_t stat = {0};
   
   rc = fds_stat(&stat);
   APP_ERROR_CHECK(rc);
   
   fds_record_desc_t desc = {0};
   fds_find_token_t  tok  = {0};
   
   rc = fds_record_find(PICTURE_FILE, PICTURE_REC_KEY, &desc, &tok);
   
   if( rc == NRF_SUCCESS )
   {
      /* A config file is in flash. Let's update it. */
      fds_flash_record_t config = {0};
   
      /* Open the record and read its contents. */
      rc = fds_record_open(&desc, &config);
      APP_ERROR_CHECK(rc);
      
      // copy picture structure from flash
      memcpy(&pictureObj, config.p_data, sizeof(picture_t));
   
      // check for correct picture length
      if( length != pictureObj.length )
      {
         return STORAGE_ERROR;
      }
      
      // copy picture data to local picture buffer
      memcpy(picture, pictureObj.data, length);
   
      /* Close the record when done reading. */
      rc = fds_record_close(&desc);
      APP_ERROR_CHECK(rc);
      
      return STORAGE_OK;
   }
   
   return STORAGE_ERROR;
}

// ----------------------------------------------------------------------------
/// \brief     Store picture.
///
/// \param     [in]  uint8_t* picture
/// \param     [in]  uint16_t length
///
/// \return    Storage_StatusTypeDef
Storage_StatusTypeDef storage_storePicture( uint8_t* picture, uint16_t length )
{
   ret_code_t rc;
   
   fds_stat_t stat = {0};
   
   uint8_t buffer[ROWS*COLS*3];
   
   rc = fds_stat(&stat);
   APP_ERROR_CHECK(rc);
   
   fds_record_desc_t desc = {0};
   fds_find_token_t  tok  = {0};
   
   rc = fds_record_find(PICTURE_FILE, PICTURE_REC_KEY, &desc, &tok);
   
   if( rc == NRF_SUCCESS )
   {
      /* A config file is in flash. Let's update it. */
      fds_flash_record_t config = {0};
      
      /* Open the record and read its contents. */
      rc = fds_record_open(&desc, &config);
      APP_ERROR_CHECK(rc);
      
      // copy picture structure from flash
      memcpy(&pictureObj, config.p_data, sizeof(picture_t));
      
      /* write into record */
      memcpy(pictureObj.data, picture, length);
      pictureObj.length = length;

      /* Close the record when done reading. */
      rc = fds_record_close(&desc);
      APP_ERROR_CHECK(rc);
      
      /* Write the updated record to flash. */
      rc = fds_record_update(&desc, &m_picure_record);
      APP_ERROR_CHECK(rc);
   }
   else
   {
      /* System config not found; write a new one. */
      memcpy(pictureObj.data, picture, length);
      pictureObj.length = length;
      rc = fds_record_write(&desc, &m_picure_record);
      APP_ERROR_CHECK(rc);
   }
   return STORAGE_OK;
}