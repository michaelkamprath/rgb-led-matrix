

#ifndef __SPICONNECTION_H__
#define __SPICONNECTION_H__

class SPIConnection {
	int _slavePin;

public:
	SPIConnection(
			int slavePin = 10
		);
	virtual ~SPIConnection();
	
	void startTransaction(void);
	void transmitByte(unsigned char data);
	void endTransaction(void);
};

#endif //__SPICONNECTION_H__
