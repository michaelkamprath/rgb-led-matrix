//     RGB Matrix Project - RGBAnimation
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
#include "RGBAnimation.h"
#include "Glyph.h"
#include "RGBLEDMatrix.h"

#pragma mark - RGBAnimationBase

RGBAnimationBase::RGBAnimationBase(
			unsigned long intervalMicros,
			RGBLEDMatrix& matrix,
			int maxSequenceIndex
	) :	TimerAction(intervalMicros),
		_originRow(0),
		_originColumn(0),
		_matrix(matrix),
		_sequenceIndex(0),
		_maxSequenceIndex(maxSequenceIndex),
		_rightPadSize(0),
		_rightPadColor(BLACK_COLOR),
		_leftPadSize(0),
		_leftPadColor(BLACK_COLOR)
{

}


void RGBAnimationBase::action() 
{	
	this->incrementSequenceIndex();
	this->update();
}

void RGBAnimationBase::update() {
	_matrix.startDrawing();
	this->draw(_matrix.image());
	if (_rightPadSize > 0) {
		int imgRightColumn = this->getOriginColumn() + this->columns();
		for (	int x = imgRightColumn >= 0 ? imgRightColumn : 0;
				(x < _matrix.image().columns())&&(x < imgRightColumn + _rightPadSize);
				x++ )
		{
			for (int y = 0; y < _matrix.image().rows(); y++) {
				_matrix.image().pixel(y,x) = _rightPadColor;
			}
		}
	}
	if (_leftPadSize > 0) {
		int imgLeftColumn = this->getOriginColumn();
		for (	int x = imgLeftColumn - _leftPadSize >= 0 ? imgLeftColumn - _leftPadSize : 0;
				(x < _matrix.image().columns())&&(x < imgLeftColumn);
				x++ )
		{
			for (int y = 0; y < _matrix.image().rows(); y++) {
				_matrix.image().pixel(y,x) = _leftPadColor;
			}
		}
	}
	_matrix.stopDrawing();
}

void RGBAnimationBase::setRightPad( int padSize, ColorType padColor ) {
	_rightPadSize = padSize;
	_rightPadColor = padColor;
}
void RGBAnimationBase::setLeftPad( int padSize, ColorType padColor ) {
	_leftPadSize = padSize;
	_leftPadColor = padColor;
}

#pragma mark - GlyphSequenceAnimation

GlyphSequenceAnimation::GlyphSequenceAnimation(
			RGBLEDMatrix& matrix,
			const Frame* frameArray,
			int	frameArraySize
	) :	RGBAnimationBase(1000,matrix,frameArraySize),
		_frameArray(frameArray),
		_frameArraySize(frameArraySize),
		_lastDrawnSequenceIdx( 0 )
{
}
		
void GlyphSequenceAnimation::draw( RGBImage& buffer)
{
	int idx = this->getSequenceIndex();

	buffer.drawGlyph(
		*_frameArray[idx].glyph,
		this->getOriginRow(),
		this->getOriginColumn(),
		_frameArray[idx].foreground,
		_frameArray[idx].background
	);

	// this function may be called multiple times in a given interval. Only
	// 
	if ( idx != _lastDrawnSequenceIdx ) {
		this->setIntervalMillis(_frameArray[idx].interval);
	}
	_lastDrawnSequenceIdx = idx;
}

int GlyphSequenceAnimation::rows() const
{
	return _frameArray[0].glyph->rows();
}
int GlyphSequenceAnimation::columns() const
{
	return _frameArray[0].glyph->columns();
}


