#pragma once

#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "systemtask/SystemTask.h"
#include "../LittleVgl.h"

#include "components/datetime/DateTimeController.h"

namespace Pinetime::Applications::Screens {
  
  
  class Alarm: public Screen {
  public:
    
    enum class Modes {
      Normal, Done
    };
    
    Alarm(DisplayApp* app, Controllers::DateTime& dateTimeController);
    
    ~Alarm() override;
    
    bool Refresh() override;
    
    void setDone();
    
    void OnButtonEvent(lv_obj_t* obj, lv_event_t event);
  
  private:
    
    bool running;
    uint8_t HoursToSet = 0;
    uint8_t MinutesToSet = 0;
    Controllers::DateTime& dateTimeController;
    
    void createButtons();
    
    lv_obj_t* time, * msecTime, * btnPlayPause, * txtPlayPause, * btnHoursUp, * btnHoursDown, * btnMinutesUp, * btnMinutesDown, * txtHUp,
        * txtHDown, * txtMUp, * txtMDown;
  };
}
