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

#ifndef UART_COMMUNICATION_H
    #define UART_COMMUNICATION_H
    
    #include "project.h"

    /*** MACROS ***/
    #define SENSOR_REFERENCE    0
    #define SENSOR_RESOLUTION   1
    #define SAMPLE_RATE         2
    #define LAST_SAMPLE         3
    #define LAST_10_MEAN        4
    #define LAST_10_STD         5
    #define SIZE_OF_FIFO        6
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    extern uint8 python_sync_up;
    extern char buffer[8];
    extern uint8 new_uart_data;
    extern uint8 uart_data;
    
    /*** FUNCTION PROTOTYPES ***/
    void userRequest(uint8 query);
    
    /*** INTERRUPTION PROTOTYPES ***/
    CY_ISR_PROTO(uartRx);
    
#endif

/* [] END OF FILE */
