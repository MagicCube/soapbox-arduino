#pragma once

class WiFiConnectionClass {
 public:
  bool isConnected();

  void begin();
  void connect();
};

extern WiFiConnectionClass WiFiConnection;
