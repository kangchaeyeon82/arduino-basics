// 아두이노 우노 A0 가변저항으로 네오픽셀 8구(10번 핀) 게이지 채우기
// 가변저항을 돌린 만큼 네오픽셀이 0개 ~ 8개까지 차오름 (초록 → 노랑 → 빨강)
// Adafruit NeoPixel 라이브러리 필요 (라이브러리 매니저에서 "Adafruit NeoPixel" 설치)

#include <Adafruit_NeoPixel.h>              // 네오픽셀 라이브러리

const int POT_PIN = A0;                     // 가변저항 핀
const int PIXEL_PIN = 10;                   // 네오픽셀 신호선 핀
const int PIXEL_COUNT = 8;                  // 네오픽셀 개수
const int BRIGHTNESS = 50;                  // 전체 밝기 (0~255), 너무 밝으면 눈부시고 전류를 많이 먹음

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);  // 네오픽셀 객체 만들기

void setup()    // 한 번만 실행
{
  Serial.begin(9600);                       // 시리얼 통신 시작, 통신 속도 9600bps
  strip.begin();                            // 네오픽셀 시작
  strip.setBrightness(BRIGHTNESS);          // 전체 밝기 설정
  strip.show();                             // 처음에는 모두 끄기
}

void loop()     //무한히 반복
{
  int value = analogRead(POT_PIN);                  // 가변저항 값 읽기 (0~1023)
  int level = (long)value * (PIXEL_COUNT + 1) / 1024;  // 0~1023 값을 켤 개수 0~8로 바꾸기 (9단계로 고르게 나눔)

  for (int i = 0; i < PIXEL_COUNT; i++)     // 0번부터 7번 네오픽셀까지
  {
    if (i < level)                          // 게이지 안에 들어가는 칸이면 켜기
    {
      if (i < 4)      strip.setPixelColor(i, strip.Color(0, 255, 0));    // 1~4번째 칸: 초록
      else if (i < 6) strip.setPixelColor(i, strip.Color(255, 150, 0));  // 5~6번째 칸: 노랑
      else            strip.setPixelColor(i, strip.Color(255, 0, 0));    // 7~8번째 칸: 빨강
    }
    else                                    // 게이지 밖의 칸이면
    {
      strip.setPixelColor(i, 0);            // 끄기
    }
  }
  strip.show();                             // 설정한 색을 네오픽셀에 반영

  Serial.print("value: ");          // 시리얼 모니터에 글자 출력
  Serial.print(value);              // 가변저항 값 출력
  Serial.print("  level: ");        // 시리얼 모니터에 글자 출력
  Serial.println(level);            // 켜진 개수 출력하고 줄 바꿈
  delay(50);                        // 0.05초 대기, 50ms 기다림
}
