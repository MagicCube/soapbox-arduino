#include "mx_scene.h"

void MXScene::begin() {
  if (isInitialized()) {
    return;
  }
  onInit();
  _initialized = true;
}

MXObject* MXScene::createRoot() {
  auto root = new MXObject();
  root->bg(MX_SCENE_DEFAULT_BG);
  return root;
}

void MXScene::activate() {
  if (isActive()) {
    return;
  }
  onActivating();
  _active = true;
}

void MXScene::deactivate() {
  if (!isActive()) {
    return;
  }
  onDeactivating();
  _active = false;
}

void MXScene::show(lv_scr_load_anim_t animation, uint32_t duration,
                   uint32_t delay) {
  if (!isActive()) {
    activate();
  }
  if (animation == LV_SCR_LOAD_ANIM_NONE) {
    lv_screen_load(root()->lv_object());
  } else {
    lv_screen_load_anim(root()->lv_object(), animation, duration, delay, false);
  }
  onShown();
}
