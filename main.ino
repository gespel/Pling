
void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT);
  pinMode(14, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(16);
  int b = analogRead(14);
  Serial.println(a);
  Serial.println(b);
}
