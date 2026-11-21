#include <Arduino.h>
#include <EspNowFloodingMesh.h>

#define ESP_NOW_CHANNEL 1
#define ESP_NOW_BSID 1
//AES 128bit
unsigned char secredKey[] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE, 0xFF };

void espNowFloodingMeshRecv(const uint8_t* data, int len, uint32_t replyPrt) {
  if (len > 0) {
    if (replyPrt) { //Reply asked. Send reply
      char m[] = "POLO";
      Serial.println((char*)data); //Prints MARCO
      espNowFloodingMesh_sendReply((uint8_t*)m, sizeof(m), 0, replyPrt); //Special function for reply messages. Only the sender gets this message.
    }
    else {
      //No reply asked... All others messages are handled in here.
    }
  }
}

void setup() {
  Serial.begin(115200);
  //Set device in AP mode to begin with
  espNowFloodingMesh_RecvCB(espNowFloodingMeshRecv);
  espNowFloodingMesh_secredkey(secredKey);
  espNowFloodingMesh_begin(ESP_NOW_CHANNEL, ESP_NOW_BSID);

  espNowFloodingMesh_syncTimeAndWait();
  espNowFloodingMesh_ErrorDebugCB([](int level, const char* str) {Serial.println(str);});
}

void loop() {
  espNowFloodingMesh_loop();
  delay(10);
}
