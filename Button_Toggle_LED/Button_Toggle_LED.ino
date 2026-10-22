// 아두이노 우노 2번 핀 버튼을 누를 때마다 13번 핀 LED 토글하기
// 13번 핀은 보드의 내장 LED(L)와도 연결돼 있어서, 외부 LED가 없어도 보드에서 바로 확인 가능
// millis()로 디바운스(버튼 떨림 무시), 현재값과 과거값을 비교해서 누르는 순간만 토글

const int BUTTON_PIN = 2;                   // 버튼 핀
const int LED_PIN = 13;                     // LED 핀
const unsigned long DEBOUNCE_DELAY = 55;   // 버튼 떨림 무시 시간, 200ms

int lastReading = HIGH;                     // 과거값: 지난번 loop에서 읽은 버튼 값
int buttonState = HIGH;                     // 떨림이 끝나고 확정된 버튼 상태
unsigned long lastDebounceTime = 0;         // 버튼 값이 마지막으로 바뀐 시각 (ms)
int ledState = LOW;                         // LED 상태 (LOW=꺼짐, HIGH=켜짐)
int toggleCount = 0;                        // 토글된 횟수 (버튼 떨림 확인용)

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  pinMode(LED_PIN, OUTPUT);                 // LED핀 모드를 출력모드로
  digitalWrite(LED_PIN, ledState);          // 처음에는 LED 끄기
}

void loop()     //무한히 반복
{
  int reading = digitalRead(BUTTON_PIN);    // 현재값: 지금 버튼 값 읽기

  if (reading != lastReading)               // 현재값과 과거값이 다르면 (버튼이 움직였거나 떨리는 중)
  {
    lastDebounceTime = millis();            // 바뀐 시각을 기록
  }

  if (millis() - lastDebounceTime > DEBOUNCE_DELAY)  // 값이 200ms 넘게 그대로면 떨림이 끝난 진짜 상태
  {
    if (reading != buttonState)             // 확정된 상태가 바뀌었으면
    {
      buttonState = reading;                // 새 상태로 저장

      if (buttonState == LOW)               // HIGH → LOW로 바뀐 순간 = 버튼을 누른 순간
      {
        ledState = !ledState;               // LED 상태 뒤집기 (토글)
        digitalWrite(LED_PIN, ledState);    // LED에 반영
        toggleCount++;                      // 토글 횟수 1 증가
        Serial.print("Toggle #");           // 시리얼 모니터에 글자 출력
        Serial.print(toggleCount);          // 토글 횟수 출력
        Serial.print("  LED: ");            // 시리얼 모니터에 글자 출력
        Serial.println(ledState ? "ON" : "OFF");  // LED 상태 출력하고 줄 바꿈
      }
    }
  }

  lastReading = reading;                    // 현재값을 과거값으로 저장 (다음 loop에서 비교용)
}
