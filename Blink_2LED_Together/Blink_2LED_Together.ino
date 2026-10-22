// 아두이노 우노 LED 2개 동시에 깜빡이기 (1번 LED: 3번 핀, 2번 LED: 8번 핀)
void setup()    // 한 번만 실행
{
  pinMode(3, OUTPUT);      // 1번 LED핀(3번) 모드를 출력모드로
  pinMode(8, OUTPUT);      // 2번 LED핀(8번) 모드를 출력모드로
}

void loop()     //무한히 반복
{
  digitalWrite(3, HIGH);   // 1번 LED 켜기, 3번 핀을 5V로
  digitalWrite(8, HIGH);   // 2번 LED 켜기, 8번 핀을 5V로
  delay(1000);             // 1초 대기, 1000ms 기다림
  digitalWrite(3, LOW);    // 1번 LED 끄기, 3번 핀을 0V로
  digitalWrite(8, LOW);    // 2번 LED 끄기, 8번 핀을 0V로
  delay(1000);             // 1초 대기, 1000ms 기다림
}
