/* NOTE
 * If a compile error occurs,
 * Use "Raspberry Pi Pico/RP2040" by Earle F.Philhower
 * instead of "Arduino Mbed OS RP2040 Boards" by Arduino
 */


#include <Keyboard.h>

// キーマトリクスの処理の有効無効を指定:
// #define DEBUG_Matrix

// 実行速度モニタリングの有効無効を指定:
// #define DEBUG_Times

// キー出力を無効にする:
// #define DISABLE_KEYOUT

#ifdef DEBUG_Times
 #ifndef DEBUG
  #define DEBUG
 #endif
#endif

#ifdef DEBUG_Matrix
 #ifndef DEBUG
  #define DEBUG
 #endif
#endif

// 読み取り間隔 (microsec):
#ifdef DEBUG
 #define delayTime 250000
#else
 #define delayTime 5000
#endif

// キー出力モードの指定用:
#define MODE_Press   true
#define MODE_Release false

// 使用するGPIOを定義:
#define Scan0  25
#define Scan1  20
#define Scan2  19
#define Scan3  18
#define Scan4  17
#define Scan5  16

#define Read0  0
#define Read1  1
#define Read2  2
#define Read3  3
#define Read4  4
#define Read5  5
#define Read6  6
#define Read7  7
#define Read8  8
#define Read9  9
#define Read10 10
#define Read11 11
#define Read12 12
#define Read13 13
#define Read14 21
#define Read15 23
#define Read16 24

// キー名称とキーコードの対応を定義:
#define Null            0x00
#define Key_ESC         0xB1
#define Key_F1          0xC2
#define Key_F2          0xC3
#define Key_F3          0xC4
#define Key_F4          0xC5
#define Key_F5          0xC6
#define Key_F6          0xC7
#define Key_F7          0xC8
#define Key_F8          0xC9
#define Key_F9          0xCA
#define Key_F10         0xCB
#define Key_F11         0xCC
#define Key_F12         0xCD
#define Key_PrintScrn   0xCE
#define Key_ScrollLock  0xCF
#define Key_Pause       0xD0
#define Key_Tilde       '~'
#define Key_1           0x31
#define Key_2           0x32
#define Key_3           0x33
#define Key_4           0x34
#define Key_5           0x35
#define Key_6           0x36
#define Key_7           0x37
#define Key_8           0x38
#define Key_9           0x39
#define Key_0           0x3A
#define Key_Hyphen      '&'
#define Key_Equal       '_'
#define Key_Backspace   0xB2
#define Key_Insert      0xD1
#define Key_Home        0xD2
#define Key_PageUp      0xD3
#define Key_Tab         0xB3
#define Key_Q           'q'
#define Key_W           'w'
#define Key_E           'e'
#define Key_R           'r'
#define Key_T           't'
#define Key_Y           'y'
#define Key_U           'u'
#define Key_I           'i'
#define Key_O           'o'
#define Key_P           'p'
#define Key_L_bracket   ']'
#define Key_R_brackets  '\\'
#define Key_BackSlash   0x5C
#define Key_Delete      0xD4
#define Key_End         0xD5
#define Key_PageDown    0xD6
#define Key_CapsLock    0xC1
#define Key_A           'a'
#define Key_S           's'
#define Key_D           'd'
#define Key_F           'f'
#define Key_G           'g'
#define Key_H           'h'
#define Key_J           'j'
#define Key_K           'k'
#define Key_L           'l'
#define Key_SemiColon   ';'
#define Key_Quote       '"'
#define Key_Enter       0xB0
#define Key_L_Shift     0x81
#define Key_Z           'z'
#define Key_X           'x'
#define Key_C           'c'
#define Key_V           'v'
#define Key_B           'b'
#define Key_N           'n'
#define Key_M           'm'
#define Key_camma       ','
#define Key_period      '.'
#define Key_slash       '/'
#define Key_R_Shift     0x85
#define Key_UP          0xDA
#define Key_L_Ctrl      0x80
#define Key_L_Win       0x83
#define Key_L_Alt       0x82
#define Key_Space       0x20
#define Key_R_Alt       0x86
#define Key_R_Win       0x87
#define Key_App         0x5D
#define Key_R_Ctrl      0x84
#define Key_LT          0xD8
#define Key_DN          0xD9
#define Key_RT          0xD7

// GPIO初期化用配列:
const uint8_t Scan[] = {Scan0, Scan1, Scan2, Scan3, Scan4, Scan5};
const uint8_t Read[] = {Read0, Read1, Read2, Read3, Read4, Read5, Read6, Read7, Read8, Read9, Read10, Read11, Read12, Read13, Read14, Read15, Read16};

// キーマトリクス操作用配列:
const uint8_t keyMap[sizeof(Scan)][sizeof(Read)] = {
  {Key_ESC     , Null     , Key_F1   , Key_F2, Key_F3, Key_F4   , Key_F5, Key_F6, Key_F7   , Key_F8    , Key_F9       , Key_F10      , Key_F11       , Key_F12      , Key_PrintScrn, Key_ScrollLock, Key_Pause   },
  {Key_Tilde   , Key_1    , Key_2    , Key_3 , Key_4 , Key_5    , Key_6 , Key_7 , Key_8    , Key_9     , Key_0        , Key_Hyphen   , Key_Equal     , Key_Backspace, Key_Insert   , Key_Home      , Key_PageUp  },
  {Key_Tab     , Key_Q    , Key_W    , Key_E , Key_R , Key_T    , Key_Y , Key_U , Key_I    , Key_O     , Key_P        , Key_L_bracket, Key_R_brackets, Key_BackSlash, Key_Delete   , Key_End       , Key_PageDown},
  {Key_CapsLock, Key_A    , Key_S    , Key_D , Key_F , Key_G    , Key_H , Key_J , Key_K    , Key_L     , Key_SemiColon, Key_Quote    , Null          , Key_Enter    , Null         , Null          , Null        },
  {Key_L_Shift , Key_Z    , Key_X    , Key_C , Key_V , Key_B    , Key_N , Key_M , Key_camma, Key_period, Key_slash    , Null         , Null          , Key_R_Shift  , Null         , Key_UP        , Null        },
  {Key_L_Ctrl  , Key_L_Win, Key_L_Alt, Null  , Null  , Key_Space, Null  , Null  , Null     , Key_R_Alt , Key_R_Win    , Key_App      , Null          , Key_R_Ctrl   , Key_LT       , Key_DN        , Key_RT      }};

// キーマトリクスの状態保存用配列:
volatile uint8_t Matrix[sizeof(Scan)][sizeof(Read)];

void setup() {
#ifdef DEBUG
  // デバッグ用シリアル通信を115200bpsで開始:
  Serial.begin(115200);
#endif

  // 読み取り線を入力にしてプルアップ:
  for(uint8_t i = 0; i < sizeof(Read); i++) {
    pinMode(Read[i],  INPUT_PULLUP);
  }

  // スキャン線を出力にしてすべてHIGH:
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    pinMode(Scan[i], OUTPUT);
    digitalWrite(Scan[i], HIGH);
  }

#ifndef DEBUG
  // キーボードエミュレート開始:
  Keyboard.begin();
#endif
}

void setup1() {
}

void loop() {
#ifdef DEBUG_Times
  uint16_t startTime = micros();
#endif

  readKeyPad();      // キーボードの状態を読み取り、配列を更新する:
  checkMatrix();     // 配列を参照し押されたかどうかを判断:

#ifdef DEBUG_Times
  uint16_t endTime = micros();
  uint8_t diff = endTime - startTime;
  char buf[30];
  sprintf(buf, " - Running Time : %2d micro sec.\n\n", diff);
  Serial.print(buf);
#endif

  delayMicroseconds(delayTime);  // 読み取り間隔を設定:
}

void loop2() {
}

void readKeyPad(void) {
  for(uint8_t i = 0; i < sizeof(Scan); i++) {    // スキャン線を順に切り替え:
    digitalWrite(Scan[i],  LOW);                 // 読み取るところだけ落とす:
    delayMicroseconds(2);
    for(uint8_t o = 0; o < sizeof(Read); o++) {  // 読み取って配列を更新:
      Matrix[i][o] = (Matrix[i][o] << 1) + (digitalRead(Read[o]) ? 0 : 1);
      delayMicroseconds(2);
    }
    delayMicroseconds(2);
    digitalWrite(Scan[i], HIGH);                 // 定常状態に戻す:
  }

#ifdef DEBUG_Matrix
  // デバッグ表示:
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    Serial.print(" | ");
    for(uint8_t o = 0; o < sizeof(Read); o++) {
      for(uint8_t b = 7; b > 0; b--) {
        if((Matrix[i][o] & 1 << b) == 0) {
          Serial.print("0");
        }else {
          Serial.print("1");
        }
      }
      Serial.print(" | ");
    }
    Serial.print("\n");
  }
  Serial.print("\n");
#endif
}

void checkMatrix(void) {
  // キーボード出力:
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    for(uint8_t o = 0; o < sizeof(Read); o++) {
            if((Matrix[i][o] & 0b00000111) == 0b011) {
        keyOut(keyMap[i][o], MODE_Press);
      }else if((Matrix[i][o] & 0b00000111) == 0b100) {
        keyOut(keyMap[i][o], MODE_Release);
      }
    }
  }
}

void keyOut(const uint8_t keys, const bool mode) {
#ifndef DISABLE_KEYOUT
  if(keys == 0) {
 #ifdef DEBUG_Matrix
      Serial.print("xxxxxxxx");
 #endif
  }else {
    if(mode) {
      Keyboard.press(keys);
    }else {
      Keyboard.release(keys);
    }
  }
#endif
}
