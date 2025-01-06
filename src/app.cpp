// Scenes
#include "ui/scenes/main_scene.h"
// #include "ui/scenes/wifi_connection_scene.h"

MainScene *mainScene;
// WiFiConnectionScene wifiConnectionScene;

void app_main() {
  mainScene = new MainScene();
  mainScene->show();
}
