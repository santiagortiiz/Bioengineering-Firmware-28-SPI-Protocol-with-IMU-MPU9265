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
#include "project.h"

#include "chronometer.h"            
#include "fifo_rx.h"                
#include "interface.h"              
#include "keyboard.h"
#include "mpu9265.h"
#include "spi_protocol.h"
#include "uart_communication.h"
#include "e2prom.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_uart_rx_StartEx(uartRx);
    isr_counter_StartEx(msCounter);
    isr_KBI_StartEx(KBI);

    /* COMPONENTS INITIALIZATION */
    Counter_Start();
    LCD_Start();
    UART_Start();
    SPIM_Start();
    EEPROM_Start();
    mpu9265_Start();                                // IMU sensor
    
    /* INITIAL INTERFACE */
    MenuUART(LAST_MEMORY_USAGE);                    // Show the statistics of the previous sesion
    amount_of_saved_values = EEPROM_ReadByte(LAST_LOCATION);
    MenuLCD(MEMORY_USAGE_MENU);
    E2PROM_readFIFOStatistics();                    // Read FIFO statistics of the last sesion
    
    for(;;)
    {
        if (new_uart_data){                         // When the UART received a new data    
            new_uart_data = 0;                      // the userRequest function is called
            uart_data = UART_ReadRxData();          // to verify the user's query.
            userRequest(uart_data);
        }
        
        if (FIFO_FULL){                             // When the FIFO is full, an statistical
            FIFO_rx.full = 0;                       // measurements are taken and stored in
            //E2PROM_writeFIFOStatistics();           // the EEPROM
        }
        
        if (ms%TIME_PERIOD == 0){
            switch(key){
                case 'A':                           // Temperature adquisition routine
                    mpu9265_GetTemperature(&temperature);
                    FIFO_putData(temperature);
                    MenuLCD(TEMP_MENU);
                    if (python_sync_up){
                        MenuUART(SEND_TEMP_DATA);
                    }
                    break;
                
                case 'B':
                    if (ms%5000 == 0){              // Accelerometer adquisition routine
                        mpu9265_GetAccelOffset(&accel_x_offset, &accel_y_offset, &accel_z_offset);
                    }
                    mpu9265_GetAccelData(&accel_x_out, &accel_y_out, &accel_z_out);
                    FIFO_putData(accel_z_out);      // Just store statistics of a plane of movement
                    MenuLCD(ACCEL_MENU);
                    if (python_sync_up){
                        MenuUART(SEND_ACCEL_DATA);
                    }
                    break;
                    
                case 'C':
                    if (ms%5000 == 0){              // Gyro adquisition routine
                        mpu9265_GetGyroOffset(&gyro_x_offset, &gyro_y_offset, &gyro_z_offset);
                    }
                    mpu9265_GetGyroData(&gyro_x_out, &gyro_y_out, &gyro_z_out);
                    FIFO_putData(gyro_x_out);       // Just store statistics of a plane of movement
                    MenuLCD(GYRO_MENU);
                    if (python_sync_up){
                        MenuUART(SEND_GYRO_DATA);
                    }
                    break;
            }
        }
    }
}

/* [] END OF FILE */