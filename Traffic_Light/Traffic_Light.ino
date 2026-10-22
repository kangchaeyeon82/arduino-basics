// 아두이노 우노 신호등 (7번: 파랑, 8번: 노랑, 9번: 빨강)
// 처음에는 모든 불이 꺼져 있고, 2번 핀 버튼을 한 번 누르면 인터럽트가 발생해서 신호등이 시작됨

const int GREEN_PIN = 7;                    // 파란불 핀
const int YELLOW_PIN = 8;                   // 노란불 핀
const int RED_PIN = 9;                      // 빨간불 핀
const int BUTTON_PIN = 2;                   // 버튼 핀 (인터럽트 0번)

const unsigned long GREEN_TIME = 3000;      // 파란불 켜져 있는 시간, 3000ms
const unsigned long YELLOW_TIME = 1000;     // 노란불 켜져 있는 시간, 1000ms
const unsigned long RED_TIME = 3000;        // 빨간불 켜져 있는 시간, 3000ms

// 인터럽트 함수 안에서 바꾸는 변수는 volatile을 붙여야 loop()에서 바뀐 값을 제대로 읽음
volatile bool started = false;              // 버튼을 눌러서 신호등이 시작됐는지

void buttonISR()    // 버튼을 누르는 순간 자동으로 실행되는 인터럽트 함수
{
  started = true;                           // 신호등 시작
}

void setLights(int green, int yellow, int red)  // 세 불을 한 번에 켜고 끄는 함수
{
  digitalWrite(GREEN_PIN, green);           // 파란불
  digitalWrite(YELLOW_PIN, yellow);         // 노란불
  digitalWrite(RED_PIN, red);               // 빨간불
}

void setup()    // 한 번만 실행
{
  pinMode(GREEN_PIN, OUTPUT);               // 파란불 핀 모드를 출력모드로
  pinMode(YELLOW_PIN, OUTPUT);              // 노란불 핀 모드를 출력모드로
  pinMode(RED_PIN, OUTPUT);                 // 빨간불 핀 모드를 출력모드로
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀 모드를 입력모드로, 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  setLights(LOW, LOW, LOW);                 // 처음에는 모든 불 끄기

  // 버튼을 누르는 순간(FALLING = HIGH → LOW) buttonISR 함수 실행
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop()     //무한히 반복
{
  if (!started)                             // 아직 버튼을 안 눌렀으면
  {
    return;                                 // 아무것도 안 하고 기다림
  }

  setLights(HIGH, LOW, LOW);                // 파란불만 켜기
  delay(GREEN_TIME);                        // 3초 대기, 3000ms 기다림

  setLights(LOW, HIGH, LOW);                // 노란불만 켜기
  delay(YELLOW_TIME);                       // 1초 대기, 1000ms 기다림

  setLights(LOW, LOW, HIGH);                // 빨간불만 켜기
  delay(RED_TIME);                          // 3초 대기, 3000ms 기다림
}
