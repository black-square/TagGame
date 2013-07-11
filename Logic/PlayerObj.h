#ifndef PlayerObj_h__
#define PlayerObj_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Core/TimeHelpers.hpp"
#include "Graphics/Texture.h"
#include "Core/DiscretePath.hpp"

class PlayerObj: public IGameObject
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  PlayerObj( GameField &field, TFieldPos fieldPos, Texture::TPtrParam pTex );

public:
  void Update( float deltaTime ) override;
  void Render() const override;

public:
  void MoveTo( TFieldPos pos );

private:
  GameField &m_field;
  TFieldPos m_fieldPos;
  TFieldPos m_fieldDstPos;
  DiscretePath<TFieldPos::TValueType> m_discretePath;

  SimpleTimer<float> m_fieldMovementTimer;
  SimpleTimer<float> m_screenMovementTimer;
  Texture::TPtr m_pTex;
};

#endif // PlayerObj_h__
