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
#include "mpu9265.h"
#include "spi_protocol.h"

/*** VARIABLES ***/
uint8 sensor_data;
uint8 raw_data_rdy;

uint16 temperature;

uint16 accel_resolution;
uint16 accel_x_offset;
uint16 accel_y_offset;
uint16 accel_z_offset;
uint16 accel_x_out;
uint16 accel_y_out;
uint16 accel_z_out;

uint16 gyro_resolution;
uint16 gyro_x_offset;
uint16 gyro_y_offset;
uint16 gyro_z_offset;
uint16 gyro_x_out;
uint16 gyro_y_out;
uint16 gyro_z_out;

/*** FUNCTIONS ***/
void mpu9265_Start(void){
    spi_write(USER_CONTROL, 0b00010000);        // Set SPI Mode Only
    CyDelay(100);
    
    spi_write(POWER_MGMT_1, 0x00);              // Power management 1
    spi_write(POWER_MGMT_2, 0x00);              // Power management 2
    
    spi_write(INT_PIN_CFG, 0b00000000);         // Pin interrupt configure as active high, push-pull, 
                                                // pulse of 50us and interrupt status cleared if any 
                                                // read operation is performed
    
    spi_write(INT_ENABLE, 0b00000000);          // Disable Raw Sensor Data ready interrupt
    CyDelay(500);
                                                // Get the initial offsets
    mpu9265_GetAccelOffset(&accel_x_offset, &accel_y_offset, &accel_z_offset);
    mpu9265_GetGyroOffset(&gyro_x_offset, &gyro_y_offset, &gyro_z_offset);
    
    SPIM_ClearRxBuffer();                       // Clear SPIM's FIFO
    SPIM_ClearFIFO();
    
}

/* Data adquisition functions are based on this Routine 
    1) Set a pointer to the input variable
    2) Assign the first byte requested from the address
       register
    3) Shift 8 positions the content to the left
    4) Make an OR operation between the actual shifted  
       content and the second byte requested from the
       address register

    At the end of this routine, each function had assigned 
    to each pointed variable, a 16-bit value corresponding 
    to the content of the high and low bytes of the variables 
    sensed in each axis.
*/

/* Temperature */
void mpu9265_GetTemperature(uint16 *temperature){
    *temperature = spi_request(TEMP_OUT_H) << 8;
    *temperature |= spi_request(TEMP_OUT_L);
}

/* Accelerometer */
void mpu9265_GetAccelResolution(uint16 *accel_resolution){
    uint8 FS_SEL = 0; 
    FS_SEL = spi_request(ACCEL_CONFIG) >> 3 | 0b00000011;
    switch(FS_SEL){                     // FullScale Selector
        case 0:
            *accel_resolution = 16384;  // [LSB/g]
            break;
        case 1:
            *accel_resolution = 8192;  // [LSB/g]
            break;
        case 2:
            *accel_resolution = 4096;  // [LSB/g]
            break;
        case 3:
            *accel_resolution = 2048;  // [LSB/g]
            break;
    }
}

void mpu9265_GetAccelOffset(uint16 *accel_x_offset, uint16 *accel_y_offset, uint16 *accel_z_offset){
    *accel_x_offset = spi_request(XA_OFFSET_H) << 8;        
    *accel_x_offset |= spi_request(XA_OFFSET_L);             
    
    *accel_y_offset = spi_request(YA_OFFSET_H) << 8;
    *accel_y_offset |= spi_request(YA_OFFSET_L);
    
    *accel_z_offset = spi_request(ZA_OFFSET_H) << 8;
    *accel_z_offset |= spi_request(ZA_OFFSET_L);
}

void mpu9265_GetAccelData(uint16 *accel_x_out, uint16 *accel_y_out, uint16 *accel_z_out){
    *accel_x_out = spi_request(ACCEL_XOUT_H) << 8;
    *accel_x_out |= spi_request(ACCEL_XOUT_L);
    
    *accel_y_out = spi_request(ACCEL_YOUT_H) << 8;
    *accel_y_out |= spi_request(ACCEL_YOUT_L);
    
    *accel_z_out = spi_request(ACCEL_ZOUT_H) << 8;
    *accel_z_out |= spi_request(ACCEL_ZOUT_L);
}

/* Gyroscope */
void mpu9265_GetGyroResolution(uint16 *gyro_resolution){
    uint8 FS_SEL = 0; 
    FS_SEL = spi_request(GYRO_CONFIG) | 0b00011000 >> 3;
    switch(FS_SEL){                     // FullScale Selector
        case 0:                         // gyro_resolution is x10 because is a float number
            *gyro_resolution = 1310;    // [LSB/g]
            break;
        case 1:
            *gyro_resolution = 655;     // [LSB/g]
            break;
        case 2:
            *gyro_resolution = 328;     // [LSB/g]
            break;
        case 3:
            *gyro_resolution = 164;     // [LSB/g]
            break;
    }
}

void mpu9265_GetGyroOffset(uint16 *gyro_x_offset, uint16 *gyro_y_offset, uint16 *gyro_z_offset){
    *gyro_x_offset = spi_request(XG_OFFSET_H) << 8;
    *gyro_x_offset |= spi_request(XG_OFFSET_L);
    
    *gyro_y_offset = spi_request(YG_OFFSET_H) << 8;
    *gyro_y_offset |= spi_request(YG_OFFSET_L);
    
    *gyro_z_offset = spi_request(ZG_OFFSET_H) << 8;
    *gyro_z_offset |= spi_request(ZG_OFFSET_L);
}

void mpu9265_GetGyroData(uint16 *gyro_x_out, uint16 *gyro_y_out, uint16 *gyro_z_out){
    *gyro_x_out = spi_request(GYRO_XOUT_H) << 8;
    *gyro_x_out |= spi_request(GYRO_XOUT_L);
    
    *gyro_y_out = spi_request(GYRO_YOUT_H) << 8;
    *gyro_y_out |= spi_request(GYRO_YOUT_L);
    
    *gyro_z_out = spi_request(GYRO_ZOUT_H) << 8;
    *gyro_z_out |= spi_request(GYRO_ZOUT_L);
}

/*** INTERRUPTS ***/

/* [] END OF FILE */
