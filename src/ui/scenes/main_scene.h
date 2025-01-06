#pragma once

#include <mx.h>

class MainScene : public MXScene {
 protected:
  void onInit() override;

 private:
  MXObject* _actionLabel;
  MXObject* _contactLabel;
  MXObject* _contactFrame;
  MXObject* _contactImage;
  MXObject* _callButton;
  MXObject* _callIcon;
};
