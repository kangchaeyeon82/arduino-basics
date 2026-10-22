// 아두이노 우노 11번 핀에 연결한 LED가 점점 밝아지다가 점점 어두워지기
// 11번 핀은 PWM 핀(~)이라서 analogWrite()로 밝기를 0~255 단계로 조절할 수 있음

const int LED_PIN = 11;                     // LED 핀 (PWM)

void setup()    // 한 번만 실행
{
  pinMode(LED_PIN, OUTPUT);                 // LED핀 모드를 출력모드로
}

void loop()     //무한히 반복
{
  for (int brightness = 0; brightness <= 255; brightness++)   // 밝기를 0부터 255까지 1씩 올리기
  {
    analogWrite(LED_PIN, brightness);       // LED 밝기 설정 (0=꺼짐, 255=가장 밝음)
    delay(5);                               // 5ms 대기, 한 바퀴에 약 1.3초
  }

  for (int brightness = 255; brightness >= 0; brightness--)   // 밝기를 255부터 0까지 1씩 내리기
  {
    analogWrite(LED_PIN, brightness);       // LED 밝기 설정
    delay(5);                               // 5ms 대기
  }
}
