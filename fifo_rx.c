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
#include "fifo_rx.h"

#include <math.h>

/*** VARIABLES ***/
fifo_rx_flags FIFO_rx;
uint16 FIFO[FIFO_SIZE];
uint16 *put_FIFO_pointer = &FIFO[0];
uint16 *get_FIFO_pointer = &FIFO[0];

/*** FUNCTIONS ***/
uint8 FIFO_putData(uint16 data){
    if (FIFO_rx.full){                              // If the FIFO_full_flag is on,  
        return FALSE;                               // the data can't be put in the FIFO
    }
    else{                                           // Otherwise the data will be put in the FIFO 
        *put_FIFO_pointer = data;                   // and the pointer position will be the next
        put_FIFO_pointer++;                         // Note: This is the same that *(put_FIFO_pointer++)
        if (put_FIFO_pointer == &FIFO[FIFO_SIZE]){  // When the pointer point to the null char
            put_FIFO_pointer = &FIFO[0];
            FIFO_FULL = TRUE;                       // This means that the fifo has 8 Bytes saved
        }
        return TRUE;
    }
}

uint8 FIFO_getData(uint16 *consumer){
    if (FIFO_rx.empty){
        return FALSE;    
    }
    else{                                           // The value of the get_FIFO_pointer is assign to 
        *consumer = *get_FIFO_pointer;              // the consumer variable.
        get_FIFO_pointer++;                         // Note: This is the same that *(get_FIFO_pointer++)
        if (get_FIFO_pointer == &FIFO[FIFO_SIZE]){  // When the pointer point to the null char
            get_FIFO_pointer = &FIFO[0];
        }
        return TRUE;
    }
}

/*
// If FIFO is EMPTY
if (put_FIFO_pointer == get_FIFO_pointer){ 
    FIFO_rx.empty = 1;
}
// If FIFO is FULL
if ((put_FIFO_pointer + 1 == get_FIFO_pointer) OR (put_FIFO_pointer - get_FIFO_pointer == FIFO_SIZE - 1)){
    FIFO_rx.full = 1;
}
*/

/* STATISTICAL FUNCTIONS */
uint16 FIFOrx_GetLastSample(void){
    uint16 data = 0;
    get_FIFO_pointer = &*put_FIFO_pointer - 1;      // Set the get FIFO pointer in the actual position
    FIFO_getData(&data);                            // Get the content of the pointer and assign
    return data;                                    // it to "data"
}

float32 FIFOrx_GetMean(uint8 samples_number){
    float32 mean = 0;
    get_FIFO_pointer = &*put_FIFO_pointer;          // Set the get FIFO pointer in the actual position
    
    for (uint8 i = 0; i < samples_number; i++){
        mean += *get_FIFO_pointer;                  // Acumulate the values of the pointer
        
        if (get_FIFO_pointer == &FIFO[0]){          // If the pointer is in the first
            get_FIFO_pointer = &FIFO[FIFO_SIZE];    // position, set it to the last one
        }
        else {                                      // Otherwise, set it to the previous one
            get_FIFO_pointer--;
        }
    }
    
    mean /= samples_number;                         // Divide the acumulated value by the samples number
    return mean;                        
}

float32 FIFOrx_GetStandardDeviation(uint8 samples_number){
    uint16 buffer[samples_number];
    float32 mean = 0;
    float32 standar_deviation = 0;
    get_FIFO_pointer = &*put_FIFO_pointer;          // Set the get FIFO pointer in the actual position
    
    for (uint8 i = 0; i < samples_number; i++){
        buffer[i] = *get_FIFO_pointer;              // Store each value in a buffer
        mean += buffer[i];                          // Acumulate each value to do an average
        
        if (get_FIFO_pointer == &FIFO[0]){          // If the pointer is in the first
            get_FIFO_pointer = &FIFO[FIFO_SIZE];    // position, set it to the last one
        }
        else {                                      // Otherwise, set it to the previous one
            get_FIFO_pointer--;
        }
    }
    
    mean /= samples_number;                         // Divide the acumulated value by the samples number
    
    for (uint8 i = 0; i < samples_number; i++){     // Apply the STD Formula
        standar_deviation += pow(buffer[i] - mean, 2);
    }
    standar_deviation = sqrt(standar_deviation/samples_number);
    
    return standar_deviation;
}

/*** INTERRUPTS ***/

/* [] END OF FILE */
