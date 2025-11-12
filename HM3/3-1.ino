// === 腳位設定 ===
const int buttonPin = 2;  // 按鈕接腳（另一端接 GND）
const int redPin = 3;     // RGB LED 的紅腳
const int greenPin = 5;   // RGB LED 的綠腳
const int bluePin = 6;    // RGB LED 的藍腳

// === 狀態變數 ===
int mode = 0;                    // 0=恆亮, 1=慢閃, 2=中閃, 3=快閃
bool lastButtonState = HIGH;
unsigned long lastBlinkTime = 0;
bool ledState = true;            // true=亮, false=滅

// === 閃爍間隔（毫秒）===
const unsigned long intervals[] = {0, 1000, 500, 200};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 一端接 GND
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  turnOnWhite(); // 初始為恆亮白光
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // ===== 偵測短按（放開瞬間） =====
  if (lastButtonState == LOW && buttonState == HIGH) {
    mode = (mode + 1) % 4;   // 循環 0~3
    ledState = true;
    lastBlinkTime = millis();
  }

  // ===== 模式控制 =====
  switch (mode) {
    case 0: // 恆亮
      turnOnWhite();
      break;

    case 1: // 慢閃爍
    case 2: // 中閃爍
    case 3: // 快閃爍
      handleBlink(intervals[mode]);
      break;
  }

  lastButtonState = buttonState;
}

// === 閃爍處理 ===
void handleBlink(unsigned long interval) {
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime >= interval) {
    ledState = !ledState;
    if (ledState) turnOnWhite();
    else turnOffLED();
    lastBlinkTime = currentTime;
  }
}

// === 白光（共陽極版本：LOW=亮）===
void turnOnWhite() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

// === 熄燈 ===
void turnOffLED() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}
