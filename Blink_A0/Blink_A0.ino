// 아두이노 우노 A0 핀에 연결한 LED 깜빡이기
void setup()    // 한 번만 실행
{
  pinMode(A0, OUTPUT);     // LED 핀을 출력모드로
}

void loop()     //무한히 반복
{
  digitalWrite(A0, HIGH);  // LED 켜기, A0핀을 5V로
  delay(1000);             // 1초 대기, 1000ms 기다림
  digitalWrite(A0, LOW);   // LED 끄기, A0핀을 0V로
  delay(1000);             // 1초 대기, 1000ms 기다림
}


