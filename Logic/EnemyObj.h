#ifndef EnemyObj_h__
#define EnemyObj_h__

#include "IGameObject.h"
#include "GameField.h"
#include "Engine/Graphics/Texture.h"
#include "MovementLogic.h"
#include "IGlobalGameEvents.h"

class EnemyObj: public IGameObject
{
public:
  typedef GameField::TFieldPos TFieldPos;
  typedef GameField::TScreenPos TScreenPos; 

public:
  EnemyObj( GameField &field, IBody::TPtrParam pBody, Texture::TPtrParam pTex, IGlobalGameEvents *pGameEvents );

public:
  Type GetType() const override { return IGameObject::Enemy; }
  TFieldPos GetPos() const override { return m_moveLogic.GetPos(); }
  void Update() override;
  void Render( float deltaTime ) const override;
  void SetPos( TFieldPos pos ) override;
  void PlayerVisible( IGameObject::TPtrParam pPlayer ) override;
  void PlayerCouldBeAtPos( TFieldPos pos ) override;
  void Kill( IGameObject::TPtrParam pKiller ) override;

public:
  void MoveTo( TFieldPos pos );

private:
  GameField &m_field;
  MovementLogic m_moveLogic;

  IBody::TPtr m_pBody;
  Texture::TPtr m_pTex;
  IGameObject::TWeakPtr m_pTarget;
  IGlobalGameEvents *m_pGameEvents;
};


#endif // EnemyObj_h__

