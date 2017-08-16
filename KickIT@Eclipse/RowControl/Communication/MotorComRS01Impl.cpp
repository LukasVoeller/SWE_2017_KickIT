#include "../Communication/MotorComRS01Impl.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <thread>

using namespace std;

MotorComRS01Impl::MotorComRS01Impl(Row r) {
	this->socketId = 0;
	this->port = "can0";
	this->row = r;
	thread c(&MotorComRS01Impl::driverInit, this);
	c.detach();
}

void MotorComRS01Impl::driverInit(){
	cout << "(1/6) Reset RS01:" << endl;
	frameInit(0x602, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x603, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00);
	sleep(20);

	cout << "(2/6) Operational RS01:" << endl;
	frameInit(0x00, 0x2, 0x01, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(3/6) Ready to switch on RS01:" << endl;
	frameInit(0x202, 0x8, 0x3E, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3E, 0x00, this->switchedNibbleR(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(4/6) Switching on RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, this->switchedNibbleR(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(5/6) Homing RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x08, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x08, this->switchedNibbleR(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(25);

	cout << "(6/6) Homed RS01:" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, this->switchedNibbleR(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void MotorComRS01Impl::linearMovement(int position){

	if(position > 280) position = 280;			//Check if position is within range
	if(position < 20) position = 20;			//Check if position is within range

	//cout << "RS is moving to: " << position << endl;

	int pos1, pos2;
	position *= 10;
	pos1 = (position & 255);
	pos2 = (position >> 8);

	frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x09, pos1, pos2, 0xBB, 0x40);
	frameInit(0x302, 0x8, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	/*frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x09, pos1, pos2, 0xBB, 0x40);
	frameInit(0x302, 0x8, 0x2C, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);*/

	/*Backup
	frameInit(0x202, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x09, pos1, pos2, 0xBB, 0x08);
	frameInit(0x302, 0x8, 0x2C, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(3);
	*/
}

void MotorComRS01Impl::rotate(int amount) {
	int pos5,pos6;
	amount *= 10;
	pos5 = (amount & 255);
	pos6 = (amount >> 8);

	frameInit(0x203, 0x8, 0x3F, 0x00, this->switchedNibbleR(), 0x09, pos5, pos6, 0xFF, 0xFF);
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}
