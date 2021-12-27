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

#ifndef SPI_PROTOCOL_H
    #define SPI_PROTOCOL_H
    
    #include "project.h"

    /*** MACROS ***/
    #define DELAY CyDelay(1)
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    
    /*** FUNCTION PROTOTYPES ***/
    void spi_write(uint8 address, uint8 data);
    uint8 spi_request(uint8 address);
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
