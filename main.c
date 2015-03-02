//#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <ncurses.h>
#include <string.h>

#include "lsm.h"
#include "util.h"

int main() {
  int file = open("/dev/i2c-1", O_RDWR);
  if (file < 0) { 
    printf("Error opening /dev/i2c-1\n");
    exit(1);
  }
  
  if (ioctl(file, I2C_SLAVE, ACC_ADDR) < 0) {
    printf("error selecting i2c device");
    exit(1);
  }

  // Activate Accel
  //accel_on(file);
  char buffer[2];
  buffer[0] = CTRL_REG1_A;
  buffer[1] = AC_PWR_ON;
  write(file, buffer, 2);

  // 
  if (ioctl(file, I2C_SLAVE, MAG_ADDR) < 0) {
    printf("Error selecting new slave\n");
    exit(1);
  }
  
  buffer[0] = MR_REG_M;
  buffer[1] = MAG_PWR_ON;
  write(file,buffer,2);
  
  while (1) {
  ioctl(file, I2C_SLAVE, ACC_ADDR);
  
  char xa[2],ya[2],za[2];
  char xm[2],ym[2],zm[2];
  char temp[2];
  char first = 1;
  printf("Accel: \n");
  // Read X
  xa[0] = i2c_smbus_read_byte_data(file,OUT_X_L_A);
  xa[1] = i2c_smbus_read_byte_data(file,OUT_X_H_A);
  printf("X: 0x%02x 0x%02x\n", xa[0], xa[1]);
  short xaval;
  xaval = xa[1];
  xaval << 8;
  xaval = xaval | xa[0];
  printf("%d\n", xaval);

  // Read Y
  ya[0] = i2c_smbus_read_byte_data(file,OUT_Y_L_A);
  ya[1] = i2c_smbus_read_byte_data(file,OUT_Y_H_A);
  printf("Y: 0x%02x 0x%02x\n", ya[0], ya[1]);
  short y = convert_bytes(ya);
  printf("%d\n", y);

  // Read Z
  za[0] = i2c_smbus_read_byte_data(file,OUT_Z_L_A);
  za[1] = i2c_smbus_read_byte_data(file,OUT_Z_H_A);
  printf("Z: 0x%02x 0x%02x\n", za[0], za[1]);
  short z = convert_bytes(za);
  printf("%d\n", z);

  ioctl(file, I2C_SLAVE, MAG_ADDR);

  printf("\nMag: \n");
  xm[0] = i2c_smbus_read_byte_data(file, OUT_X_L_M);
  xm[1] = i2c_smbus_read_byte_data(file, OUT_X_H_M);
  printf("X: 0x%02x 0x%02x\n", xm[0], xm[1]);
  short x = convert_bytes(xm);
  printf("%d\n", x);


  ym[0] = i2c_smbus_read_byte_data(file, OUT_Y_L_M);
  ym[1] = i2c_smbus_read_byte_data(file, OUT_Y_H_M);
  printf("Y: 0x%02x 0x%02x\n", ym[0], ym[1]);
  y = convert_bytes(ym);
  printf("%d\n", y);


  zm[0] = i2c_smbus_read_byte_data(file, OUT_Y_L_M);
  zm[1] = i2c_smbus_read_byte_data(file, OUT_Y_H_M);
  printf("Z: 0x%02x 0x%02x\n", ym[0], ym[1]);
  z = convert_bytes(zm);
  printf("%d\n", z);


  temp[0] = i2c_smbus_read_byte_data(file,OUT_TEMP_L);
  temp[1] = i2c_smbus_read_byte_data(file,OUT_TEMP_H);
  printf("\nT: 0x%02x 0x%02x\n", temp[0], temp[1]);
  sleep(1);
  }
  buffer[0] = MR_REG_M;
  buffer[1] = MAG_PWR_OFF;
  write(file,buffer,2);
  
  ioctl(file, I2C_SLAVE, ACC_ADDR);
  
  buffer[0] = CTRL_REG1_A;
  buffer[1] = AC_PWR_OFF;
  write(file,buffer,2);
  close(file);
}
