#ifndef Body_h__
#define Body_h__

#include "IBody.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Core/TimeHelpers.hpp"

class Body: public IBody
{
public:
  explicit Body( Texture::TPtrParam pTex, IEffects::TPtrParam pEff );

public:
  void Render( float deltaTime ) override;
  void MoveTo( TPoint dst, float time ) override;
  void SetPos( TPoint dst ) override;
  void Stop() override;
  IEffects *Effects() const override { return &*m_pEff; }
  TPoint GetPos() const override { return m_pos; }
  void StartBlinking() override;
  void StopBlinking() override;

private:
  TPoint m_pos;
  TPoint m_fromPos;
  TPoint m_dstPos;
  float m_curTime;
  float m_totalTime;
  Texture::TPtr m_pTex;
  IEffects::TPtr m_pEff;
  SimpleTimer<float> m_animTmr;
  int m_curFrame;
  TimeInterval::Processor<int, TimeInterval::Continuous> m_blinkValue; 
};
//////////////////////////////////////////////////////////////////////////

class StaticBody: public IBody
{
public:
  explicit StaticBody( Texture::TPtrParam pTex );

public:
  void Render( float deltaTime ) override;
  void SetPos( TPoint dst ) override { m_pos = dst; } 
  TPoint GetPos() const override { return m_pos; }

private:
  TPoint m_pos;
  Texture::TPtr m_pTex;
  SimpleTimer<float> m_animTmr;
  int m_curFrame;
};


#endif // Body_h__


