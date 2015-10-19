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

bool Signal::setCalibrationOn() {
	Signal::calibration = true;
	return Signal::getCalibrationStatus();
}

bool Signal::setCalibrationOff() {
	Signal::calibration = false;
	return Signal::getCalibrationStatus();
}

Signal::Signal(int pin) {
	this->pin = pin;
	this->minValue = 1023;
	this->maxValue = 0;
	this->centerValue = 0;
	pinMode(this->pin, INPUT);

	//Kalman - start
	this->q = 0.125;
	this->r = 32;
	this->p = 1023;
	this->x = 0;
	//Kalman - end

	this->read();
}

void Signal::read() {
	//Kalman - start
	this->p = this->p + this->q;

	this->k = this->p / (this->p + this->r);
	this->x = this->x + this->k * (analogRead(this->pin) - this->x);
	this->p = (1 - this->k) * this->p;
	//Kalman - end

	this->setValue((int) this->x);
	if (this->value > this->maxValue) {
		this->maxValue = this->value;
	}

	if (this->value < this->minValue) {
		this->minValue = this->value;
	}

	if (Signal::getCalibrationStatus() == true) {
		this->centerValue = this->value;
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
int Signal::getMinValue() {
	return this->minValue;
}
int Signal::getCenterValue() {
	return this->centerValue;
}

int Signal::getTiltRod() {
	if (this->getValue() > this->getCenterValue()) {
		return (int) ((100 * (this->getValue() - this->getCenterValue()))
				/ (this->getMaxValue() - this->getCenterValue()));
	}

	if (this->getValue() < this->getCenterValue()) {
		return (int) ((-100 * (this->getCenterValue() - this->getValue()))
				/ (this->getCenterValue() - this->getMinValue()));
	}
	return 0;
}

Signal::~Signal() {
}

