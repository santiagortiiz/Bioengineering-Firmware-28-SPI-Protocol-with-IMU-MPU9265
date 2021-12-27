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

#ifndef INTERFACE_H
    #define INTERFACE_H
    
    #include "project.h"

    /*** MACROS ***/
    #define TEMP_MENU               0
    #define ACCEL_MENU              1
    #define GYRO_MENU               2
    #define MEMORY_USAGE_MENU       3
    
    #define SENSOR_REFERENCE_MENU   0
    #define ACCEL_RESOLUTION_MENU   1
    #define GYRO_RESOLUTION_MENU    2
    #define SAMPLE_RATE_MENU        3
    #define LAST_SAMPLE_MENU        4
    #define LAST_10_MEAN_MENU       5
    #define LAST_10_STD_MENU        6
    #define SIZE_OF_FIFO_MENU       7
    #define MEAN_MENU               8
    #define STD_MENU                9
    #define LAST_MEMORY_USAGE       10
    #define FIFO_FULL_COUNTER       11
    #define SEND_ACCEL_DATA         12
    #define SEND_GYRO_DATA          13
    #define SEND_TEMP_DATA          14
    #define CONFIRM_RECEPTION       15
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    
    /*** FUNCTION PROTOTYPES ***/
    void MenuLCD(uint8);
    void MenuUART(uint8);
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
