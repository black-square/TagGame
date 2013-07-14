#include "stdafx.h"
#include "GameField.h"

GameField::GameField()
{
  //Nothing
}

GameField::~GameField()
{
  DEBUG_OP( Clear() );
}

void GameField::Clear()
{
  ASSERT( IsDestroyListEmpty() );
  ForEach(GetSize(), [this]( TFieldPos pos )
  {
    if( Get(pos) )
      Set(pos);         
  });
    
  ASSERT( m_allObjects.empty() );
  DestroyDeleatedObjects(); 
}
//////////////////////////////////////////////////////////////////////////


