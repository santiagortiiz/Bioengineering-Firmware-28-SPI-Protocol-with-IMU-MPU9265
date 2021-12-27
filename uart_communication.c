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
#include "uart_communication.h"
#include "chronometer.h"
#include "interface.h"
#include "keyboard.h"
#include "mpu9265.h"
#include "fifo_rx.h"
#include "e2prom.h"

#include <stdio.h>

/*** VARIABLES ***/
uint8 python_sync_up = 0;
char buffer[8];
uint8 new_uart_data = 0;
uint8 uart_data = 0;

/*** FUNCTIONS ***/
void userRequest(uint8 query){                              // Do a task depending on the 
    switch(query){                                          // received message from the user
        case 'A':
            key = 'A';
            MenuUART(CONFIRM_RECEPTION);
            python_sync_up = 1;
            ms = 0;
            break;
        case 'B':
            key = 'B';
            MenuUART(CONFIRM_RECEPTION);
            python_sync_up = 1;
            ms = 0;
            break;
        case 'C':
            key = 'C';
            MenuUART(CONFIRM_RECEPTION);
            python_sync_up = 1;
            ms = 0;
            break;
        case 'S':
            key = 0;
            python_sync_up = 0;
            break;
        
        case SENSOR_REFERENCE:                                             
            MenuUART(SENSOR_REFERENCE_MENU);
            break;
        case SENSOR_RESOLUTION:                                             
            mpu9265_GetAccelResolution(&accel_resolution);
            CLEAN_BUFFER;
            sprintf(buffer, "%8u", accel_resolution);
            MenuUART(ACCEL_RESOLUTION_MENU);
            mpu9265_GetGyroResolution(&gyro_resolution);   
            CLEAN_BUFFER; 
            sprintf(buffer, "%8u", gyro_resolution);
            MenuUART(GYRO_RESOLUTION_MENU);
            break;
        case SAMPLE_RATE:                                             
            MenuUART(SAMPLE_RATE_MENU);
            break;
        case LAST_SAMPLE:                                             
            CLEAN_BUFFER;
            sprintf(buffer, "%u", FIFOrx_GetLastSample());
            MenuUART(LAST_SAMPLE_MENU);
            break;
        case LAST_10_MEAN:                                            
            CLEAN_BUFFER;
            sprintf(buffer, "%.1f", FIFOrx_GetMean(LAST_10));
            MenuUART(LAST_10_MEAN_MENU);
            break;
        case LAST_10_STD:
            CLEAN_BUFFER;
            sprintf(buffer, "%.1f", FIFOrx_GetStandardDeviation(LAST_10));
            MenuUART(LAST_10_STD_MENU);
            break;
        case SIZE_OF_FIFO:                                            
            MenuUART(SIZE_OF_FIFO_MENU);
            break;
    }
}

/*** INTERRUPTS ***/
CY_ISR(uartRx){                                             // Set a flag when an UART data 
    new_uart_data = 1;                                      // is received
}

/* [] END OF FILE */
