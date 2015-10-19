/*
 * Signal.cpp
 *
 *  Created on: 18 paź 2015
 *      Author: plysiu
 */

#include "Signal.h"
bool Signal::calibration = true;

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
	this->value = START_VALUE;
	this->minValue = 1023;
	this->maxValue = 0;
	this->centerValue = 0;
	pinMode(this->pin, INPUT);
}

void Signal::read() {
	this->value = analogRead(this->pin);
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

	if (this->getValue() == this->getCenterValue()) {
		return 0;
	}
}

Signal::~Signal() {
}

