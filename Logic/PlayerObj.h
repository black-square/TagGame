#ifndef PlayerObj_h__
#define PlayerObj_h__

#include "IGameObject.h"
#include "GameField.h"
#include "MovementLogic.h"
#include "Presentation/IBody.h"
#include "Graphics/Texture.h"


class PlayerObj: public IGameObject
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  PlayerObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex );

public:
  Type GetType() const override { return IGameObject::Player; }
  TFieldPos GetPos() const override { return m_moveLogic.GetPos(); }
  void Update() override;
  void Render( float deltaTime ) const override;
  void SetPos( TFieldPos pos ) override;
  void Stop() override;

public:
  void MoveTo( TFieldPos pos );
  const IBody *GetBody() const { return &*m_pBody; }

private:
  GameField &m_field;
  MovementLogic m_moveLogic;

  IBody::TPtr m_pBody;
  Texture::TPtr m_pTex;
};

#endif // PlayerObj_h__
