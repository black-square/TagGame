#ifndef GameField_h__
#define GameField_h__

#include "IGameObject.h"

class GameField: boost::noncopyable
{
private:
  enum { FieldSize = 64, CellSizePx = 16 };
  typedef TinyList<IGameObject, GameObjectListTag> TAllObjects;

public:
  typedef IGameObject::TFieldPos TFieldPos;
  typedef Size TFieldSize;
  typedef PointBase<float> TScreenPos;  

public:
  GameField();
  ~GameField();
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
    ASSERT( !m_field[x][y] || m_field[x][y]->GetPos() == TFieldPos(x, y) );
    return m_field[x][y];
  }
  
  void Set( int x, int y, const IGameObject::TPtr &pObj )
  {
    ASSERT( pObj );
    ASSERT( !Get(x, y) );

    m_field[x][y] = pObj;
    pObj->SetPos( TFieldPos(x, y) );
    m_allObjects.push_back( pObj.get() );
  }

  void Set( int x, int y )
  {
    ASSERT( Get(x, y) );
    m_allObjects.erase( m_field[x][y].get() );
    m_field[x][y].reset();
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

  void Set( TFieldPos pt ) 
  { 
    Set( pt.x, pt.y ); 
  } 

  TFieldSize GetSize() const
  {
    return TFieldSize(FieldSize, FieldSize);
  }
  
  template<class Fnc>
  friend void ForEach( const GameField &field, Fnc fnc );

private:
  IGameObject::TPtr m_field[FieldSize][FieldSize]; 

  //Separate object list is used for multiple Update call prevention 
  //if object was moved in the m_field on the last call
  mutable TAllObjects m_allObjects;
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
  for( auto &obj: field.m_allObjects )
  {
    ASSERT( field.Get(obj.GetPos()).get() == &obj );
    fnc( &obj );
  }
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

template<class Fnc>
void ForEachRadius( const GameField &field, GameField::TFieldPos center, GameField::TFieldSize::TValueType radius, Fnc fnc )
{
  ForEachRadius( center, radius, [&field, fnc]( Point cur )
  {
    if( !field.IsValid(cur) )
      return;

    auto &pVal = field.Get(cur);

    if( pVal )
      fnc(pVal);    
  });
}
//////////////////////////////////////////////////////////////////////////



#endif // GameField_h__
