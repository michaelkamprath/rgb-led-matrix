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
