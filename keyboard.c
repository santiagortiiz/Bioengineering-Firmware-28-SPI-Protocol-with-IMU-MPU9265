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
#include "keyboard.h"

/*** VARIABLES ***/
unsigned char key;

/*** FUNCTIONS ***/

/*** INTERRUPTS ***/
CY_ISR(KBI){
    key = KeyBoard_teclaPresionada();  
}


/* [] END OF FILE */
