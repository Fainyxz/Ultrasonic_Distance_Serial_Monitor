#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// GANTI alamat jika hasil scan beda (0x27 / 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// PIN ULTRASONIK
#define TRIG_PIN 9
#define ECHO_PIN 10

// PIN LED
#define LED_HIJAU 2
#define LED_KUNING 3
#define LED_MERAH 4

// PIN BUZZER
#define BUZZER 5

void setup() {
  // Inisialisasi pin
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  // Inisialisasi LCD (KHUSUS Frank de Brabander)
  lcd.init();           // WAJIB
  lcd.backlight();      // WAJIB

  lcd.setCursor(0, 0);
  lcd.print("Sensor Parkir");
  lcd.setCursor(0, 1);
  lcd.print("Siap...");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duration;
  int distance;

  // Trigger ultrasonik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Baca echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  distance = duration * 0.034 / 2;

  // Jika tidak terbaca
  if (duration == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Objek tidak   ");
    lcd.setCursor(0, 1);
    lcd.print("terdeteksi    ");
    delay(500);
    return;
  }

  // Tampilkan jarak
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  // Reset output
  digitalWrite(LED_HIJAU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(BUZZER, LOW);

  // Logika jarak
  if (distance > 30) {
    digitalWrite(LED_HIJAU, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("AMAN           ");
  }
  else if (distance > 15) {
    digitalWrite(LED_KUNING, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("HATI-HATI      ");
  }
  else {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("BERHENTI!      ");
  }

  delay(300);
}
