/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/*** INCLUDED COMPONENTS ***/
#include "spi_protocol.h"
#include "fifo_rx.h"

/*** VARIABLES ***/

/*** FUNCTIONS ***/
void spi_write(uint8 address, uint8 data){
    address = address & 0x7F;       // Clear the first bit of the address
    
    CS_Write(0);     
    DELAY;
    SPIM_WriteTxData(address);      // Writing Routune 
    SPIM_WriteTxData(data);   
    DELAY;
    CS_Write(1);
}

uint8 spi_request(uint8 address){
    uint8 data = 0;
    address = address | 0x80;       // Set the first bit of the address
    
    for (uint8 i = 0; i < 2; i++){  // The first 3 bytes received are trash 
        CS_Write(0);   
        DELAY;
        SPIM_WriteTxData(address);  // Write Read command + Address
        SPIM_WriteTxData(0);        // Write null byte
        
        SPIM_ReadRxData();          // Reading Routine
        data = SPIM_ReadRxData();   // Just the 4th byte requested is of interest
        DELAY;
        CS_Write(1);
    }
    
    return data;
}

/*** INTERRUPTS ***/

/* [] END OF FILE */
