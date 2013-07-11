#ifndef PlayerObj_h__
#define PlayerObj_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Graphics/Texture.h"
#include "MovementLogic.h"


class PlayerObj: public IGameObject
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  PlayerObj( GameField &field, Texture::TPtrParam pTex );

public:
  Type GetType() const override { return IGameObject::Player; }
  TFieldPos GetPos() const override { return m_pos; }
  void Update() override;
  void Render( float deltaTime ) const override;
  void SetPos( TFieldPos pos ) override;
  void Stop() override;

public:
  void MoveTo( TFieldPos pos );

private:
  GameField &m_field;
  TFieldPos m_pos;
  MovementLogic m_moveLogic;

  Texture::TPtr m_pTex;
};

#endif // PlayerObj_h__
