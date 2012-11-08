//
//  PointContainer.h
//  epanet-rtx
//
//  Created by the EPANET-RTX Development Team
//  See README.md and license.txt for more information
//  

#ifndef epanet_rtx_PointContainer_h
#define epanet_rtx_PointContainer_h

#define POINTCONTAINER_CACHESIZE 10000;

#include <map>
#include <time.h>
#include <vector>
#include "Point.h"
#include "PointRecord.h"
#include "rtxMacros.h"

namespace RTX {
    
  //class PointContainerIterator;
  
  
  /*! \class PointContainer 
      \brief A Container class for storing Points, ordered in time. 
  
      Derived classes may choose to extend the storage functionality for data persistence or acquisition.
  */
  
  class PointContainer {
  public:
    RTX_SHARED_POINTER(PointContainer);
    PointContainer();
    virtual ~PointContainer();
     
    bool isEmpty();
    size_t size();
    
    virtual void hintAtRange(time_t start, time_t end) {};
    virtual void hintAtBulkInsertion(time_t start, time_t end) {};
    //virtual std::vector< Point > pointsInRange(time_t start, time_t end);
    virtual bool isPointAvailable(time_t time);
    virtual Point findPoint(time_t time);
    virtual Point pointAfter(time_t time);
    virtual Point pointBefore(time_t time);
    virtual Point firstPoint();
    virtual Point lastPoint();
    virtual long int numberOfPoints();
    virtual void insertPoint(Point point);
    virtual void insertPoints(std::vector< Point > points);
    
    virtual void setCacheSize(int size);
    int cacheSize();
    
    virtual void reset();
    virtual std::ostream& toStream(std::ostream &stream);
    
  private:
    //typedef std::map<time_t,Point> PointMap_t;
    //PointMap_t _points;
    typedef std::pair<double,double> PointPair_t;
    typedef std::map<time_t, PointPair_t > PairMap_t;
    PairMap_t _pairMap;
    int _cacheSize;
    
    Point makePoint(PairMap_t::iterator iterator);
  };
  
  std::ostream& operator<< (std::ostream &out, PointContainer &pointContainer);

}

#endif
