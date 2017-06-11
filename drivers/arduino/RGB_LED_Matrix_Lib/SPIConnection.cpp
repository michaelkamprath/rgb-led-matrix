#include <Arduino.h>
#include <SPI.h>
#include "SPIConnection.h"

SPIConnection::SPIConnection(
	int slavePin
)	:	_slavePin(slavePin)
{
	pinMode (_slavePin, OUTPUT);
	SPI.begin();
}

SPIConnection::~SPIConnection()
{
	SPI.end();
}
	
void SPIConnection::startTransaction(void) {
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	digitalWrite (_slavePin, LOW);
}

void SPIConnection::transmitByte(unsigned char data) {
	SPI.transfer(data);
}

void SPIConnection::endTransaction(void) {
	digitalWrite (_slavePin, HIGH);
	SPI.endTransaction();
}
