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
#include "interface.h"
#include "uart_communication.h"
#include "mpu9265.h"
#include "e2prom.h"

/*** VARIABLES ***/

/*** FUNCTIONS ***/
void MenuLCD(uint8 menu_index){
    switch(menu_index){
        case TEMP_MENU:
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Temperature");
            LCD_Position(1,0);
            LCD_PrintNumber(temperature);
            break;
            
        case ACCEL_MENU:
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Accel RawData");
            LCD_Position(1,0);
            LCD_PrintString("Xout: ");
            if ((accel_x_out & 0x8000) == 0x8000){     
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - accel_x_out);
            }
            else{
                LCD_PrintNumber(accel_x_out);
            }
            
            LCD_Position(2,0);
            LCD_PrintString("Yout: ");
            if ((accel_y_out & 0x8000) == 0x8000){
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - accel_y_out);
            }
            else{
                LCD_PrintNumber(accel_y_out);
            }
            
            LCD_Position(3,0);
            LCD_PrintString("Zout: ");
            if ((accel_z_out & 0x8000) == 0x8000){
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - accel_z_out);
            }
            else{
                LCD_PrintNumber(accel_z_out);
            }
            
            
            LCD_Position(0,14);
            LCD_PrintString("Offset");
            LCD_Position(1,14);
            LCD_PrintNumber(accel_x_offset);
            LCD_Position(2,14);
            LCD_PrintNumber(accel_y_offset);
            LCD_Position(3,14);
            LCD_PrintNumber(accel_z_offset);
            break;
            
        case GYRO_MENU:
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Gyro  RawData");
            LCD_Position(1,0);
            LCD_PrintString("Xout: ");
            if ((gyro_x_out & 0x8000) == 0x8000){
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - gyro_x_out);
            }
            else{
                LCD_PrintNumber(gyro_x_out);
            }
            
            LCD_Position(2,0);
            LCD_PrintString("Yout: ");
            if ((gyro_y_out & 0x8000) == 0x8000){
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - gyro_y_out);
            }
            else{
                LCD_PrintNumber(gyro_y_out);
            }
            
            LCD_Position(3,0);
            LCD_PrintString("Zout: ");
            if ((gyro_z_out & 0x8000) == 0x8000){
                LCD_PutChar('-');
                LCD_PrintNumber(65535 - gyro_z_out);
            }
            else{
                LCD_PrintNumber(gyro_z_out);
            }
            
            LCD_Position(0,14);
            LCD_PrintString("Offset");
            LCD_Position(1,14);
            LCD_PrintNumber(gyro_x_offset);
            LCD_Position(2,14);
            LCD_PrintNumber(gyro_y_offset);
            LCD_Position(3,14);
            LCD_PrintNumber(gyro_z_offset);
            break;
            
        case MEMORY_USAGE_MENU:
            LCD_ClearDisplay();
            LCD_Position(0,0);
            LCD_PrintString("Last sesion use: ");
            LCD_Position(1,0);
            LCD_PrintNumber(amount_of_saved_values);
            LCD_PrintString(" bits of the ");
            LCD_Position(2,0);
            LCD_PrintString("EEPROM");
            break;
    }
}

void MenuUART(uint8 menu_index){
    switch(menu_index){
        case SENSOR_REFERENCE_MENU: // Referencia Comercial
            UART_PutCRLF(' ');
            UART_PutString("MPU-92/65");     
            break;
        case ACCEL_RESOLUTION_MENU: // Resolucion de muestras
            UART_PutCRLF(' ');
            UART_PutString("Accel Resolution: ");
            UART_PutString(buffer);  
            break;
        case GYRO_RESOLUTION_MENU: // Resolucion de muestras
            UART_PutCRLF(' ');
            UART_PutString("Gyro Resolution: ");     
            UART_PutString(buffer);     
            break;
        case SAMPLE_RATE_MENU:
            UART_PutCRLF(' ');
            UART_PutString("Sample Rate:");
            UART_PutCRLF(' ');
            UART_PutString("Accel - 4kHz");
            UART_PutCRLF(' ');
            UART_PutString("Gyro - 8kHz");
            break;
        case LAST_SAMPLE_MENU:
            UART_PutCRLF(' ');
            UART_PutString("Last Sample: ");
            UART_PutString(buffer);    
            break;
        case LAST_10_MEAN_MENU:
            UART_PutCRLF(' ');
            UART_PutString("Mean of the last 10 samples: ");
            UART_PutString(buffer);     
            break;
        case LAST_10_STD_MENU:
            UART_PutCRLF(' ');
            UART_PutString("Standar Deviation of the last 10 samples: ");
            UART_PutString(buffer);     
            break;
        case SIZE_OF_FIFO_MENU:
            UART_PutCRLF(' ');
            UART_PutString("Size of the sensor's FIFO: ");
            UART_PutString("512");     
            break;
        case MEAN_MENU:
            UART_PutCRLF(' ');
            UART_PutString(identifier);
            UART_PutCRLF(' ');
            UART_PutString(" Mean: ");
            UART_PutString(buffer);  
            break;
        case STD_MENU:
            UART_PutCRLF(' ');
            UART_PutString(" Standar Deviation: ");
            UART_PutString(buffer);  
            break;
        case LAST_MEMORY_USAGE:
            UART_PutCRLF(' ');
            UART_PutString("Last Activity");
            break;
        case FIFO_FULL_COUNTER:
            UART_PutCRLF(' ');
            UART_PutString("FIFO full counter: ");
            UART_PutString(buffer);
            break;
        case SEND_ACCEL_DATA:
            if ((accel_x_out & 0x8000) == 0x8000){     
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(accel_x_out/1000);
            UART_PutChar(accel_x_out/100%10);
            UART_PutChar(accel_x_out/10%10);
            UART_PutChar(accel_x_out%10);
            
            if ((accel_y_out & 0x8000) == 0x8000){
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(accel_y_out/1000);
            UART_PutChar(accel_y_out/100%10);
            UART_PutChar(accel_y_out/10%10);
            UART_PutChar(accel_y_out%10);
            
            if ((accel_z_out & 0x8000) == 0x8000){  // 
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(accel_z_out/1000);
            UART_PutChar(accel_z_out/100%10);
            UART_PutChar(accel_z_out/10%10);
            UART_PutChar(accel_z_out%10);
            break;
        case SEND_GYRO_DATA:
            if ((gyro_x_out & 0x8000) == 0x8000){     
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(gyro_x_out/1000);
            UART_PutChar(gyro_x_out/100%10);
            UART_PutChar(gyro_x_out/10%10);
            UART_PutChar(gyro_x_out%10);
            
            
            if ((gyro_y_out & 0x8000) == 0x8000){     
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(gyro_y_out/1000);
            UART_PutChar(gyro_y_out/100%10);
            UART_PutChar(gyro_y_out/10%10);
            UART_PutChar(gyro_y_out%10);
            
            
            if ((gyro_z_out & 0x8000) == 0x8000){     
                UART_PutChar('-');
            }
            else{
                UART_PutChar('+');
            }
            UART_PutChar(gyro_z_out/1000);
            UART_PutChar(gyro_z_out/100%10);
            UART_PutChar(gyro_z_out/10%10);
            UART_PutChar(gyro_z_out%10);
            break;
        case SEND_TEMP_DATA:
            UART_PutChar(temperature/1000);
            UART_PutChar(temperature/100%10);
            UART_PutChar(temperature/10%10);
            UART_PutChar(temperature%10);
            break;
            
        case CONFIRM_RECEPTION:
            UART_PutChar(0xFF);
            break;
    }
}

/*** INTERRUPTS ***/

/* [] END OF FILE */
