/***************************************************************
 * Name:      vzsysex.h
 * Purpose:   Defines VZSysex class
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2019-01-10
 * Copyright: Brian Walton (riban.co.uk)
 * License:   GPL3
 **************************************************************/

#pragma once

#include "wx/wx.h"

#define VZ_HEADER_SIZE 7
#define VZ_HEADER {0xF0,0x44,0x03,0x00,0x70}
#define VZ_HEADER_CHANNEL 4
#define VZ_HEADER_TYPE 5
#define VZ_HEADER_SUBTYPE 6

wxDECLARE_EVENT(SYSEX_EVENT, wxCommandEvent);

/** Provides interface to VZ SysEx data
*   @note   Data is stored as raw SysEx data
*/
class VZSysex
{
public:
    /** @brief  Construct VZSysex object from existing SysEx data
    *   @param  nPayloadSize Quantity of bytes in payload
    *   @param  pData Pointer to a buffer containing raw SysEx operation data [default=null]
    *   @param  bPayload True if pData contains payload only (create default header and footer) [Default: false]
    *   @note   Initialises any invalid values to defaults and sets modified field
    */
    VZSysex(unsigned int nPayload, wxByte* pData = NULL, bool bPayload = false);

    /** @brief  Default destruct VZSysex object
    */
    virtual ~VZSysex();

    //!@todo implement copy operator

    /** @brief  Update sysex data with content of all abstract layers and fixes header
    *   @note   Virtual function must be implemented in derived classes
    */
    virtual void Update();

    /** @brief  Check if data has been changed since last validate / save (***which)
    *   @retval bool True if data has been modified
    */
    bool IsModified();

    /** @brief  Get the raw SysEx data
    *   @param  pData Pointer to buffer to store raw SyseEx data
    */
    void GetSysEx(wxByte* pData);

    /** @brief  Get the raw SysEx data
    *   @retval wxByte* Pointer to buffer with raw SyseEx data
    */
    wxByte* GetSysEx();

    /** @brief  Set the raw SysEx data
    *   @param  pData Pointer to a buffer containing raw SysEx operation data
    *   @param  bPayload True if data only contains payload - create default header [Default: false]
    *   @retval bool True if any data is invalid and initialised
    *   @note   Data is validated before populating the sysex data
    */
    bool SetSysEx(wxByte* pData, bool bPayload = false);

    /** @brief  Validate a single byte
    *   @param  pByte Pointer to the byte to validate
    *   @param  nByte Value to validate against
    *   @param  bFix True to correct invalid data
    *   @retval bool True if data invalid
    */
    bool ValidateByte(wxByte* pByte, wxByte nByte, bool bFix);

    /** @brief  Validates raw SysEx sysex data
    *   @param  bFix True to initialise invalid data
    *   @param  nSubheaderSize Quantity of bytes in message subheader [Default: 2]
    *   @param  bChecksum True if message has checksum as penultimate byte
    *   @retval bool True if data is valid
    */
    virtual bool Validate(bool bFix = false, unsigned int nSubheaderSize = 2, bool bChecksum = true);

    /** @brief  Validate data against checksum
    *   @param  pData Pointer to the data to validate
    *   @param  nSize Quantity of bytes to validate
    *   @param  nChecksum Checksum to validate [Default: 0 - calculate checksum]
    *   @retval wxByte Calculated value of checksum (zero if valid checksum)
    *   @note   Pass zero checksum to calculate a checksum. Pass a checksum to check data (zero return for valid data)
    */
    wxByte Checksum(wxByte* pData, unsigned int nSize, wxByte nChecksum = 0);

    /** @brief  Get the quantity of bytes in a SysEx message
    *   @param  bPayload True to get size of payload. False to get size of whole sysex message including header and footer [Default: false]
    *   @retval unsigned int Quantity of bytes
    */
    unsigned int GetSize(bool bPayload = false);

    /** @brief  Set filename
    *   @param  sFilename Absolute or relative filename
    */
    void SetFilename(wxString sFilename) { m_sFilename = sFilename; };

    /** @brief  Get filename
    *   @retval wxString Filename
    */
    wxString GetFilename() { return m_sFilename; };

    /** @brief  Create a zip archive of sysex data
    */
    void Archive();

    /** @brief  Set the object that will handle change of value events
    *   @param  pHandler Pointer to event handler
    */
    void SetEventHandler(wxEvtHandler* pHandler);

    /** @brief  Inhibit or allow events to be sent when values change
    *   @param  bInhibit True to inhibit events
    */
    void InhibitEvents(bool bInhibit = true);

protected:
    wxByte* m_pSysEx; //Raw sysex operation data
    unsigned int m_nPayloadSize; //Quantity of bytes in payload
    wxByte GetValue(unsigned int nOffset, wxByte nMask); //!< Helper function to get value from SysEx
    void SetValue(unsigned int nOffset, wxByte nMask, wxByte nValue); //!< Helper function to set value in SysEx
    wxByte DecodeByte(wxByte* pCursor); //!< Decodes 2 nibbles in separate bytes to single byte
    void EncodeByte(wxByte* pCursor, wxByte nValue); //!< Encodes byte to 2 nibbles in separate bytes
    wxByte GetByteFromSysex(unsigned int nOffset); //!< Decode a byte of data from the position in SysEx payload pointed to by cursor
    bool PutByteToSysex(unsigned int nOffset, wxByte nValue); //!< Encode a byte of data into position in SysEx payload pointed to by cursor
    bool m_bModified; //True if any fields have changed since last validate / save ***We don't really mean save
    void SendEvent(); // Send an event to indicate a parameter has changed

private:
    wxString m_sFilename; //Filename of last file loaded into saved from this voice
    wxEvtHandler* m_pEventHandler = NULL; //Pointer to a handler for change events
    bool m_bInhibitEvent = false; //True to inhibit sending events on value change
};
