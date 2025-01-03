#include <mx.h>

#include "wifi/wifi_connection.h"

class WiFiConnectionScene : public MXScene {
 protected:
  MXObject* _label;

  inline void onInit() override {
    MXScene::onInit();
    root()->bg(mx_theme_color_primary());
    _label =
        &mx(this)->label("Connecting to WiFi...", MX_FONT_SIZE_XL).center();
  }

  inline void dispose() override {
    MXScene::dispose();
    delete _label;
    _label = nullptr;
  }

  bool _firstUpdate = true;
  inline void onUpdate() override {
    if (_firstUpdate) {
      _firstUpdate = false;
      return;
    }

    if (!WiFiConnection.isConnected()) {
      WiFiConnection.connect();
    } else {
      _label->text("WiFi connected");
    }
  }
};
