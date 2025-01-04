#pragma once

#include <mx.h>

#define CALL_COLOR rgb(0x40D05B)
#define HANG_UP_COLOR rgb(0xFF3B2F)
#define DEFAULT_CONTACT_NAME "Aimee"

LV_IMG_DECLARE(img_call);
LV_IMG_DECLARE(img_contact_amy);

class MainScene : public MXScene {
 protected:
  MXObject* actionLabel;
  MXObject* contactLabel;
  MXObject* contactFrame;
  MXObject* contactImage;
  MXObject* callButton;
  MXObject* callIcon;

  inline void onInit() override {
    MXScene::onInit();
    root()->bg(lv_color_black()).scrollable(false);

    actionLabel =
        &root()->label("Choose contact").center_x(0, 28).text_secondary();
    contactLabel =
        &root()->label(DEFAULT_CONTACT_NAME, MX_FONT_SIZE_2XL).center_x(0, 54);
    contactFrame = &root()
                        ->object()
                        .rounded_full(144)
                        .center()
                        .border(4, rgb(0xDEDEDE))
                        .scrollable(false);
    contactImage = &root()->image(&img_contact_amy).center();
    callButton = &root()
                      ->button()
                      .rounded_full(72)
                      .center_x(0, 276)
                      .bg(CALL_COLOR)
                      .border(4);
    callIcon = &callButton->image(&img_call).center();
  }
};
