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
#include "digital_pot.h"

/*** VARIABLES ***/
static uint16 output_data = 0;
static uint8 output_ready = 0;
uint16 MCP_414X_data = 0;

/*** FUNCTIONS ***/
void digital_pot_adjust(uint8 input_data){
    if (output_data == 0){
        output_ready++;
        output_data = (uint16) input_data;
    }
    else if (output_ready == 1){
        output_data = output_data << 8 | (uint16) input_data;
        output_ready = 0;
        spi_digital_pot_comunication(output_data);
    }
}

void spi_digital_pot_comunication(uint16 input_data){
    output_ready = 0;
    uint16 action = 0;
    action = input_data & 0b0000110000000000;
    if (action != 0xC00){
        SPIM_R_WriteTxData(input_data);
    }
    else {
        SPIM_R_WriteTxData(input_data);
        MCP_414X_data = SPIM_R_ReadRxData();
    }
}

/*
Bytes: Address (4) + Command (2) + XX (2) + Data N (8)
00 = escritura de dato
01 = incrementar
10 = decrementar
11 = lectura de dato
*/

/*** INTERRUPTS ***/

/* [] END OF FILE */
