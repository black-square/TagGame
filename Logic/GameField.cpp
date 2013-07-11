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


