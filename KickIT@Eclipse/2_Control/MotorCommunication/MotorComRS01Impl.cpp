/**
 * @file MotorComRS01Impl.cpp
 * @brief
 */
#include "../../2_Control/MotorCommunication/MotorComRS01Impl.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <iostream>

using namespace std;
extern bool defenseHomed;

MotorComRS01Impl::MotorComRS01Impl() {
	this->socketId = 0;
	this->port = "can0";
	if(mc.homingRequired){
		thread c(&MotorComRS01Impl::driverInit, this);
		c.detach();
	} else defenseHomed = true;
}

void MotorComRS01Impl::driverInit(){
	cout << "(1/6) Reset RS01:" << endl;
	frameInit(0x602, 0x8, 0x23, 0x0, 0x20, 0xB, 0x0, 0x0, 0x00, 0x0);
	frameInit(0x603, 0x8, 0x23, 0x0, 0x20, 0xB, 0x0, 0x0, 0x0, 0x0);
	sleep(this->mc.defenseSleepAfterReset);

	cout << "(2/6) Operational RS01:" << endl;
	frameInit(0x0, 0x2, 0x01, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(3/6) Ready to switch on RS01:" << endl;
	frameInit(0x202, 0x8, 0x3E, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x203, 0x8, 0x3E, 0x0, this->switchedNibbleR(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(4/6) Switching on RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x203, 0x8, 0x3F, 0x0, this->switchedNibbleR(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(5/6) Homing RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x08, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x08, this->switchedNibbleR(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(this->mc.defenseSleepAfterHoming);

	cout << "(6/6) Homed RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x203, 0x8, 0x3F, 0x0, this->switchedNibbleR(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

	defenseHomed = true;
}

void MotorComRS01Impl::linearMovement(int position){
	if(position > mc.defenseBoundaryInwards) position = mc.defenseBoundaryInwards;		//Check if position is within range
	if(position < mc.defenseBoundaryOutwards) position = mc.defenseBoundaryOutwards;	//Check if position is within range

	int pos1, pos2;
	position *= 10;
	pos1 = (position & 255);
	pos2 = (position >> 8);

	int acceleration = this->mc.defenseAccelerationTranslational;
	int aLow = acceleration & 255;
	int aHigh = acceleration >> 8;

	int deceleration = this->mc.defenseDecelerationTranslational;
	int dLow = deceleration & 255;
	int dHigh = deceleration >> 8;

	int maxSpeed = this->mc.defenseSpeedTranslational;
	int sLow = maxSpeed & 255;
	int sHigh = maxSpeed >> 8;

	frameInit(0x202, 0x8, 0x3F, 0x0, this->switchedNibbleT(), 0x09, pos1, pos2, sLow, sHigh);
	frameInit(0x302, 0x8, aLow, aHigh, dLow, dHigh, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
}

void MotorComRS01Impl::rotate(int amount) {
	int pLow,pHigh;
	amount *= 10;
	pLow = (amount & 255);
	pHigh = (amount >> 8);

	int acceleration = this->mc.defenseAccelerationRotary;
	int aLow = acceleration & 255;
	int aHigh = acceleration >> 8;

	int deceleration = this->mc.defenseDecelerationRotary;
	int dLow = deceleration & 255;
	int dHigh = deceleration >> 8;

	int maxSpeed = this->mc.defenseSpeedRotary;
	int sLow = maxSpeed & 255;
	int sHigh = maxSpeed >> 8;

	frameInit(0x203, 0x8, 0x3F, 0x0, this->switchedNibbleR(), 0x09, pLow, pHigh, 0xFF, 0xFF);
	frameInit(0x303, 0x8, aLow, aHigh, dLow, dHigh, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
}
