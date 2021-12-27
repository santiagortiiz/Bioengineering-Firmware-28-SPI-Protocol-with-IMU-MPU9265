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

#ifndef DIGITAL_POT_H
    #define DIGITAL_POT_H
    
    #include "project.h"

    /*** MACROS ***/
    #define UP 0
    #define DOWN 1
    #define WIPER_SELECT 2
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    void digital_pot_adjust(uint8 input_data);
    void spi_digital_pot_comunication(uint16 input_data);
    
    /*** FUNCTION PROTOTYPES ***/
    extern uint16 MCP_414X_data;
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
