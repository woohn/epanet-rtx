//
//  IrregularClock.cpp
//  epanet-rtx
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#include <iostream>
#include "IrregularClock.h"

using namespace RTX;

IrregularClock::IrregularClock(PointRecord::sharedPointer pointRecord, std::string name) : Clock(0,0), _name(name) {
  if (pointRecord) {
    _pointRecord = pointRecord;
  }
  else {
    std::cerr << "could not construct IrregularClock object: no Point Record provided\n";
  }
  
}

IrregularClock::~IrregularClock() {
  
}

#pragma mark - Public Methods

bool IrregularClock::isCompatibleWith(Clock::sharedPointer clock) {
  // we're irregular, so we're compatible with anything... TODO - but only if the PointRecord is read/write...
  return true;
}

bool IrregularClock::isValid(time_t time) {
  if (_pointRecord->isPointAvailable(_name, time)) {
    return true;
  }
  else {
    return false;
  }
}


time_t IrregularClock::timeAfter(time_t time) {
  Point aPoint;
  aPoint = _pointRecord->pointAfter(_name, time);
  if (aPoint.isValid()) {
    return aPoint.time();
  }
  else {
    //std::cerr << "irregular clock cannot find time after " << time << std::endl;
    return 0;
    // TODO -- what if there's no data here?
  }
}

time_t IrregularClock::timeBefore(time_t time) {
  Point aPoint;
  aPoint = _pointRecord->pointBefore(_name, time);
  if (aPoint.isValid()) {
    return aPoint.time();
  }
  else {
    //std::cerr << "previous time not found" << std::endl;
    return 0;
    // TODO -- what if there's no data here?
  }
}



#pragma mark - Protected Methods
std::ostream& IrregularClock::toStream(std::ostream &stream) {
  stream << "Irregular Clock based on Point Record:\n";
  stream << *_pointRecord;
  return stream;
}