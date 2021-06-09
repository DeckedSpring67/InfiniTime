#include "Alarm.h"

#include "Screen.h"
#include "Symbols.h"
#include "lvgl/lvgl.h"


using namespace Pinetime::Applications::Screens;


static void btnEventHandler(lv_obj_t* obj, lv_event_t event) {
  Alarm* screen = static_cast<Alarm*>(obj->user_data);
  screen->OnButtonEvent(obj, event);

}

void Alarm::createButtons() {
  btnHoursUp = lv_btn_create(lv_scr_act(), nullptr);
  btnHoursUp->user_data = this;
  lv_obj_set_event_cb(btnHoursUp, btnEventHandler);
  lv_obj_align(btnHoursUp, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 20, -80);
  lv_obj_set_height(btnHoursUp, 40);
  lv_obj_set_width(btnHoursUp, 60);
  txtHUp = lv_label_create(btnHoursUp, nullptr);
  lv_label_set_text(txtHUp, "+");

  btnHoursDown = lv_btn_create(lv_scr_act(), nullptr);
  btnHoursDown->user_data = this;
  lv_obj_set_event_cb(btnHoursDown, btnEventHandler);
  lv_obj_align(btnHoursDown, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 20, +40);
  lv_obj_set_height(btnHoursDown, 40);
  lv_obj_set_width(btnHoursDown, 60);
  txtHDown = lv_label_create(btnHoursDown, nullptr);
  lv_label_set_text(txtHDown, "-");

  btnMinutesUp = lv_btn_create(lv_scr_act(), nullptr);
  btnMinutesUp->user_data = this;
  lv_obj_set_event_cb(btnMinutesUp, btnEventHandler);
  lv_obj_align(btnMinutesUp, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 10, -80);
  lv_obj_set_height(btnMinutesUp, 40);
  lv_obj_set_width(btnMinutesUp, 60);
  txtMUp = lv_label_create(btnMinutesUp, nullptr);
  lv_label_set_text(txtMUp, "+");

  btnMinutesDown = lv_btn_create(lv_scr_act(), nullptr);
  btnMinutesDown->user_data = this;
  lv_obj_set_event_cb(btnMinutesDown, btnEventHandler);
  lv_obj_align(btnMinutesDown, lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, 10, +40);
  lv_obj_set_height(btnMinutesDown, 40);
  lv_obj_set_width(btnMinutesDown, 60);
  txtMDown = lv_label_create(btnMinutesDown, nullptr);
  lv_label_set_text(txtMDown, "-");
}

Alarm::Alarm(DisplayApp* app, Controllers::DateTime& dateTimeController): Screen(app), running{true},dateTimeController{dateTimeController}{

  time = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_76);
  lv_obj_set_style_local_text_color(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);

  lv_label_set_text_fmt(time, "%02d:%02d", dateTimeController.AlarmHour(), dateTimeController.AlarmMinute());

  lv_obj_align(time, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, -20);

  btnPlayPause = lv_btn_create(lv_scr_act(), nullptr);
  btnPlayPause->user_data = this;
  lv_obj_set_event_cb(btnPlayPause, btnEventHandler);
  lv_obj_align(btnPlayPause, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, -10);
  lv_obj_set_height(btnPlayPause, 40);
  txtPlayPause = lv_label_create(btnPlayPause, nullptr);
  if (dateTimeController.AlarmRunning()) {
    lv_label_set_text(txtPlayPause, "UNSET");
  } else {
    lv_label_set_text(txtPlayPause, "SET");
    createButtons();
  }

}

Alarm::~Alarm() {
  lv_obj_clean(lv_scr_act());
  
}

bool Alarm::Refresh() {
  return running;
}

void Alarm::OnButtonEvent(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (obj == btnPlayPause) {
      if (dateTimeController.AlarmRunning()) {
        lv_label_set_text(txtPlayPause, "SET");
	dateTimeController.UnsetAlarm();
        createButtons();

      } else if (MinutesToSet + HoursToSet > 0) {
        lv_label_set_text(txtPlayPause, "UNSET");
	dateTimeController.SetAlarm(dateTimeController.Year(),(uint8_t) dateTimeController.Month(), dateTimeController.Day(), HoursToSet, MinutesToSet);
        lv_obj_del(btnHoursDown);
        btnHoursDown = nullptr;
        lv_obj_del(btnHoursUp);
        btnHoursUp = nullptr;
        lv_obj_del(btnMinutesDown);
        btnMinutesDown = nullptr;
        lv_obj_del(btnMinutesUp);
        btnMinutesUp = nullptr;

      }
    } else {
      if (!dateTimeController.AlarmRunning()) {
        if (obj == btnMinutesUp) {
          if (MinutesToSet >= 59) {
            MinutesToSet = 0;
          } else {
            MinutesToSet++;
          }
          lv_label_set_text_fmt(time, "%02d:%02d", HoursToSet, MinutesToSet);

        } else if (obj == btnMinutesDown) {
          if (MinutesToSet == 0) {
            MinutesToSet = 59;
          } else {
            MinutesToSet--;
          }
          lv_label_set_text_fmt(time, "%02d:%02d", HoursToSet, MinutesToSet);

        } else if (obj == btnHoursUp) {
          if (HoursToSet >= 23) {
            HoursToSet = 0;
          } else {
            HoursToSet++;
          }
          lv_label_set_text_fmt(time, "%02d:%02d", HoursToSet, MinutesToSet);

        } else if (obj == btnHoursDown) {
          if (HoursToSet == 0) {
            HoursToSet = 23;
          } else {
            HoursToSet--;
          }
          lv_label_set_text_fmt(time, "%02d:%02d", HoursToSet, MinutesToSet);

        }
      }

    }
  }
}


void Alarm::setDone() {
}
