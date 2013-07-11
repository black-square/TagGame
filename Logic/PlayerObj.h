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
  PlayerObj( GameField &field, Texture::TPtrParam pTex );

public:
  Type GetType() const override { return IGameObject::Player; }
  void Update( float deltaTime ) override;
  void Render() const override;
  void SetPos( TFieldPos pos ) override;
  void Stop() override;

public:
  void MoveTo( TFieldPos pos );

private:
  GameField &m_field;
  TFieldPos m_pos;
  TFieldPos m_dstPos;
  DiscretePath<TFieldPos::TValueType> m_discretePath;

  SimpleTimer<float> m_fieldMovementTimer;
  Texture::TPtr m_pTex;
};

#endif // PlayerObj_h__
