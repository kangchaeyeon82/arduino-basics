// 아두이노 우노 A0, A1 핀에 연결한 가변저항 2개의 값과 전압을 읽어서 시리얼 모니터에 출력하기
void setup()    // 한 번만 실행
{
  Serial.begin(9600);      // 시리얼 통신 시작, 통신 속도 9600bps
}

void loop()     //무한히 반복
{
  int value0 = analogRead(A0);             // A0핀의 전압을 읽어서 0~1023 값으로 저장 (0V=0, 5V=1023)
  int value1 = analogRead(A1);             // A1핀의 전압을 읽어서 0~1023 값으로 저장 (0V=0, 5V=1023)
  float voltage0 = value0 * 5.0 / 1023.0;  // A0에서 읽은 값을 전압(0~5V)으로 바꾸기
  float voltage1 = value1 * 5.0 / 1023.0;  // A1에서 읽은 값을 전압(0~5V)으로 바꾸기

  Serial.print("A0 value: ");   // 시리얼 모니터에 글자 출력
  Serial.print(value0);         // A0에서 읽은 값 출력
  Serial.print("  voltage: ");  // 시리얼 모니터에 글자 출력
  Serial.print(voltage0, 2);    // A0 전압을 소수점 둘째 자리까지 출력
  Serial.print(" V");           // 단위 출력

  Serial.print("  |  A1 value: ");  // 시리얼 모니터에 글자 출력
  Serial.print(value1);             // A1에서 읽은 값 출력
  Serial.print("  voltage: ");      // 시리얼 모니터에 글자 출력
  Serial.print(voltage1, 2);        // A1 전압을 소수점 둘째 자리까지 출력
  Serial.println(" V");             // 단위 출력하고 줄 바꿈
  delay(100);                       // 0.1초 대기, 100ms 기다림
}
