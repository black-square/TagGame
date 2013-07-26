#include "stdafx.h"
#include "Effects.h"
#include "Engine/Audio/SoundManager.h"

//////////////////////////////////////////////////////////////////////////

static void MakeExplosion( ParticlesManager &pm, Point pos, Texture::TPtrParam pTex )
{
  Particle::Param rgParams[4];

  const float scale = 1.5f;
  const float lt = 0.3f;
  const float dl = 0.01f;
  const float alpha = 0.9f;

  rgParams[0].scaleEnd = scale; 
  rgParams[0].lifeTime = lt;
  rgParams[0].alphaMiddle = alpha;

  rgParams[1].hideDelay = dl;
  rgParams[1].scaleEnd = scale; 
  rgParams[1].lifeTime = lt + rgParams[1].hideDelay;
  rgParams[1].alphaMiddle = alpha;
  rgParams[1].texFrame = 1;

  rgParams[2].hideDelay = dl * 2;
  rgParams[2].scaleEnd = scale; 
  rgParams[2].lifeTime = lt + rgParams[2].hideDelay;
  rgParams[2].alphaMiddle = alpha;
  rgParams[2].texFrame = 2;

  rgParams[3].hideDelay = dl * 3;
  rgParams[3].scaleEnd = 1.5f * (scale); 
  rgParams[3].lifeTime = 1.5f * (lt + rgParams[3].hideDelay);
  rgParams[3].alphaMiddle = alpha;
  rgParams[3].texFrame = 3;

  pm.Emit( pos, pTex, rgParams, ARRAY_SIZE(rgParams) );
}
//////////////////////////////////////////////////////////////////////////

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


