// === 腳位設定 ===
const int buttonPin = 2;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

// === 心情參數 ===
int mood = 10;                 // 初始心情值
const int MOOD_MIN = 0;
const int MOOD_MAX = 50;       // 可自行調整上限
unsigned long lastPressTime = 0;  // 上次按下的時間
unsigned long lastDecreaseTime = 0;

bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 按鈕接 GND
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  updateLED(); // 初始顯示
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // ===== 按鈕短按偵測 =====
  if (lastButtonState == HIGH && buttonState == LOW) {
    mood++;
    if (mood > MOOD_MAX) mood = MOOD_MAX;
    lastPressTime = millis();  // 更新最後互動時間
    updateLED();
  }

  // ===== 若超過5秒沒按按鈕，開始變難過 =====
  if (millis() - lastPressTime > 3000) {
    if (millis() - lastDecreaseTime >= 500) { // 每1秒減一次
      if (mood > MOOD_MIN) {
        mood--;
        updateLED();
      }
      lastDecreaseTime = millis();
    }
  }

  lastButtonState = buttonState;
}

// === 根據 mood 更新 LED 顏色 ===
void updateLED() {
  // 心情越高 → 藍越強，綠越弱，紅維持 0
  int greenVal = map(mood, MOOD_MIN, MOOD_MAX, 255, 0);  // 開心時綠少
  int blueVal  = map(mood, MOOD_MIN, MOOD_MAX, 0, 255);  // 開心時藍多

  // 共陽極版本 → 要反轉顏色值
  analogWrite(redPin, 255 - 0);
  analogWrite(greenPin, 255 - greenVal);
  analogWrite(bluePin, 255 - blueVal);
}
