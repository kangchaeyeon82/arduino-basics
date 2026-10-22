// 아두이노 우노 A0 핀 가변저항으로 11번 핀 LED 밝기 조절하기
// 11번 핀은 PWM 핀(~)이라서 analogWrite()로 밝기를 0~255 단계로 조절할 수 있음

const int POT_PIN = A0;                     // 가변저항 핀
const int LED_PIN = 11;                     // LED 핀 (PWM)

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(LED_PIN, OUTPUT);                 // LED핀 모드를 출력모드로
}

void loop()     //무한히 반복
{
  int value = analogRead(POT_PIN);                  // 가변저항 값 읽기 (0~1023)
  int brightness = map(value, 0, 1023, 0, 255);     // 0~1023 값을 밝기 0~255로 바꾸기
  analogWrite(LED_PIN, brightness);                 // LED 밝기 설정 (0=꺼짐, 255=가장 밝음)

  Serial.print("value: ");          // 시리얼 모니터에 글자 출력
  Serial.print(value);              // 가변저항 값 출력
  Serial.print("  brightness: ");   // 시리얼 모니터에 글자 출력
  Serial.println(brightness);       // 밝기 출력하고 줄 바꿈
  delay(100);                       // 0.1초 대기, 100ms 기다림
}
