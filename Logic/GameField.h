#ifndef GameField_h__
#define GameField_h__

#include "IGameObject.h"

class GameField
{
private:
  enum { FieldSize = 64, CellSizePx = 16 };

public:
  typedef IGameObject::TFieldPos TFieldPos;
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
  
  void Set( int x, int y, const IGameObject::TPtr &pObj )
  {
    ASSERT( pObj );
    ASSERT( !Get(x, y) );

    m_field[x][y] = pObj;
    pObj->SetPos( TFieldPos(x, y) );
  }

  void Move( TFieldPos from, TFieldPos to )
  {
    ASSERT( Get(from) && !Get(to) );
    m_field[to.x][to.y] = std::move( m_field[from.x][from.y] );
  }
  
  const IGameObject::TPtr &Get( TFieldPos pt ) const 
  { 
    return Get( pt.x, pt.y ); 
  }
  
  void Set( TFieldPos pt, const IGameObject::TPtr &pObj ) 
  { 
    Set( pt.x, pt.y, pObj ); 
  } 

  TFieldSize GetSize() const
  {
    return TFieldSize(FieldSize, FieldSize);
  }

private:
  IGameObject::TPtr m_field[FieldSize][FieldSize];
};
//////////////////////////////////////////////////////////////////////////

template<class Fnc>
void ForEach( GameField::TFieldSize size, Fnc fnc )
{
  GameField::TFieldPos cur;

  for( cur.x = 0; cur.x < size.w; ++cur.x )
    for( cur.y = 0; cur.y < size.h; ++cur.y )
      fnc( cur );
}
//////////////////////////////////////////////////////////////////////////

template<class Fnc>
void ForEach( const GameField &field, Fnc fnc )
{
  ForEach( field.GetSize(), [&field, fnc] ( GameField::TFieldPos cur ) 
  {
    auto &pVal = field.Get(cur);

    if( pVal )
      fnc( pVal );
  });
}
//////////////////////////////////////////////////////////////////////////

template<class Fnc>
void ForEachRadius( GameField::TFieldPos center, GameField::TFieldSize::TValueType radius, Fnc fnc )
{
  const float radiusf = radius - 0.5f;
  const float radius2 = radiusf * radiusf;
  GameField::TFieldPos cur;

  for( cur.x = center.x - radius; cur.x <= center.x + radius; ++cur.x )
    for( cur.y = center.y - radius; cur.y <= center.y + radius; ++cur.y )
      if( vecLengthSquared(PointBase<float>(cur - center)) <= radius2 )
        fnc( cur );
}
//////////////////////////////////////////////////////////////////////////


#endif // GameField_h__
