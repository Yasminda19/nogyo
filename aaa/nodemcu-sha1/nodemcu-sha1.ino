#include <Hash.h>
 
void setup() {
  Serial.begin(115200);
 
  String result = sha1(namaString);

 String namaString = ambil();

  void ambil(){
    return Serial.read();
  }
  Serial.println();
  Serial.print(result);
 
}
 
void loop() {}
