/*
 * MS5837.h
 *
 *  Created on: Jun 15, 2021
 *      Author: Damian
 */

#ifndef INC_MS5837_H_BLUEROBOTICS
#define INC_MS5837_H_BLUEROBOTICS

//#include "Arduino.h"
#include <stdint.h>
#include "stm32f1xx_hal.h"


#ifndef FALSE
	#define FALSE 0
#endif

#ifndef TRUE
	#define TRUE 1
#endif

	uint8_t MS5837_init(I2C_HandleTypeDef *hi2c);

	/** Set model of MS5837 sensor. Valid options are MS5837::MS5837_30BA (default)
	 * and MS5837::MS5837_02BA.
	 */
	void MS5837_setModel(uint8_t model);

	/** Provide the density of the working fluid in kg/m^3. Default is for
	 * seawater. Should be 997 for freshwater.
	 */
	void MS5837_setFluidDensity(float density);

	/** The read from I2C takes up to 40 ms, so use sparingly is possible.
	 */
	void MS5837_read();

	/** Pressure returned in mbar or mbar*conversion rate.
	 */
	float MS5837_pressure(float conversion);

	/** Temperature returned in deg C.
	 */
	float MS5837_temperature();

	/** Depth returned in meters (valid for operation in incompressible
	 *  liquids only. Uses density that is set for fresh or seawater.
	 */
	float MS5837_depth();

	/** Altitude returned in meters (valid for operation in air only).
	 */
	float MS5837_altitude();

	/** Performs calculations per the sensor data sheet for conversion and
	 *  second order compensation.
	 */
//	void calculate();

//	uint8_t crc4(uint16_t n_prom[]);


#endif /* INC_MS5837_H_BLUEROBOTICS */
