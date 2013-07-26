#ifndef GameField_h__
#define GameField_h__

#include "Engine/Logic/GameFieldBase.hpp"
#include "IGameObject.h"
#include "GameConsts.h"


class GameField: public GameFieldBase<IGameObject>
{
public:
  typedef PointBase<float> TScreenPos;  
  typedef SizeBase<float> TScreenSize;  

public:
  GameField(): GameFieldBase( Editor::GetFieldSize() ) {} 

  TScreenPos ToScreen( TFieldPos pt ) const
  {
    return TScreenPos( pt * Editor::GetCellSizePx() );
  }

  TScreenPos ToScreenCenter( TFieldPos pt ) const
  {
    return TScreenPos( pt * Editor::GetCellSizePx() + TFieldPos( Editor::GetCellSizePx(), Editor::GetCellSizePx() ) / 2 );
  }

  TFieldPos FromScreen( TScreenPos pt ) const
  {
    return TFieldPos( pt / static_cast<float>(Editor::GetCellSizePx()) );
  }
};
//////////////////////////////////////////////////////////////////////////

#endif // GameField_h__
