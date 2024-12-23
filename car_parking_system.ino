#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
int rs = 12, en = 11, d7 = 4, d6 = 5, d5 = 6, d4 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String wifi_name = "TurkTelekom_TEAB6";
String wifi_password = "Df9Q4Mxu";

String ip = "184.106.153.149";

int trigPin = 9, echoPin = 10;
int red = 2, green = 3;
long duration;
long range;

void setup() {
  Serial.begin(115200);
  Serial.println("AT");
  delay(3000);
  while(!Serial.find("OK")){
    Serial.println("AT+CWMODE=1");
    delay(200);
    Serial.println("AT+CWJAP=\"" + wifi_name + "\",\"" + wifi_password + "\"");
    delay(500);
  }
  Serial.print("AT+CIPMUX=1\r\n");
  delay(200);
  Serial.print("AT+CIPSERVER=1,80\r\n");
  delay(1000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  Serial.println("AT+CIPSTART=\"TCP\",\"" + ip + "\",80");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  range = (duration / 2 ) / 29.154;

  String data = "GET /update?api_key=GYY7UDH1MYBRREET&field1=";

  if(range <= 8){
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Occupied");
    delay(100);
  }
  else{
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Available");
    delay(100);
  }

  data += range;
  Serial.print("AT+CIPSEND=");
  Serial.println(data.length() + 2);
  delay(20);

  Serial.println(data);

  Serial.println("AT+CIPCLOSE");
  delay(15500);
}
