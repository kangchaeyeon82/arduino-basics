// 아두이노 우노 신호등 (10번: 초록, 7번: 노랑, 5번: 빨강)
// 초록 5초 → 노랑 2초 → 빨강 5초 순서로 계속 반복
// 3번 핀 버튼을 누르면 인터럽트가 발생해서 세 불이 바로 다 켜짐, 한 번 더 누르면 다시 신호등 시작

const int GREEN_PIN = 10;                   // 초록불 핀
const int YELLOW_PIN = 7;                   // 노란불 핀
const int RED_PIN = 5;                      // 빨간불 핀
const int BUTTON_PIN = 3;                   // 버튼 핀 (인터럽트 1번)

const unsigned long GREEN_TIME = 5000;      // 초록불 켜져 있는 시간, 5000ms
const unsigned long YELLOW_TIME = 2000;     // 노란불 켜져 있는 시간, 2000ms (곧 빨간불로 바뀐다는 경고라 짧게)
const unsigned long RED_TIME = 5000;        // 빨간불 켜져 있는 시간, 5000ms
const unsigned long DEBOUNCE_DELAY = 200;   // 버튼 떨림 무시 시간, 200ms

// 인터럽트 함수 안에서 바꾸는 변수는 volatile을 붙여야 loop()에서 바뀐 값을 제대로 읽음
volatile bool allOn = false;                // 세 불 다 켜기 상태인지
volatile unsigned long lastInterruptTime = 0; // 마지막으로 인정한 인터럽트 시각 (ms)

void setLights(int green, int yellow, int red)  // 세 불을 한 번에 켜고 끄는 함수
{
  digitalWrite(GREEN_PIN, green);           // 초록불
  digitalWrite(YELLOW_PIN, yellow);         // 노란불
  digitalWrite(RED_PIN, red);               // 빨간불
}

void buttonISR()    // 버튼을 누르는 순간 자동으로 실행되는 인터럽트 함수
{
  unsigned long now = millis();             // 지금 시각 (ms)
  if (now - lastInterruptTime < DEBOUNCE_DELAY)  // 200ms 안에 또 들어온 건 버튼 떨림이라 무시
  {
    return;
  }
  lastInterruptTime = now;                  // 인정한 시각 기록

  allOn = !allOn;                           // 세 불 다 켜기 상태 켜기/끄기 (토글)
  if (allOn)
  {
    setLights(HIGH, HIGH, HIGH);            // 신호 도중이라도 바로 세 불 다 켜기
  }
}

bool waitMs(unsigned long ms)   // delay() 대신 쓰는 대기 함수, 기다리는 중에 버튼이 눌리면 바로 멈춤
{
  unsigned long start = millis();           // 기다리기 시작한 시각
  while (millis() - start < ms)             // 정해진 시간이 지날 때까지
  {
    if (allOn)                              // 버튼이 눌렸으면
    {
      return false;                         // 기다리기 중단
    }
  }
  return true;                              // 끝까지 기다림
}

void setup()    // 한 번만 실행
{
  pinMode(GREEN_PIN, OUTPUT);               // 초록불 핀 모드를 출력모드로
  pinMode(YELLOW_PIN, OUTPUT);              // 노란불 핀 모드를 출력모드로
  pinMode(RED_PIN, OUTPUT);                 // 빨간불 핀 모드를 출력모드로
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)

  // 버튼을 누르는 순간(FALLING = HIGH → LOW) buttonISR 함수 실행
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop()     //무한히 반복
{
  if (allOn)                                // 세 불 다 켜기 상태면
  {
    setLights(HIGH, HIGH, HIGH);            // 세 불 다 켜고 신호등은 멈춤
    return;
  }

  setLights(HIGH, LOW, LOW);                // 초록불만 켜기
  if (!waitMs(GREEN_TIME)) return;          // 5초 대기, 버튼 눌리면 바로 멈춤

  setLights(LOW, HIGH, LOW);                // 노란불만 켜기
  if (!waitMs(YELLOW_TIME)) return;         // 2초 대기, 버튼 눌리면 바로 멈춤

  setLights(LOW, LOW, HIGH);                // 빨간불만 켜기
  if (!waitMs(RED_TIME)) return;            // 5초 대기, 버튼 눌리면 바로 멈춤
}
