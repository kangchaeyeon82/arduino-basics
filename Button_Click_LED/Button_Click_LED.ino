// 아두이노 우노 A0 버튼으로 A5 LED 제어하기
// 빠르게 두 번 누르기(더블 클릭) = LED 켜기, 길게 누르기 = LED 끄기, 한 번 짧게 누르기 = 아무 일 없음
// millis()로 디바운스(버튼 떨림 무시), 현재값과 과거값을 비교해서 누르는 순간/떼는 순간을 찾음

const int BUTTON_PIN = A0;                  // 버튼 핀
const int LED_PIN = A5;                     // LED 핀
const unsigned long DEBOUNCE_DELAY = 50;    // 버튼 떨림 무시 시간, 50ms
const unsigned long LONG_PRESS_TIME = 1000; // 이 시간 이상 누르고 있으면 길게 누르기, 1000ms
const unsigned long DOUBLE_CLICK_GAP = 400; // 첫 번째 클릭 후 이 시간 안에 또 누르면 더블 클릭, 400ms

int lastReading = HIGH;                     // 과거값: 지난번 loop에서 읽은 버튼 값
int buttonState = HIGH;                     // 떨림이 끝나고 확정된 버튼 상태
unsigned long lastDebounceTime = 0;         // 버튼 값이 마지막으로 바뀐 시각 (ms)
unsigned long pressStartTime = 0;           // 버튼을 누르기 시작한 시각 (ms)
unsigned long releaseTime = 0;              // 버튼을 마지막으로 뗀 시각 (ms)
int clickCount = 0;                         // 짧게 누른 횟수 (더블 클릭 판단용)
bool longPressHandled = false;              // 이번에 누른 게 이미 길게 누르기로 처리됐는지

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  pinMode(LED_PIN, OUTPUT);                 // LED핀 모드를 출력모드로
  digitalWrite(LED_PIN, LOW);               // 처음에는 LED 끄기
}

void loop()     //무한히 반복
{
  unsigned long now = millis();             // 지금 시각 (ms)
  int reading = digitalRead(BUTTON_PIN);    // 현재값: 지금 버튼 값 읽기

  if (reading != lastReading)               // 현재값과 과거값이 다르면 (버튼이 움직였거나 떨리는 중)
  {
    lastDebounceTime = now;                 // 바뀐 시각을 기록
  }

  if (now - lastDebounceTime > DEBOUNCE_DELAY)  // 값이 50ms 넘게 그대로면 떨림이 끝난 진짜 상태
  {
    if (reading != buttonState)             // 확정된 상태가 바뀌었으면
    {
      buttonState = reading;                // 새 상태로 저장

      if (buttonState == LOW)               // HIGH → LOW = 버튼을 누른 순간
      {
        pressStartTime = now;               // 누르기 시작한 시각 기록
        longPressHandled = false;           // 아직 길게 누르기 아님
      }
      else                                  // LOW → HIGH = 버튼을 뗀 순간
      {
        if (!longPressHandled)              // 길게 누르기가 아니었으면 짧은 클릭
        {
          clickCount++;                     // 짧게 누른 횟수 1 증가
          releaseTime = now;                // 뗀 시각 기록

          if (clickCount == 2)              // 시간 안에 두 번 눌렀으면 더블 클릭
          {
            digitalWrite(LED_PIN, HIGH);    // LED 켜기
            Serial.println("Double click -> LED ON");  // 시리얼 모니터에 출력하고 줄 바꿈
            clickCount = 0;                 // 횟수 초기화
          }
        }
      }
    }
  }

  // 길게 누르기: 누르고 있는 동안 1초가 지나면 손을 떼기 전에 바로 처리
  if (buttonState == LOW && !longPressHandled && now - pressStartTime >= LONG_PRESS_TIME)
  {
    digitalWrite(LED_PIN, LOW);             // LED 끄기
    Serial.println("Long press -> LED OFF");   // 시리얼 모니터에 출력하고 줄 바꿈
    longPressHandled = true;                // 이번 누르기는 처리 끝 (뗄 때 클릭으로 안 셈)
    clickCount = 0;                         // 횟수 초기화
  }

  // 한 번만 짧게 누르기: 첫 클릭 후 0.4초 동안 다시 안 누르면 한 번 누른 것으로 확정
  if (clickCount == 1 && buttonState == HIGH && now - releaseTime > DOUBLE_CLICK_GAP)
  {
    Serial.println("Single click -> nothing"); // 시리얼 모니터에 출력하고 줄 바꿈 (LED는 그대로)
    clickCount = 0;                         // 횟수 초기화
  }

  lastReading = reading;                    // 현재값을 과거값으로 저장 (다음 loop에서 비교용)
}
