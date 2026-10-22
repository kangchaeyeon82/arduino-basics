// 아두이노 우노 내장 LED(13번 핀) 깜빡이기
void setup()    // 한 번만 실행
{
  pinMode(LED_BUILTIN, OUTPUT);     // 내장 LED핀 모드를 출력모드로
}

void loop()     //무한히 반복
{
  digitalWrite(LED_BUILTIN, HIGH);  // LED 켜기, 내장 LED핀을 5V로
  delay(1000);                      // 1초 대기, 1000ms 기다림
  digitalWrite(LED_BUILTIN, LOW);   // LED 끄기, 내장 LED핀을 0V로
  delay(1000);                      // 1초 대기, 1000ms 기다림
}
