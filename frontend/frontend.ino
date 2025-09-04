#include "esp_camera.h"
#include "WiFi.h"
#include "HTTPClient.h"

// Wi-Fi接続情報
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// バックエンドのURL
const char* serverUrl = "http://your_server_address:port/process_image";

// カメラ設定
#define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     21
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y1_GPIO_NUM       35
#define Y2_GPIO_NUM       34
#define Y3_GPIO_NUM       39
#define Y4_GPIO_NUM       36
#define Y5_GPIO_NUM       13
#define Y6_GPIO_NUM       33
#define Y7_GPIO_NUM       18
#define Y8_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define D0_GPIO_NUM       19
#define D1_GPIO_NUM       21
#define D2_GPIO_NUM       15
#define D3_GPIO_NUM       14
#define D4_GPIO_NUM       13
#define D5_GPIO_NUM       12
#define D6_GPIO_NUM       4
#define D7_GPIO_NUM       16
#define LED_GPIO_NUM      -1

camera_config_t config;

void setup() {
    Serial.begin(115200);
    // Wi-Fi接続
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    // カメラ初期化
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = D0_GPIO_NUM;
    config.pin_d1 = D1_GPIO_NUM;
    // ... 他のピン設定 ...
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_QVGA; // 解像度設定
    config.jpeg_quality = 12; // 圧縮品質
    config.fb_count = 1;
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
}

void loop() {
    // 冷蔵庫の開閉を検出するロジック（Leafonyからの信号を待つ）
    // 例えば、シリアル通信やGPIOピンの信号を監視する
    if (fridge_is_open()) {
        capture_and_send_image();
        // 省電力モードに移行
        // 例: ESP32のDeep Sleepモード
        esp_deep_sleep_start();
    }
}

void capture_and_send_image() {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }

    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "image/jpeg");
    int httpResponseCode = http.POST(fb->buf, fb->len);
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Server Response: " + response);
    } else {
        Serial.printf("HTTP POST failed with error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    esp_camera_fb_return(fb);
    http.end();
}