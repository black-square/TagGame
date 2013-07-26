#ifndef Effects_h__
#define Effects_h__

#include "IEffects.h"
#include "Engine/Particles/ParticlesManager.h"
#include "Engine/Graphics/Texture.h"

class Effects: public IEffects
{
public:
  typedef boost::shared_ptr<Effects> TPtr;
  typedef const TPtr &TPtrParam;

public:
  Effects();
  void Render( float deltaTime );


public:
  void Play( TPoint pos, Effect effect ) override;

private:
  ParticlesManager m_pm;
  Texture::TPtr m_pTexExplosion;
};


#endif // Effects_h__


