#include "stdafx.h"
#include "GameField.h"

GameField::GameField()
{
  //Nothing
}

void GameField::Clear()
{
  for( int i = 0; i < FieldSize; ++i )
    for( int j = 0; j < FieldSize; ++j )
      m_field[i][j].reset(); 
}
//////////////////////////////////////////////////////////////////////////

Point GetNextMovementPos( Point curPos, Point dstPos )
{
  //Bresenham's algorithm (http://en.wikipedia.org/wiki/Bresenham's_line_algorithm) 
  //provides better performance and accuracy, but requires storing several variables 
  //between calls
 
  typedef PointBase<float> PointF; 
  const PointF diff( dstPos - curPos );
  
  return round<Point>( PointF(curPos) + vecNormalize( diff ) ); 
}


