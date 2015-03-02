#ifndef LSM_H
#define LSM_H
// Address constants


//Accel
#define ACC_ADDR    0x19
#define CTRL_REG1_A 0x20
#define CTRL_REG4_A 0x23
#define OUT_X_L_A   0x28
#define OUT_X_H_A   0x29
#define OUT_Y_L_A   0x2A
#define OUT_Y_H_A   0x2B
#define OUT_Z_L_A   0x2C
#define OUT_Z_H_A   0x2D

#define AC_PWR_ON   0x4B
#define AC_PWR_OFF  0x00

//Mag
#define MAG_ADDR    0x1E
#define CRA_REG_M   0x00
#define CRB_REG_M   0x01
#define MR_REG_M    0x02
#define OUT_X_H_M   0x03
#define OUT_X_L_M   0x04
#define OUT_Z_H_M   0x05
#define OUT_Z_L_M   0x06
#define OUT_Y_H_M   0x07
#define OUT_Y_L_M   0x08

// #define MAG_CONFIG  0x94   //1001 0100;
#define MAG_CONFIG  0x80 //1000 0000
#define MAG_PWR_ON  0x00
#define MAG_PWR_OFF 0x03
#define OUT_TEMP_H  0x31
#define OUT_TEMP_L  0x32

#endif
