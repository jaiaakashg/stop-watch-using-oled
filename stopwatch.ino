#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128   
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define START_BUTTON 2
#define STOP_BUTTON 3
#define RESET_BUTTON 4

bool running = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.clearDisplay();
  display.display();

  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  pinMode(RESET_BUTTON, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(START_BUTTON) == LOW) {
    running = true;
    startTime = millis() - elapsedTime; 
    delay(200); 
  }

  if (digitalRead(STOP_BUTTON) == LOW) {
    running = false;
    elapsedTime = millis() - startTime;  
    delay(200);  
  }

  if (digitalRead(RESET_BUTTON) == LOW) {
    running = false;
    elapsedTime = 0;
    startTime = millis();
    delay(200);  
  }

  if (running) {
    elapsedTime = millis() - startTime;
  }

  displayTime(elapsedTime);
}

void displayTime(unsigned long time) {
  display.clearDisplay();
 
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  unsigned long hours = time / 3600000;
  time %= 3600000;
  unsigned long minutes = time / 60000;
  time %= 60000;
  unsigned long seconds = time / 1000;
  unsigned long milliseconds = time % 1000;
  
  // Format the time as HH:MM:SS:MS
  char timeString[20];
  sprintf(timeString, "%02lu:%02lu:%02lu:%03lu", hours, minutes, seconds, milliseconds);
  
  display.setCursor(0, 20);
  display.print(timeString);
  
  display.display();
}

