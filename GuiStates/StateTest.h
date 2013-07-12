#ifndef StateTest_h__
#define StateTest_h__

#include "Gui/State.h"
#include "Logic/PlayerObj.h"
#include "Particles/ParticlesManager.h"
#include "Presentation/Effects.h"
#include "Graphics/Camera.h"
#include "Logic/IGlobalGameEvents.h"
#include "Gui/Widgets.h"

class GuiStateTest: public Gui::State, public IGlobalGameEvents
{   
public:
  typedef GuiStateTest ThisType;
 
public:
  GuiStateTest();

private:
  void OnRenderBelow( float deltaTime ) const override;
  void OnUpdate() override;
  void OnLButtonDown( Point pos ) override;

  void OnAddScore( int val ) override;
  void OnLifeLost() override;
  void OnWin() override;
  void OnLose() override;

private:
  GameField m_field;
  Texture::TPtr m_pTexGrid;

  boost::weak_ptr<PlayerObj> m_pPlayer;
  Effects::TPtr m_pEffects;
  mutable Camera m_camera;
  Gui::Label::TPtr m_pScoreLbl;
  Gui::Label::TPtr m_pLivesLbl;
  Gui::Label::TPtr m_pWinLoseLbl;
  int m_score;
  int m_lives;
};

#endif // StateTest_h__