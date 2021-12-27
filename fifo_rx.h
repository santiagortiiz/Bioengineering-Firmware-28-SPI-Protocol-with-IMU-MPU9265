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

#ifndef FIFO_RX_H
    #define FIFO_RX_H
    
    #include "project.h"

    /*** MACROS ***/
    #define FIFO_SIZE 100
    #define LAST_10 10
    #define TRUE 1
    #define FALSE 0
    
    #define FIFO_FULL FIFO_rx.full
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    typedef struct fifo_rx_flags {
        uint8 empty:1;
        uint8 full:1;
    } fifo_rx_flags;
    
    extern fifo_rx_flags FIFO_rx;
    extern uint16 FIFO[FIFO_SIZE];
    extern uint16 *put_FIFO_pointer;
    extern uint16 *get_FIFO_pointer;
    
    /*** FUNCTION PROTOTYPES ***/
    uint8 FIFO_putData(uint16 data);
    uint8 FIFO_getData(uint16 *consume);
    
    uint16 FIFOrx_GetLastSample(void);
    float32 FIFOrx_GetMean(uint8 samples_number);
    float32 FIFOrx_GetStandardDeviation(uint8 samples_number);
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
