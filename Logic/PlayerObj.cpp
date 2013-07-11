#include "stdafx.h"
#include "PlayerObj.h"
#include "Audio/SoundManager.h"

PlayerObj::PlayerObj( GameField &field, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_fieldMovementTimer(0.2f),
  m_pTex(pTex)
{
    
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update( float deltaTime )
{
  if( m_fieldMovementTimer.TickWithRestart(deltaTime) )
  {
    ASSERT( m_pos != m_dstPos );

    TFieldPos nextPos( m_pos );

    m_discretePath.Next( nextPos );

    if( nextPos == m_dstPos )
      m_fieldMovementTimer.Stop();
         
    auto &pObj = m_field.Get( nextPos );

    if( pObj )
      pObj->Touch(this);
    else
    {
      m_field.Move( m_pos, nextPos );
      m_pos = nextPos;
    }     
  }
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Render() const
{
  Draw( *m_pTex, Rect( round<Point>(m_field.ToScreen(m_pos)), Size(15, 15)) );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::MoveTo( TFieldPos pos )
{
  ASSERT( m_field.IsValid(pos) );
  
  if( m_pos == pos )
    return;
    
  m_dstPos = pos;
  m_discretePath.Start( m_pos, pos );
  m_fieldMovementTimer.Start(); 
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::SetPos( TFieldPos pos ) 
{
  ASSERT( m_field.IsValid(pos) );
  m_pos = pos; 
  m_dstPos = pos;
  m_fieldMovementTimer.Stop();
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Stop()
{
  SetPos(m_pos);
  PlaySound("./_data/click.wav"); 
}
