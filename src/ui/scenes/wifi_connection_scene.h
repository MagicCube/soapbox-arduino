#pragma once

#include <mx.h>

#include "wifi/wifi_connection.h"

class WiFiConnectionScene : public MXScene {
 protected:
  MXObject* _label;

  inline void onInit() override {
    MXScene::onInit();
    _label =
        &root()
             ->label(LV_SYMBOL_WIFI "  Connecting to WiFi...", MX_FONT_SIZE_XL)
             .center();
  }

  inline void dispose() override {
    MXScene::dispose();
    delete _label;
    _label = nullptr;
  }

  inline void onShown() override {
    MXScene::onShown();
    WiFiConnection.begin();
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
      _label->text(LV_SYMBOL_WIFI "  WiFi connected");
    }
  }
};
