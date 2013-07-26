#include "stdafx.h"
#include "Effects.h"
#include "Engine/Audio/SoundManager.h"


Effects::Effects()
{
  m_pTexExplosion = boost::make_shared<Texture>( "./_data/explosion.png", 4 );
}
//////////////////////////////////////////////////////////////////////////

void Effects::Play( TPoint pos, Effect effect )
{
  switch(effect)
  {
    case IEffects::PlayerStoped:
      PlaySound("./_data/fall.wav");
      break;

    case IEffects::EnemyDied:
    case IEffects::PlayerDied:
      PlaySound("./_data/expl.wav");
      MakeExplosion( m_pm, round<Point>(pos), m_pTexExplosion );
      break;

    default:
      ASSERT(false);
  };
}
//////////////////////////////////////////////////////////////////////////

void Effects::Render( float deltaTime )
{
  m_pm.Update(deltaTime);
  m_pm.Render();
}


