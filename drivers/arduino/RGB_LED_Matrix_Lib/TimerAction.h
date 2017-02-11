//     RGB Matrix Project - Timer Action
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

#ifndef __TIMERACTION_H__
#define __TIMERACTION_H__

class TimerAction {
private:
  unsigned long _minMicrosDelta;
  unsigned long  _lastLoopMicros;
  
protected:
  virtual void action() = 0;
public:
  TimerAction(unsigned long minMicros) {
    _minMicrosDelta = minMicros;
    _lastLoopMicros = micros();
  }

  void loop() {
    unsigned long curMicros = micros();
    // current micros is less than last micros. Since micros is 
    // represented by a 4 byte "long", the count will roll over at
    // about 1 hour 10 minutes.
    unsigned long timeSinceLast;
    if (curMicros < _lastLoopMicros) {
      timeSinceLast = (0xFFFFUL - _lastLoopMicros) + curMicros;
    }
    else {
      timeSinceLast = curMicros - _lastLoopMicros;
    }
    if ( _minMicrosDelta <= timeSinceLast ) {
      _lastLoopMicros = curMicros;
      action();
    }
  }
};

#endif //__TIMERACTION_H__
