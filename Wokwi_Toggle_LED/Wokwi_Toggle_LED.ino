// Wokwi 시뮬레이터용: 2번 핀 버튼을 누를 때마다 13번 핀 LED 토글하기
// 버튼은 내부 풀업 사용 (안 누르면 HIGH, 누르면 LOW)
// 누르는 순간(HIGH → LOW)만 잡고, 손 뗄 때까지 기다려서 버튼 떨림(바운스) 무시
// Wokwi 버튼은 실제 버튼처럼 떨림까지 흉내 내서, 떨림 처리가 없으면 한 번 눌러도 여러 번 토글됨

const int BUTTON_PIN = 2;                   // 버튼 핀
const int LED_PIN = 13;                     // LED 핀

int lastButton = HIGH;                      // 과거값: 지난번 loop에서 읽은 버튼 값
int ledState = LOW;                         // LED 상태 (LOW=꺼짐, HIGH=켜짐)

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // 버튼핀을 입력모드로, 내부 풀업 저항 사용
  pinMode(LED_PIN, OUTPUT);                 // LED핀을 출력모드로
  digitalWrite(LED_PIN, ledState);          // 처음에는 LED 끄기
}

void loop()     // 무한히 반복
{
  int button = digitalRead(BUTTON_PIN);     // 현재값: 지금 버튼 값 읽기

  if (lastButton == HIGH && button == LOW)  // 안 눌림 → 눌림으로 바뀐 순간
  {
    ledState = !ledState;                   // LED 상태 뒤집기 (토글)
    digitalWrite(LED_PIN, ledState);        // LED에 반영
    Serial.println(ledState ? "LED ON" : "LED OFF");
    delay(50);                              // 누를 때 버튼 떨림 무시
    while (digitalRead(BUTTON_PIN) == LOW); // 손 뗄 때까지 기다리기
    delay(50);                              // 뗄 때 버튼 떨림 무시
    button = HIGH;                          // 이제 버튼은 떼진 상태
  }

  lastButton = button;                      // 현재값을 과거값으로 저장
}
