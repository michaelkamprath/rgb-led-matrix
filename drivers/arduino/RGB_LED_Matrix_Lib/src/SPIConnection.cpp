//     RGB Matrix Project - SPIConnection
//     Copyright (C) 2017 Michael Kamprath
//
//     This file is part of RGB Matrix Project.
// 
//     RGB Matrix Project is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     RGB Matrix Project is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with RGB Matrix Project.  If not, see <http://www.gnu.org/licenses/>.
#include <Arduino.h>
#include <SPI.h>
#include "SPIConnection.h"

SPIConnection::SPIConnection(
	int slavePin
)	:	_slavePin(slavePin)
{
}

SPIConnection::~SPIConnection()
{
	SPI.end();
}

void SPIConnection::setup() {
	pinMode (_slavePin, OUTPUT);
	SPI.begin();
}

void SPIConnection::startTransaction(void) {
	SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE0));
	digitalWrite (_slavePin, LOW);
}

void SPIConnection::transmitByte(unsigned char data) {
	SPI.transfer(data);
}

void SPIConnection::endTransaction(void) {
	digitalWrite (_slavePin, HIGH);
	SPI.endTransaction();
}
