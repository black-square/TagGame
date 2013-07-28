#include "stdafx.h"
#include "TrapObj.h"

void TrapObj::Render( float deltaTime ) const
{
  m_pBody->Render( deltaTime );
}
//////////////////////////////////////////////////////////////////////////

void TrapObj::Touch( IGameObject::TPtrParam pWho )
{
  ASSERT( pWho != 0 );

  switch( pWho->GetType() )
  {
  case Player:
    pWho->Stop();
    break;

  case Enemy:
    pWho->Kill( m_field.Get(this) );
    break;
      
  default:
    break;
  }
}
//////////////////////////////////////////////////////////////////////////

void TrapObj::SetPos( TFieldPos pos ) 
{ 
  m_pos = pos;
  m_pBody->SetPos( m_field.ToScreen(m_pos) );
}
