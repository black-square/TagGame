#include "stdafx.h"
#include "PlayerObj.h"
#include "Audio/SoundManager.h"
#include "GameConsts.h"

PlayerObj::PlayerObj( GameField &field, Texture::TPtrParam pTex ): 
  m_field(field), 
  m_moveLogic( Editor::PlayerCellMoveTime() ),
  m_pTex(pTex)
{
    
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Update()
{
  m_moveLogic.Update( this, m_field, m_pos );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Render( float deltaTime ) const
{
  Draw( *m_pTex, Rect( round<Point>(m_field.ToScreen(m_pos)), Size(15, 15)) );  
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::MoveTo( TFieldPos pos )
{
  m_moveLogic.MoveTo(m_field, m_pos, pos );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::SetPos( TFieldPos pos ) 
{
  m_pos = pos; 
  m_moveLogic.SetPos( m_field, pos );
}
//////////////////////////////////////////////////////////////////////////

void PlayerObj::Stop()
{
  PlaySound("./_data/fall.wav"); 
}
