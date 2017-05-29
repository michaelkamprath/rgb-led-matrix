//     RGB Matrix Project - SPIBitCache
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

#ifndef __SPIBITCACHE_H__
#define __SPIBITCACHE_H__

/***
 * This class allows us to use SPI out 1 bit at a time by creating a local buffer
 * Great reference for SPI:
 *		https://arduino.stackexchange.com/questions/16348/how-do-you-use-spi-on-an-arduino
 *
 * This class only supports multiples 8 bit transfers. Plan accordingly
 * with MSB padding if needed.
 *
 */


class SPIBitCache {
private:	
	unsigned char *_cache;
	unsigned char *_curCachePtr;
	int _cacheBytes;
	int _cacheByteCounter;
	int _cacheBitCounter;
	int _slavePin;
	
	void zeroCache();
public:
	
	SPIBitCache(
			int cacheBytes,
			int slavePin = 10
		);
	virtual ~SPIBitCache();
	
	// Send a HIGH or LOW value to the SPI bus
	void shiftOutBit( uint8_t bitValue);
	
	void shiftNLowBits( int bitCount );
	void shiftNHighBits( int bitCount );
	
	// should never need to call this as shiftOutBits calls when cache is full.
	void flushCache();
};

#endif // __SPIBITCACHE_H__
