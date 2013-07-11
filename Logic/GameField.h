#ifndef GameField_h__
#define GameField_h__

#include "IGameObject.h"

class GameField
{
private:
  enum { FieldSize = 64, CellSizePx = 16 };

public:
  typedef Point TFieldPos;
  typedef Size TFieldSize;
  typedef PointBase<float> TScreenPos;  

public:
  GameField();

  void Clear();

  
  bool IsValid( int x, int y ) const
  {
    return x >= 0 && x < FieldSize && y >= 0 && y < FieldSize;
  }

  bool IsValid( TFieldPos pt ) const
  {
    return IsValid( pt.x, pt.y );
  }

  TScreenPos ToScreen( TFieldPos pt ) const
  {
    return TScreenPos( pt * CellSizePx );
  }

  TFieldPos FromScreen( TScreenPos pt ) const
  {
    return TFieldPos( pt / CellSizePx );
  }

  const IGameObject::TPtr &Get( int x, int y ) const
  {
    ASSERT( IsValid(x, y) );
    return m_field[x][y];
  }
  
  void Set( int x, int y, const IGameObject::TPtr &obj )
  {
    ASSERT( IsValid(x, y) );
    m_field[x][y] = obj;
  }
  
  const IGameObject::TPtr &Get( TFieldPos pt ) const 
  { 
    return Get( pt.x, pt.y ); 
  }
  
  void Set( TFieldPos pt, const IGameObject::TPtr &obj ) 
  { 
    Set( pt.x, pt.y, obj ); 
  } 

  TFieldSize GetSize() const
  {
    return TFieldSize(FieldSize, FieldSize);
  }

private:
  IGameObject::TPtr m_field[FieldSize][FieldSize];
};


#endif // GameField_h__
