/*
 * Signal.h
 *
 *  Created on: 18 paź 2015
 *      Author: plysiu
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <Arduino.h>

class Signal {
	int pin;
	int value;
	int centerValue;
	int maxValue;
	int minValue;
protected:
	static bool calibration;
public:
	const int START_VALUE = -1;
	static bool setCalibrationOn();
	static bool setCalibrationOff();
	static bool getCalibrationStatus();
	Signal(int pin);
	void read();
	int getValue();
	int getMaxValue();
	int getMinValue();
	int getCenterValue();
	int getTiltRod();
	virtual ~Signal();
};

#endif /* SIGNAL_H_ */
