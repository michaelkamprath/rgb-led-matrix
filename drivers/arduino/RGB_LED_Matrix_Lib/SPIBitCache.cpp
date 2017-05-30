#include <SPI.h>
#include "SPIBitCache.h"

const unsigned char CACHE8_BIT_MASKS[8] = {
	B10000000,
	B01000000,
	B00100000,
	B00010000,
	B00001000,
	B00000100,
	B00000010,
	B00000001
}; 

const unsigned char HIGH_BIT_PRESETS[8] = {
	B11111111,
	B01111111,
	B00111111,
	B00011111,
	B00001111,
	B00000111,
	B00000011,
	B00000001
}; 


SPIBitCache::SPIBitCache(
	int cacheBytes,
	int slavePin
)	:	_cache(0),
		_cacheBytes(cacheBytes),
		_cacheByteCounter(0),
		_cacheBitCounter(0),
		_slavePin(slavePin)
{
	// set up cache
	_cache = new unsigned char[_cacheBytes];
	_curCachePtr = _cache;
	zeroCache();
	
	pinMode (_slavePin, OUTPUT);
	SPI.begin();
}

SPIBitCache::~SPIBitCache() {
	SPI.end();
	delete _cache;
}

void SPIBitCache::zeroCache() {
	memset(_cache,0,_cacheBytes);
}

void SPIBitCache::shiftOutBit( uint8_t bitValue ) {

	if (bitValue == HIGH) {
		*_curCachePtr |= CACHE8_BIT_MASKS[_cacheBitCounter];
	}
	
	_cacheBitCounter++;
	
	if (_cacheBitCounter >= 8) {
		_cacheBitCounter = 0;
		_cacheByteCounter++;
		if (_cacheByteCounter >= _cacheBytes) {
			// time to flush the cache
			flushCache();
			_cacheByteCounter = 0;
		}
		_curCachePtr = _cache + _cacheByteCounter;
	}
}

void SPIBitCache::shiftNLowBits( int bitCount ) {
	// since the buffer was initialized to 0, just increment counters
	_cacheBitCounter += bitCount;
	
	if (_cacheBitCounter >= 8) {
		int byteCounterIncrement = _cacheBitCounter/8;
		_cacheBitCounter = _cacheBitCounter%8;
	
		_cacheByteCounter += byteCounterIncrement;
		if (_cacheByteCounter >= _cacheBytes) {
			// time to flush the cache
			flushCache();
			_cacheByteCounter = 0;
			_cacheBitCounter = 0;
		}
		_curCachePtr = _cache + _cacheByteCounter;
	}
}

void SPIBitCache::shiftNHighBits( int bitCount ) {
	if ( _cacheBitCounter + bitCount > 8 ) {
		int bitsRemaining = bitCount - (8-_cacheBitCounter);
	
		// set bits remaining in current byte and then recurse 
		*_curCachePtr |= HIGH_BIT_PRESETS[_cacheBitCounter];
		
		_cacheByteCounter++;
		if (_cacheByteCounter >= _cacheBytes) {
			// time to flush the cache and must stop recursing
			flushCache();
			_cacheByteCounter = 0;
			_cacheBitCounter = 0;
			return;
		}
		_curCachePtr = _cache + _cacheByteCounter;
		_cacheBitCounter = 0;
		
		shiftNHighBits(bitsRemaining);
	} else {
		// at this point, it is just as fast to shift remaining bitsRemaining
		for (int i = 0; i < bitCount; i++) {
			shiftOutBit(HIGH);
		}
	}
}


void SPIBitCache::flushCache() {
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	digitalWrite (_slavePin, LOW);
	for (int i = 0; i < _cacheBytes; i++) {
		SPI.transfer(_cache[i]);
	}
	digitalWrite (_slavePin, HIGH);
	SPI.endTransaction();
	zeroCache();
}
