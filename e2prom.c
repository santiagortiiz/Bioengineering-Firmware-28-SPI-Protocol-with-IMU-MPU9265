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
#include "e2prom.h"
#include "uart_communication.h"
#include "interface.h"
#include "fifo_rx.h"

#include <stdio.h>

/*** VARIABLES ***/
uint8 amount_of_saved_values = 0;
char identifier[8];                               // Select mean or std each byte
uint8 location = 0x0;     
static uint16 StatisticsCounter;                          

/*** FUNCTIONS ***/
void E2PROM_writeFIFOStatistics(void){
    CLEAN_BUFFER;
    sprintf(buffer, "%.1f", FIFOrx_GetMean(FIFO_SIZE));
    for(uint8 i = 0; i < 8; i++){                   // Get the mean of all data in the FIFO
        EEPROM_WriteByte(buffer[i], location);      // and store it in the char buffer.
        location++;                                 // Each byte of the buffer is saved in the EEPROM
    }
    CLEAN_BUFFER;
    sprintf(buffer, "%.1f", FIFOrx_GetStandardDeviation(FIFO_SIZE));
    for(uint8 i = 0; i < 8; i++){                   // Get the std of all data in the FIFO
        EEPROM_WriteByte(buffer[i], location);      // and store it in the char buffer.
        location++;                                 // Then each byte of the buffer is saved in the EEPROM
    }
    EEPROM_WriteByte(location, LAST_LOCATION);      // The last memory address used is saved
    
    StatisticsCounter++;                            // Count how many times the FIFO get full
    CLEAN_BUFFER;
    sprintf(buffer, "%u", StatisticsCounter);       // Show FIFO_dataFullCounter
    MenuUART(FIFO_FULL_COUNTER);                           
}

void E2PROM_readFIFOStatistics(void){
    uint8 i;                                        // Iterate over the memory locations
    uint8 j = 0;                                    // Iterate over the buffer byte
    uint8 k = 0;                                    // Validate if is mean or std
    uint8 values_counter = 1;
    
    for(i = 0x0; i < amount_of_saved_values; i++){  // walk through the memory positions reading
        buffer[j] = EEPROM_ReadByte(i);             // each value and assign it to the buffer byte
        j++;        
        if (j == 8){                                // When the buffer is full, show it in the console
            j = 0;                                  // with an identifier
            k = !k;
            sprintf(identifier, "%u)", values_counter);
            if (k == 1){
                MenuUART(MEAN_MENU);                   
            }
            else if (k == 0){
                MenuUART(STD_MENU);                       
                values_counter++;
            }
        }
        
    }
    
}

/*** INTERRUPTS ***/

/* [] END OF FILE */
