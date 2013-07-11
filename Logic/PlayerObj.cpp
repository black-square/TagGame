#include "stdafx.h"
#include "PlayerObj.h"

PlayerObj::PlayerObj( GameField &field, TFieldPos fieldPos, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_fieldPos(fieldPos), 
  m_fieldDstPos(fieldPos),
  //m_screenPos( m_field.ToScreen(fieldPos) ),
  m_fieldMovementTimer(0.2f),
  m_pTex(pTex)
{
  ASSERT( m_field.IsValid(fieldPos) );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update( float deltaTime )
{
  if( m_fieldMovementTimer.TickWithRestart(deltaTime) )
  {
    ASSERT( m_fieldPos != m_fieldDstPos );
    m_discretePath.Next( m_fieldPos );

    if( m_fieldPos == m_fieldDstPos )
      m_fieldMovementTimer.Stop();  
  }
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Render() const
{
  Draw( *m_pTex, Rect( round<Point>(m_field.ToScreen(m_fieldPos)), Size(15, 15)) );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::MoveTo( TFieldPos pos )
{
  ASSERT( m_field.IsValid(pos) );
  
  if( m_fieldPos == pos )
    return;
    
  m_fieldDstPos = pos;
  m_discretePath.Start( m_fieldPos, pos );
  m_fieldMovementTimer.Start(); 
}
