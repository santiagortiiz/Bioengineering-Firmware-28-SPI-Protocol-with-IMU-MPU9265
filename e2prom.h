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

#ifndef E2PROM_H
    #define E2PROM_H
    
    #include "project.h"

    /*** MACROS ***/
    #define CLEAN_BUFFER for(uint8 clean = 0; clean < 8; clean++) buffer[clean] = 0
    
                       // 0x000000FilaColumna - La columna corresponde al Byte numero "i", que va desde 0x0 hasta 0xF 
    #define fila_0_byte_0 0x00000000
    #define fila_0_byte_1 0x00000001
    #define fila_0_byte_2 0x00000002
    
    #define fila_0_byte_3 0x00000003
    #define fila_0_byte_4 0x00000004
    #define fila_0_byte_5 0x00000005
    
    #define fila_0_byte_6 0x00000006
    #define fila_0_byte_7 0x00000007
    #define fila_0_byte_8 0x00000008
    
    #define fila_1_byte_0 0x00000010
    #define fila_2_byte_0 0x00000020
    
    #define LAST_LOCATION 0x7FF
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    extern uint8 amount_of_saved_values;
    extern char identifier[8];
    extern uint8 location;
    
    /*** FUNCTION PROTOTYPES ***/
    void E2PROM_writeFIFOStatistics(void);
    void E2PROM_readFIFOStatistics(void);
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
