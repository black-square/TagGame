#ifndef EnemyObj_h__
#define EnemyObj_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Graphics/Texture.h"
#include "MovementLogic.h"

class EnemyObj: public IGameObject
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  EnemyObj( GameField &field, Texture::TPtrParam pTex );

public:
  Type GetType() const override { return IGameObject::Enemy; }
  TFieldPos GetPos() const override { return m_pos; }
  void Update() override;
  void Render( float deltaTime ) const override;
  void SetPos( TFieldPos pos ) override;
  void PlayerVisible( IGameObject *pPlayer ) override;
  void PlayerCouldBeAtPos( TFieldPos pos ) override;

public:
  void MoveTo( TFieldPos pos );

private:
  GameField &m_field;
  TFieldPos m_pos;
  MovementLogic m_moveLogic;

  Texture::TPtr m_pTex;
  IGameObject::TWeakPtr m_pTarget;
};


#endif // EnemyObj_h__
