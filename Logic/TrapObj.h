#ifndef TrapObj_h__
#define TrapObj_h__

#include "IGameObject.h"
#include "Graphics/Texture.h"
#include "GameField.h"

class TrapObj: public IGameObject
{
public:
  explicit TrapObj( const GameField &field, Texture::TPtrParam pTex ): m_field(field), m_pTex(pTex) {}

  Type GetType() const override { return Trap; }
  void Render() const override;
  void Touch( IGameObject *pWho ) override;
  void SetPos( TFieldPos pos ) override { m_pos = pos; }

private:
  const GameField &m_field;
  TFieldPos m_pos;
  Texture::TPtr m_pTex;
};

#endif // TrapObj_h__