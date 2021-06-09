#include "HelloWorld.h"
#include <lvgl/lvgl.h>

using namespace Pinetime::Applications::Screens;

HelloWorld::HelloWorld(Pinetime::Applications::DisplayApp* app)
  : Screen(app){
  
  label1 = lv_label_create(lv_scr_act(), nullptr);
  label2 = lv_label_create(lv_scr_act(), nullptr);
  label3 = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_user_data(label1,this);	  
  lv_label_set_text(label1, "Riproviamo.");
  lv_label_set_text(label2, "Hello World, btw");
  lv_label_set_text(label3, "Mirko fallitus");
  lv_obj_set_auto_realign(label1, true);
  lv_obj_set_auto_realign(label2, true);
  lv_obj_set_auto_realign(label3, true);
  lv_obj_align(label1, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_obj_align(label2, nullptr, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(label3, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
}

HelloWorld::~HelloWorld() {
  lv_obj_clean(lv_scr_act());
}

bool HelloWorld::Refresh() {
  return running;
}

void HelloWorld::OnValueChanged() {
}

bool HelloWorld::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
	return true;
}
