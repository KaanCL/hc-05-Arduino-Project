#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0,1); // RX || TX

int gazSensorPin = A0;
int sensorValue = 0;
int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Serial Monitor iletişimi için
  BTSerial.begin(38400); // Bluetooth modülünün baud hızını ayarlıyoruz
  Serial.println("Bluetooth ile iletişim başlatıldı.");
}

void loop() {
  // Gaz sensöründen veri oku
  sensorValue = analogRead(gazSensorPin);
  delay(1000);

  // Gaz sensörü değeri 100'ün üzerinde ise buzzeri çalıştır
  if (sensorValue >= 100) {
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
  }

  // Bluetooth modülünden gelen veriyi Serial Monitor'e yazdır
  if (BTSerial.available()) {
    Serial.write(char(BTSerial.read()));
    
  }

  // Serial Monitor üzerinden gelen veriyi Bluetooth modülüne gönder
  if (Serial.available()) {
    BTSerial.write(Serial.read()); // Sensör değerini Bluetooth'a gönder
  }
}
