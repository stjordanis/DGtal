#pragma once

/**
 * @file ImageContainerBySTLMap.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/15
 *
 * Header file for module ImageContainerBySTLMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageContainerBySTLMap_RECURSES)
#error Recursive header files inclusion detected in ImageContainerBySTLMap.h
#else // defined(ImageContainerBySTLMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageContainerBySTLMap_RECURSES

#if !defined ImageContainerBySTLMap_h
/** Prevents repeated inclusion of headers. */
#define ImageContainerBySTLMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class ImageContainerBySTLMap
  /**
   * Description of class 'ImageContainerBySTLMap' <p>
   * Aim:
   * \todo Documentation
   * @example test_Image.cpp
   */

  template <typename Point, typename ValueType>
  class ImageContainerBySTLMap: public map<Point,ValueType>
  {

  public:
    typedef typename map<Point,ValueType>::size_type TSizeType;
    typedef typename map<Point,ValueType>::iterator Iterator;
    typedef typename map<Point,ValueType>::const_iterator ConstIterator;

    ///\todo create span iterators
    class SpanIterator: public Iterator
    {
      friend class ImageContainerBySTLMap<Point,ValueType>;

    public:
      SpanIterator( const Point & p ,
		    const std::size_t aDim ,
		    ImageContainerBySTLMap<Point,ValueType> *aMap ) :   
	myStartingPoint( p ),	myDimension ( aDim ), 	myMap ( aMap )
      {
	myPos = myMap->find( p );
      }


      const ValueType & operator*() const
      {
	return (*myPos).second;
      }
      
      /**
       * Implements the next() method
       *
       **/
      void next()
      {
	while ((myPos != myMap->end()) && 
	       ( (*myPos).first.at(myDimension) != myStartingPoint.at(myDimension)))
	  {
	    myPos++;
	  }
      }

      /**
       * Implements the prev() method
       *
       **/
      void prev()
      {
	while ((myPos != myMap->end()) && 
	       ( (*myPos).first.at(myDimension) != myStartingPoint.at(myDimension)))
	  {
	    myPos--;
	  }
      }      

      /**
       * Operator ++ (++it)
       *
       */
      SpanIterator &operator++()
      {
	this->next();
	return *this;
      }

      /**
       * Operator ++ (it++)
       *
       */
      SpanIterator &operator++ ( int )
      {
	SpanIterator tmp = *this;
	++*this;
	return tmp;
      }


      /**
       * Operator -- (--it)
       *
       */
      SpanIterator &operator--()
      {
	this->prev();
	return *this;
      }

      /**
       * Operator -- (it--)
       *
       */
      SpanIterator &operator-- ( int )
      {
	SpanIterator tmp = *this;
	--*this;
	return tmp;
      }

    private:
      
      ///Copie of starting point
      Point myStartingPoint;
      
      ///Current  position in the built-in iterator
      Iterator myPos;

      /// Copy of the underlying images
      ImageContainerBySTLMap<Point,ValueType> *myMap;

      ///Dimension on which the iterator must iterate
      std::size_t myDimension;

    };

    ImageContainerBySTLMap(const Point &aPointA,
			   const Point &aPointB ) {};

    ~ImageContainerBySTLMap() {};

    ValueType operator()(const Point &aPoint) throw( std::bad_alloc )
    {
      Iterator it = this->find( aPoint );
      if ( it == this->end() )
	throw std::bad_alloc();
      else
	return this->operator[]( aPoint );
    }


    ValueType operator()(const Iterator &it) throw( std::bad_alloc )
    {
      if ( it == this->end() )
	throw std::bad_alloc();
      else
	return (*it).second;
    }
    

    void setValue(const Point &aPoint, const ValueType &aValueType)
    {
      Iterator it  = find( aPoint ) ;
      if (it != this->end() )
	(*it).second = aValueType;
    }


    void setValue(SpanIterator &it, const ValueType &aValueType)
    {
      ASSERT("NOT-YET-IMPLEMENTED");
    }

    void setValue(Iterator &it, const ValueType &aValueType)
    {
      it->second = aValueType;
    }


    SpanIterator span_begin(const Point &aPoint, const std::size_t aDimension)
    {
      return SpanIterator ( aPoint, aDimension, this);
    }

    SpanIterator span_end(const Point &aPoint,const std::size_t aDimension)
    {
      Point tmp = aPoint;
      tmp.at( aDimension ) = myLowerBound.at( aDimension ) +
	myUpperBound.at( aDimension ) - 
	myLowerBound.at( aDimension ) + 1;
      return SpanIterator( tmp, aDimension, this);
    }

    void allocate(const std::size_t aSize) {};

  private:
    
    Point myLowerBound;
    Point myUpperBound;
  };

} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageContainerBySTLMap_h

#undef ImageContainerBySTLMap_RECURSES
#endif // else defined(ImageContainerBySTLMap_RECURSES)