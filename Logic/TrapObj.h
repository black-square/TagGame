#ifndef TrapObj_h__
#define TrapObj_h__

#include "IGameObject.h"
#include "Engine/Graphics/Texture.h"
#include "GameField.h"
#include "Presentation/IBody.h"

class TrapObj: public IGameObject
{
public:
  explicit TrapObj( const GameField &field, IBody::TPtrParam pBody ): m_field(field), m_pBody(pBody) {}

  Type GetType() const override { return Trap; }
  TFieldPos GetPos() const override { return m_pos; }
  void Render( float deltaTime ) const override;
  void Touch( IGameObject::TPtrParam pWho ) override;
  void SetPos( TFieldPos pos ) override;

private:
  const GameField &m_field;
  TFieldPos m_pos;
  IBody::TPtr m_pBody;
};

#endif // TrapObj_h__