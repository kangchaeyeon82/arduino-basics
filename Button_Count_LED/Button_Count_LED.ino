// 아두이노 우노 A0 버튼 누른 횟수 세기 + 5번 누를 때마다 A5 LED 토글하기
// millis()로 디바운스(버튼 떨림 무시), 현재값과 과거값을 비교해서 누르는 순간만 셈

const int BUTTON_PIN = A0;               // 버튼 핀
const int LED_PIN = A5;                  // LED 핀
const unsigned long DEBOUNCE_DELAY = 50; // 버튼 떨림 무시 시간, 50ms

int lastReading = HIGH;                  // 과거값: 지난번 loop에서 읽은 버튼 값
int buttonState = HIGH;                  // 떨림이 끝나고 확정된 버튼 상태
unsigned long lastDebounceTime = 0;      // 버튼 값이 마지막으로 바뀐 시각 (ms)
int pressCount = 0;                      // 버튼 누른 횟수
int ledState = LOW;                      // LED 상태 (LOW=꺼짐, HIGH=켜짐)

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                    // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(BUTTON_PIN, INPUT_PULLUP);     // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  pinMode(LED_PIN, OUTPUT);              // LED핀 모드를 출력모드로
  digitalWrite(LED_PIN, ledState);       // 처음에는 LED 끄기
}

void loop()     //무한히 반복
{
  int reading = digitalRead(BUTTON_PIN); // 현재값: 지금 버튼 값 읽기

  if (reading != lastReading)            // 현재값과 과거값이 다르면 (버튼이 움직였거나 떨리는 중)
  {
    lastDebounceTime = millis();         // 바뀐 시각을 기록
  }

  if (millis() - lastDebounceTime > DEBOUNCE_DELAY)  // 값이 50ms 넘게 그대로면 떨림이 끝난 진짜 상태
  {
    if (reading != buttonState)          // 확정된 상태가 바뀌었으면
    {
      buttonState = reading;             // 새 상태로 저장

      if (buttonState == LOW)            // HIGH → LOW로 바뀐 순간 = 버튼을 누른 순간
      {
        pressCount++;                    // 누른 횟수 1 증가
        Serial.print("Press count: ");   // 시리얼 모니터에 글자 출력
        Serial.println(pressCount);      // 누른 횟수 출력하고 줄 바꿈

        if (pressCount % 5 == 0)         // 5번, 10번, 15번... 누를 때마다
        {
          ledState = !ledState;          // LED 상태 뒤집기 (토글)
          digitalWrite(LED_PIN, ledState);         // LED에 반영
          Serial.print("LED: ");                   // 시리얼 모니터에 글자 출력
          Serial.println(ledState ? "ON" : "OFF"); // LED 상태 출력하고 줄 바꿈
        }
      }
    }
  }

  lastReading = reading;                 // 현재값을 과거값으로 저장 (다음 loop에서 비교용)
}
