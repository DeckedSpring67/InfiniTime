#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <cstdint>
#include "Screen.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class HelloWorld: public Screen {
      public:
        HelloWorld(DisplayApp* app);
        ~HelloWorld() override;
        bool Refresh() override;

        bool OnTouchEvent(TouchEvents event) override;

        void OnValueChanged();
      private:
	lv_obj_t* label1;
	lv_obj_t* label2;
	lv_obj_t* label3;
      };
    }
  }
}
