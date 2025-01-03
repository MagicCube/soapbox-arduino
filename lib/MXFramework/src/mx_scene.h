#pragma once

#include <lvgl.h>

#include "mx_object.h"

#define MX_SCENE_DEFAULT_BG lv_color_black()

class MXScene {
 public:
  MXScene() {}

  inline static MXScene* activeScene() { return _activeScene; }

  inline bool isInitialized() const { return _initialized; }
  inline bool isActive() const { return _activeScene == this; }
  inline MXObject* root() const { return _root; }

  void begin();
  virtual inline void dispose() {
    if (_root) {
      delete _root;
      _root = nullptr;
    }
  }
  inline ~MXScene() { dispose(); }

  void activate();

  void deactivate();

  inline void update() { onUpdate(); }

  void show(lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_FADE_ON,
            uint32_t duration = 200, uint32_t delay = 0);

 protected:
  virtual MXObject* createRoot();
  virtual void onInit() { _root = createRoot(); };
  virtual void onActivating() {};
  virtual void onDeactivating() {};
  virtual void onShown() {};
  virtual void onUpdate() {};

 private:
  bool _initialized = false;
  MXObject* _root;

  static MXScene* _activeScene;
};
