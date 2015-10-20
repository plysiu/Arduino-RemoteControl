/*
 * Signal.cpp
 *
 *  Created on: 18 paź 2015
 *      Author: plysiu
 *      @TODO create Kalman library
 */

#include "Signal.h"

bool Signal::calibration = false;

bool Signal::getCalibrationStatus() {
	return Signal::calibration;
}

void Signal::setCalibrationOn() {
	Signal::calibration = true;
}

void Signal::setCalibrationOff() {
	Signal::calibration = false;
}
//http://forum.arduino.cc/index.php?topic=333493.0
Signal::Signal(int pin) {
	this->pin = pin;
	this->minValue = 1023;
	this->maxValue = 0;
	this->centerValue = 1023;
	pinMode(this->pin, INPUT);

	//Kalman - start
//	this->q = 0.99;
//	this->r = 32;
//	this->p = 1023;
//	this->x = 0;
	//Kalman - end

	//this->read();
}

void Signal::read() {
//	//Kalman - start
//	this->p = this->p + this->q;
//
//	this->k = this->p / (this->p + this->r);
//	this->x = this->x + this->k * (analogRead(this->pin) - this->x);
//	this->p = (1 - this->k) * this->p;
//	this->setValue(this->x);

//	//Kalman - end

	this->setValue(analogRead(this->pin));
	if (this->getValue() > this->getMaxValue()) {
		this->setMaxValue(this->getValue());
	}

	if (this->getValue() < this->getMinValue()) {
		this->setMinValue(this->getValue());
	}

	if (Signal::getCalibrationStatus() == true) {
		this->setCenterValue(this->getValue());
	}
}

int Signal::getValue() {
	return this->value;
}
void Signal::setValue(int _value) {
	this->value = _value;
}

int Signal::getMaxValue() {
	return this->maxValue;
}
void Signal::setMaxValue(int _value) {
	this->maxValue = _value;
}

int Signal::getMinValue() {
	return this->minValue;
}
void Signal::setMinValue(int _value) {
	this->minValue = _value;
}

int Signal::getCenterValue() {
	return this->centerValue;
}
void Signal::setCenterValue(int _value) {
	this->centerValue = _value;
}

int Signal::getTiltRod() {
	if (this->getValue() > this->getCenterValue()) {

		return (int) 127 * (this->getValue() - this->getCenterValue())
				/ (this->getMaxValue() - this->getCenterValue());
	}

	if (this->getValue() < this->getCenterValue()) {
		return (int) 127 * (this->getCenterValue() - this->getValue())
				/ (this->getMinValue() - this->getCenterValue());
	}
	return 0;

}

Signal::~Signal() {
}

