#ifndef HCI_H
#define HCI_H

#include <node.h>
#include <bluetooth/hci.h>

class HCI : node::ObjectWrap {
public:
  enum HCIState {
    HCI_STATE_DOWN,
    HCI_STATE_UNAUTHORIZED,
    HCI_STATE_UNSUPPORTED,
    HCI_STATE_UNKNOWN,
    HCI_STATE_UP
  };

  HCI();
  virtual ~HCI();

  // Node.js stuff
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> StartAdvertising(const v8::Arguments& args);
  static v8::Handle<v8::Value> StopAdvertising(const v8::Arguments& args);

private:
  v8::Local<v8::String> errnoMessage(const char* msg);
  static int getAdvType(v8::Local<v8::Value> arg);
  int getHCISocket();
  void closeHCISocket();
  HCIState getAdapterState();
  void setAdvertisingParameters(le_set_advertising_parameters_cp& params);
  void setAdvertisingData(uint8_t* data, uint8_t length);
  void setScanResponseData(uint8_t* data, uint8_t length);
  void startAdvertising(uint8_t* data, uint8_t length);
  void stopAdvertising();

  int hciSocket;
  HCIState state;
  bool socketClosed;
  struct hci_dev_info hciDevInfo;
  bool isAdvertising;

  v8::Handle<v8::Object> self;
};

#endif
