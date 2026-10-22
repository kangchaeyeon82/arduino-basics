// 아두이노 우노 인터럽트 핀(2번)에 연결한 버튼을 누를 때와 뗄 때마다 A5 LED 토글하기
// 우노에서 attachInterrupt()를 쓸 수 있는 핀은 2번, 3번뿐이라서 버튼은 2번 핀에 연결

const int BUTTON_PIN = 2;                   // 버튼 핀 (인터럽트 0번)
const int LED_PIN = A5;                     // LED 핀
const unsigned long DEBOUNCE_DELAY = 50;    // 버튼 떨림 무시 시간, 50ms

// 인터럽트 함수 안에서 바꾸는 변수는 volatile을 붙여야 loop()에서 바뀐 값을 제대로 읽음
volatile int lastButtonState = HIGH;        // 과거값: 마지막으로 인정한 버튼 상태
volatile unsigned long lastInterruptTime = 0; // 마지막으로 인정한 인터럽트 시각 (ms)
volatile int ledState = LOW;                // LED 상태 (LOW=꺼짐, HIGH=켜짐)
volatile bool changed = false;              // 인터럽트에서 LED를 바꿨는지 (시리얼 출력용)

void buttonISR()    // 버튼 핀 값이 바뀔 때마다 자동으로 실행되는 인터럽트 함수
{
  unsigned long now = millis();             // 지금 시각 (ms)
  if (now - lastInterruptTime < DEBOUNCE_DELAY)  // 50ms 안에 또 들어온 건 버튼 떨림이라 무시
  {
    return;
  }

  int state = digitalRead(BUTTON_PIN);      // 현재값: 지금 버튼 값 읽기
  if (state == lastButtonState)             // 현재값과 과거값이 같으면 실제로 바뀐 게 아니라 무시
  {
    return;
  }

  lastButtonState = state;                  // 현재값을 과거값으로 저장
  lastInterruptTime = now;                  // 인정한 시각 기록
  ledState = !ledState;                     // LED 상태 뒤집기 (토글)
  digitalWrite(LED_PIN, ledState);          // LED에 반영
  changed = true;                           // loop()에서 시리얼 출력하도록 표시
}

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작, 통신 속도 9600bps
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  pinMode(LED_PIN, OUTPUT);                 // LED핀 모드를 출력모드로
  digitalWrite(LED_PIN, ledState);          // 처음에는 LED 끄기

  // 버튼 핀 값이 바뀔 때(CHANGE = 누를 때, 뗄 때 둘 다) buttonISR 함수 실행
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
}

void loop()     //무한히 반복
{
  if (changed)                              // 인터럽트에서 LED를 바꿨으면
  {
    noInterrupts();                         // 값 복사하는 동안 인터럽트 잠깐 막기
    int button = lastButtonState;           // 버튼 상태 복사
    int led = ledState;                     // LED 상태 복사
    changed = false;                        // 표시 지우기
    interrupts();                           // 인터럽트 다시 허용

    // 인터럽트 함수 안에서는 Serial을 쓰면 안 돼서 loop()에서 출력
    Serial.print(button == LOW ? "Button PRESSED" : "Button RELEASED");  // 버튼 상태 출력
    Serial.print(" -> LED ");                // 시리얼 모니터에 글자 출력
    Serial.println(led ? "ON" : "OFF");      // LED 상태 출력하고 줄 바꿈
  }
}
