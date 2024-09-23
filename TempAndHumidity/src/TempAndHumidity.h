/*
  This code is developed under the MYOSA (LearnTheEasyWay) initiative of MakeSense EduTech and Pegasus Automation.
  Code has been derived from internet sources and component datasheets.
  Existing readily-available libraries would have been used "AS IS" and modified for ease of learning purpose.

  Synopsis of Temperature And Humidity Board
  MYOSA Platform consists of an Temperature And Humidity Board. It is equiped with Si7021 IC.
  It has ± 3% relative humidity measurements with a range of 0–80% RH, and ±0.4 °C temperature accuracy at a range of -10 to +85 °C.
  I2C Address of the board = 0x40.
  Detailed Information about Temperature and Humidity board Library and usage is provided in the link below.
  Detailed Guide: https://drive.google.com/file/d/1On6kzIq3ejcu9aMGr2ZB690NnFrXG2yO/view

  NOTE
  All information, including URL references, is subject to change without prior notice.
  Please always use the latest versions of software-release for best performance.
  Unless required by applicable law or agreed to in writing, this software is distributed on an
  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied

  Modifications
  1 December, 2021 by Pegasus Automation
  (as a part of MYOSA Initiative)
 
  Contact Team MakeSense EduTech for any kind of feedback/issues pertaining to performance or any update request.
  Email: dev.myosa@gmail.com
*/

#ifndef __TEMPANDHUMIDITY_H__
#define __TEMPANDHUMIDITY_H__

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

#define Si7021_I2C_ADDRESS              0x40u
#define Si7021_SOFT_RESET_DELAY         0x0Fu
#define Si7021_MEAS_RH_HOLD_MODE        0xE5u   /**< Measure Relative Humidity, Hold Master Mode */
#define Si7021_MEAS_RH_NOHOLD_MODE      0xF5u   /**< Measure Relative Humidity, No Hold Master Mode */
#define Si7021_MEAS_TEMP_HOLD_MODE      0xE3u   /**< Measure Temperature, Hold Master Mode */
#define Si7021_MEAS_TEMP_NOHOLD_MODE    0xF3u   /**< Measure Temperature, No Hold Master Mode */
#define Si7021_READ_TEMP_PREV_RH_MEAS   0xE0u   /**< Read Temperature Value from Previous RH Measurement */
#define Si7021_RESET                    0xFEu
#define Si7021_WRITE_USER_REG           0xE6u   /**< Write RH/T User Register 1 */
#define Si7021_READ_USER_REG            0xE7u   /**< Read RH/T User Register 1 */
#define Si7021_WRITE_HEATER_CNTRL_REG   0x51u   /**< Write Heater Control Register */
#define Si7021_READ_HEATER_CNTRL_REG    0x11u   /**< Read Heater Control Register */
#define Si7021_ID1_CMD0                 0xFAu   /**< Read Electronic ID 1st Byte */
#define Si7021_ID1_CMD1                 0x0Fu   /**< Read Electronic ID 1st Byte */
#define Si7021_ID2_CMD0                 0xFCu   /**< Read Electronic ID 2nd Byte */
#define Si7021_ID2_CMD1                 0xC9u   /**< Read Electronic ID 2nd Byte */
#define Si7021_FIMWARE_REV_CMD0         0x84u   /**< Read Firmware Revision */
#define Si7021_FIMWARE_REV_CMD1         0xB8u   /**< Read Firmware Revision */

/*!
 * list of bitfields to configure the User Register 1
 */
typedef struct
{
  uint8_t RES0:1;
  uint8_t RSVD0:1;
  uint8_t HTRE:1;
  uint8_t RSVD1:3;
  uint8_t VDDS:1;
  uint8_t RES1:1;
}USER_REG_t;

class TempAndHumidity
{
  public:
    TempAndHumidity();
    bool begin(void);
    bool reset(void);
    bool ping(void);
    float getRelativeHumdity(bool print=true);
    float getTempC(bool print=true);
    float getTempF(bool print=true);
    float getHeatIndexC(bool print=true);
    float getHeatIndexF(bool print=true);
    uint64_t getSerialNumber(void);
    char *getFirmwareVersion(void);
  private:
    uint8_t _i2cSlaveAddress;
    bool _isConnected;
    void i2c_init(void);
    bool readByte(uint8_t reg, uint8_t *in);
    bool readMultiBytes(uint8_t reg, uint8_t length, uint8_t *in);
    bool readMultiBytes(uint8_t length, uint8_t *in);
    bool writeByte(uint8_t reg);
    bool writeByte(uint8_t reg, uint8_t val);
    bool writeAddress(void);
    void delay_ms(uint16_t ms);
};
#endif
