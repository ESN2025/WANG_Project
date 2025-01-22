#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>
#include "sys/alt_sys_init.h"

#include "opencores_i2c.h"
#include "opencores_i2c_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_pio_regs.h"

uint8_t x_low, x_high, y_low, y_high, z_low, z_high;
int16_t accel_x, accel_y, accel_z;
uint8_t axis_select = 0;
static volatile uint8_t button_count = 0;
static uint8_t prev_btn_state = 1;

#define ADXL345_ADDR 0x1D
#define I2C_SPEED    400000
#define REG_DATAX0   0x32
#define REG_DATAX1   0x33
#define REG_DATAY0   0x34
#define REG_DATAY1   0x35
#define REG_DATAZ0   0x36
#define REG_DATAZ1   0x37
#define REG_OFSX     0x1E
#define REG_OFSY     0x1F
#define REG_OFSZ     0x20

uint8_t adxl_read(int16_t addr) {
    uint8_t data = 0;
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_ADDR, 0);
    I2C_write(OPENCORES_I2C_0_BASE, addr, 0);
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_ADDR, 1);
    data = I2C_read(OPENCORES_I2C_0_BASE, 1);
    return data;
}

void adxl_write(int16_t addr, int16_t value) {
    I2C_start(OPENCORES_I2C_0_BASE, ADXL345_ADDR, 0);
    I2C_write(OPENCORES_I2C_0_BASE, addr, 0);
    I2C_write(OPENCORES_I2C_0_BASE, value, 1);
}

void adxl_calibrate() {
    adxl_write(REG_OFSX, 0);
    adxl_write(REG_OFSY, 4);
    adxl_write(REG_OFSZ, 6);
}

int16_t convert_mg(int16_t val) {
    return (int16_t)(val * 3.9);
}

void display_7seg(int16_t val) {
    uint8_t d[5] = {0,0,0,0,0};
    int16_t absv = (val < 0) ? -val : val;
    if (absv > 9999) absv = 9999;
    d[0] = absv % 10;
    d[1] = (absv / 10) % 10;
    d[2] = (absv / 100) % 10;
    d[3] = (absv / 1000) % 10;
    d[4] = (val < 0) ? 10 : 0;
    IOWR_ALTERA_AVALON_PIO_DATA(UNITS_PIO_BASE, d[0]);
    IOWR_ALTERA_AVALON_PIO_DATA(TENS_PIO_BASE,  d[1]);
    IOWR_ALTERA_AVALON_PIO_DATA(HUND_PIO_BASE,  d[2]);
    IOWR_ALTERA_AVALON_PIO_DATA(THOU_PIO_BASE,  d[3]);
    IOWR_ALTERA_AVALON_PIO_DATA(SIGN_PIO_BASE,  d[4]);
}

static void timer_isr(void *context, alt_u32 id) {
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
    unsigned int curr_btn = IORD_ALTERA_AVALON_PIO_DATA(BTN_PIO_BASE) & 0x1;
    if (prev_btn_state == 1 && curr_btn == 0) {
        axis_select++;
        if (axis_select > 2) axis_select = 0;
        alt_printf("Button pressed! axis=%x\n", axis_select);
    }
    prev_btn_state = curr_btn;
    x_low  = adxl_read(REG_DATAX0);
    x_high = adxl_read(REG_DATAX1);
    y_low  = adxl_read(REG_DATAY0);
    y_high = adxl_read(REG_DATAY1);
    z_low  = adxl_read(REG_DATAZ0);
    z_high = adxl_read(REG_DATAZ1);
    accel_x = (int16_t)((x_high << 8) | x_low);
    accel_y = (int16_t)((y_high << 8) | y_low);
    accel_z = (int16_t)((z_high << 8) | z_low);
    accel_x = convert_mg(accel_x);
    accel_y = convert_mg(accel_y);
    accel_z = convert_mg(accel_z);
    alt_printf("X:%x Y:%x Z:%x\n", accel_x, accel_y, accel_z);
    switch(axis_select) {
        case 0: display_7seg(accel_x); alt_printf("X axis\n"); break;
        case 1: display_7seg(accel_y); alt_printf("Y axis\n"); break;
        case 2: display_7seg(accel_z); alt_printf("Z axis\n"); break;
    }
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0x1);
}

int main() {
    I2C_init(OPENCORES_I2C_0_BASE, ALT_CPU_CPU_FREQ, I2C_SPEED);
    adxl_write(0x31, 0x0B);
    adxl_write(0x2D, 0x08);
    adxl_calibrate();
    alt_printf("DATA_FORMAT=%x OFS=%x %x %x\n",
        adxl_read(0x31),
        adxl_read(REG_OFSX),
        adxl_read(REG_OFSY),
        adxl_read(REG_OFSZ));
    alt_irq_register(TIMER_0_IRQ, NULL, timer_isr);
    while(1) {}
    return 0;
}
