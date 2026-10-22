// 아두이노 우노 A0 핀에 연결한 버튼 상태를 읽어서 시리얼 모니터에 출력하기
void setup()    // 한 번만 실행
{
  Serial.begin(9600);          // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(A0, INPUT_PULLUP);   // A0핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
}

void loop()     //무한히 반복
{
  int state = digitalRead(A0);  // A0핀의 상태를 읽어서 저장 (HIGH=1, LOW=0)

  if (state == LOW)             // 버튼을 눌렀으면 (A0핀이 GND와 연결되어 0V)
  {
    Serial.println("Button: PRESSED");   // 시리얼 모니터에 출력하고 줄 바꿈
  }
  else                          // 버튼을 안 눌렀으면 (내부 풀업 저항 때문에 5V)
  {
    Serial.println("Button: RELEASED");  // 시리얼 모니터에 출력하고 줄 바꿈
  }
  delay(100);                   // 0.1초 대기, 100ms 기다림
}
