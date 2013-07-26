#include "stdafx.h"
#include "Engine/IEngineParams.h"
#include "GameConsts.h"
#include "GuiStates/StateMain.h"

struct EngineParamsImpl: IEngineParams
{
  Size GetInitialScreenSize() const override
  {
    return Editor::VisibleFieldSizePx();  
  }

  float GetUpdateTimeDelta() const override
  {
    return Editor::LogicUpdateTime();
  }

  Gui::State::TPtr MakeMainState() const override
  {
    return boost::make_shared<GuiStateMain>();
  }
};
//////////////////////////////////////////////////////////////////////////

IEngineParams *EngineParams()
{
  static EngineParamsImpl params;
  return &params; 
}



