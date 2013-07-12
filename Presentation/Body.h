#ifndef Body_h__
#define Body_h__

#include "IBody.h"
#include "Graphics/Texture.h"

class Body: public IBody
{
public:
  explicit Body( Texture::TPtrParam pTex );

public:
  void Render( float deltaTime ) override;
  void MoveTo( TPoint dst, float time ) override;
  void SetPos( TPoint dst ) override;
  void Stop() override;

private:
  TPoint m_pos;
  TPoint m_fromPos;
  TPoint m_dstPos;
  float m_curTime;
  float m_totalTime;
  Texture::TPtr m_pTex;   
};


#endif // Body_h__


