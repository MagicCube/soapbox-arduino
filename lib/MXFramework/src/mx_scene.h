#pragma once

#include <lvgl.h>

#include "mx_object.h"

#define MX_SCENE_DEFAULT_BG lv_color_black()

class MXScene {
 public:
  MXScene() {}

  inline bool isInitialized() const { return _initialized; }
  inline bool isActive() const { return _active; }
  inline MXObject* root() const { return _root; }

  void begin();

  MXObject* createRoot();

  void activate();

  void deactivate();

  void show(lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_FADE_ON,
            uint32_t duration = 200, uint32_t delay = 0);

 protected:
  virtual void onInit() { _root = createRoot(); };
  virtual void onActivating() {};
  virtual void onDeactivating() {};
  virtual void onShown() {};

 private:
  bool _initialized = false;
  bool _active = false;
  MXObject* _root;
};
