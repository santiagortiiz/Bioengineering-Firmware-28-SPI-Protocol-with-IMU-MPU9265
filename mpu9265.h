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

#ifndef MPU9265_H
    #define MPU9265_H
    
    #include "project.h"

    /*** MACROS ***/
    #define RAW_DATA_RDY_INT 0x1
    
    /* Functional Configuraction */
    #define INT_PIN_CFG     0x37
    #define INT_ENABLE      0x38
    #define INT_STATUS      0x3A
    #define USER_CONTROL    0x6A
    #define POWER_MGMT_1    0x6B
    #define POWER_MGMT_2    0x6C
    #define FIFO_R_W        0x74
    #define WHO_AM_I        0x75
    
    /* Accelerometer Data */
    #define ACCEL_CONFIG    0x1C
    #define XA_OFFSET_H     0x77
    #define XA_OFFSET_L     0x78
    #define YA_OFFSET_H     0x7A
    #define YA_OFFSET_L     0x7B
    #define ZA_OFFSET_H     0x7D
    #define ZA_OFFSET_L     0x7E 
    
    #define ACCEL_XOUT_H    0x3B
    #define ACCEL_XOUT_L    0x3C
    #define ACCEL_YOUT_H    0x3D
    #define ACCEL_YOUT_L    0x3E
    #define ACCEL_ZOUT_H    0x3F
    #define ACCEL_ZOUT_L    0x40
    
    /* Temperature Data */
    #define TEMP_OUT_H      0x41
    #define TEMP_OUT_L      0x42
    
    /* Gyroscope Data */
    #define GYRO_CONFIG     0x1B
     
    #define XG_OFFSET_H     0x13
    #define XG_OFFSET_L     0x14
    #define YG_OFFSET_H     0x15
    #define YG_OFFSET_L     0x16
    #define ZG_OFFSET_H     0x17
    #define ZG_OFFSET_L     0x18
    
    #define GYRO_XOUT_H     0x43
    #define GYRO_XOUT_L     0x44
    #define GYRO_YOUT_H     0x45
    #define GYRO_YOUT_L     0x46
    #define GYRO_ZOUT_H     0x47
    #define GYRO_ZOUT_L     0x48
    
    /*** GLOBAL VARIABLE PROTOTYPES ***/
    extern uint8 sensor_data;
    extern uint8 raw_data_rdy;
    
    extern uint16 temperature;
    
    extern uint16 accel_resolution;
    extern uint16 accel_x_offset;
    extern uint16 accel_y_offset;
    extern uint16 accel_z_offset;
    extern uint16 accel_x_out;
    extern uint16 accel_y_out;
    extern uint16 accel_z_out;

    extern uint16 gyro_resolution;
    extern uint16 gyro_x_offset;
    extern uint16 gyro_y_offset;
    extern uint16 gyro_z_offset;
    extern uint16 gyro_x_out;
    extern uint16 gyro_y_out;
    extern uint16 gyro_z_out;
    
    /*** FUNCTION PROTOTYPES ***/
    void mpu9265_Start(void);
    void mpu9265_GetTemperature(uint16 *temperature);
    void mpu9265_GetAccelResolution(uint16 *accel_resolution);
    void mpu9265_GetAccelOffset(uint16 *accel_x_offset, uint16 *accel_y_offset, uint16 *accel_z_offset);
    void mpu9265_GetAccelData(uint16 *accel_x_out, uint16 *accel_y_out, uint16 *accel_z_out);
    void mpu9265_GetGyroResolution(uint16 *gyro_resolution);
    void mpu9265_GetGyroOffset(uint16 *gyro_x_offset, uint16 *gyro_y_offset, uint16 *gyro_z_offset);
    void mpu9265_GetGyroData(uint16 *gyro_x_out, uint16 *gyro_y_out, uint16 *gyro_z_out);
    
    /*** INTERRUPTION PROTOTYPES ***/
    
#endif

/* [] END OF FILE */
