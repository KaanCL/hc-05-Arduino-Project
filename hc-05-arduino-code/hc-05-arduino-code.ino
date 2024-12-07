#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX || TX

int gazSensorPin = A0;
int sensorValue = 0;
int buzzerPin = 8;
int redLedPin = 12; 
int greenLedPin= 13;

boolean alarm = false;
boolean stop = false;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  Serial.begin(9600); // Serial Monitor iletişimi için
  BTSerial.begin(9600); // Bluetooth modülünün baud hızını ayarlıyoruz
  Serial.println("Bluetooth ile iletişim başlatıldı.");
}

void loop() {
  // Gaz sensöründen veri oku
  sensorValue = analogRead(gazSensorPin);

  delay(1000);

  Serial.println(alarm);
  Serial.println(sensorValue);

  // Gaz sensörü değeri 100'ün üzerinde ise buzzeri çalıştır
  alarm = sensorValue >= 100 ? true : false;

  if (alarm && !stop) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLedPin, HIGH);
  } else {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLedPin, LOW); 
  }

  // Bluetooth modülünden gelen veriyi Serial Monitor'e yazdır
  if (BTSerial.available()) {
    char gelenVeri = BTSerial.read();   
    if(alarm){
     if (gelenVeri == 's') {
      stop = true; // Alarmı kapat
      BTSerial.print("Alarm kapatıldı\n");
    }
    }else{stop = false;}
   
    Serial.write(gelenVeri);
  }

  // Serial Monitor üzerinden gelen veriyi Bluetooth modülüne gönder
  if (Serial.available()) {
    char gidenVeri = Serial.read();   
    BTSerial.write(gidenVeri);
  }

}
