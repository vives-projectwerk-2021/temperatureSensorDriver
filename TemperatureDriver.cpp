#include "mbed.h"
#include "TemperatureDriver.h"
#pragma once


/** 
 * Wiring scheme: Moisture
 *
 * TCN75         STM32L476RG
 * -------------------------
 * 1. SDA        A4 (PC1)
 * 2. SCL        A5 (PC0)
 * 3. ALERT      ---
 * 4. GND        GND
 * 5. A2         GND
 * 6. A1         GND
 * 7. A0         GND
 * 8. VCC        3V3
 */


I2C i2c(I2C_SDA, I2C_SCL);   
// const int addr8bit = 0x48 << 1; // 8-bit I2C address, 0x90     
const int addr1 = 0x48; //address for the temp sensor in the pipe.
const int addr2 = 0x49; //address for the temp sensor on the main board.




float TemperatureSensorMoisture::temperature()
{
    printf("\r\nTCN75 Tempsensor\r\n"); //prints TCN75 Tempsensor
    //enables the 12bit adc res
    char buffer1[] = { CONFIG,0b01100000 }; 
    i2c.write(addr1, buffer1, 2);
    //sets the max temperature range on 40°C
    char buffer2[] = {TsetLimit,(0b00101000 << 8 )};
    i2c.write(addr1, buffer2, 2);

    //sets the pointer to the Temperature register 
    
    while (true) {
        
        //this part reads the temperature 
        wait(1); //waits 1 ms

        
        i2c.write(addr1, ReadTemp, 1);  //writes the address 1 byte, and then the register address

        i2c.read(addr1, ReadTemp, 2);  //reads 2 bytes 
        printf("Value = %.2f ", ReadTemp);

        float temp1 = (ReadTemp[0]<<8|ReadTemp[1]) / 256; //first data address shifts 8 places and get OR with second data and gets divided by 256 page 16 in http://ww1.microchip.com/downloads/en/devicedoc/21935d.pdf
        
        printf("Temperature = %.2f C\r\n", temp1);

        if (temp1 > 50 | temp1 < -20) { //rekening houden met de waarde van value en aan de hand van de value kijken met 
                                        //hoeveel dit overeen komt voor de temp waarde en zo een range instellen voor de temperatuurssensordriver
            "Temperature isnt in the range."
        }
}

/** 
 * Wiring scheme: Main
 *
 * TCN75         STM32L476RG
 * -------------------------
 * 1. SDA        A4 (PC0)
 * 2. SCL        A5 (PC1)
 * 3. ALERT      --- 
 * 4. GND        GND
 * 5. A2         GND
 * 6. A1         GND
 * 7. A0         VCC
 * 8. VCC        3V3
 */

float TemperatureSensorMain::temperature()
{
    printf("\r\nTCN75 Tempsensor\r\n"); //prints TCN75 Tempsensor
    //enables the 12bit adc res
    char buffer1[] = { CONFIG,0b01100000 }; 
    i2c.write(addr2, buffer1, 2);
    //sets the max temperature range on 40°C
    char buffer2[] = {TsetLimit,(0b00101000 << 8 )};
    i2c.write(addr2, buffer2, 2);

    //sets the pointer to the Temperature register 
    
    while (true) {
        //this part reads the temperature 
        wait(1); //waits 1 ms

        
        i2c.write(addr2, ReadTemp, 1);  //writes the address 1 byte, and then the register address

        i2c.read(addr2, ReadTemp, 2);  //reads 2 bytes 
        printf("Value = %.2f ", ReadTemp);

        float temp2 = (ReadTemp[0]<<8|ReadTemp[1]) / 256; //first data address shifts 8 places and get OR with second data and gets divided by 256 page 16 in http://ww1.microchip.com/downloads/en/devicedoc/21935d.pdf
        
        printf("Temperature = %.2f C\r\n", temp2);

        if (temp2 > 50 | temp2 < -20) { //rekening houden met de waarde van value en aan de hand van de value kijken met 
                                        //hoeveel dit overeen komt voor de temp waarde en zo een range instellen voor de temperatuurssensordriver
            "Temperature isnt in the range."
        }
}
   