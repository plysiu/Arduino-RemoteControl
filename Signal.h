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

	//Kalman - start
	double q; //process noise covariance
	double r; //measurement noise covariance
	double x; //value
	double p; //estimation error covariance
	double k; //kalman gain
	//Kalman - end

protected:
	static bool calibration;
public:

	static bool setCalibrationOn();
	static bool setCalibrationOff();
	static bool getCalibrationStatus();

	Signal(int pin);
	void read();
	int getValue();
	void setValue(int _value);
	int getMaxValue();
	void setMaxValue(int _value);
	int getMinValue();
	void setMinValue(int _value);
	int getCenterValue();
	void setCenterValue(int _value);
	int getTiltRod();
	virtual ~Signal();
};

#endif /* SIGNAL_H_ */
