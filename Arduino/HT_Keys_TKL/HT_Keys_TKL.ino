/* NOTE
 * If a compile error occurs,
 * Use "Raspberry Pi Pico/RP2040" by Earle F.Philhower
 * instead of "Arduino Mbed OS RP2040 Boards" by Arduino
 */


#include <Keyboard.h>
#define US_KEYBOARD

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

/* キー出力モードの指定用 */
#define MODE_Press true
#define MODE_Release false

/* 使用するGPIOを定義 */
#define Scan0 25
#define Scan1 20
#define Scan2 19
#define Scan3 18
#define Scan4 17
#define Scan5 16

#define Read0   0
#define Read1   1
#define Read2   2
#define Read3   3
#define Read4   4
#define Read5   5
#define Read6   6
#define Read7   7
#define Read8   8
#define Read9   9
#define Read10 10
#define Read11 11
#define Read12 12
#define Read13 13
#define Read14 21
#define Read15 23
#define Read16 24

/* 各キースイッチとそれに割り当てるキーの対応を定義 */
#define SW1  Key_ESC
#define SW2  Key_F1
#define SW3  Key_F2
#define SW4  Key_F3
#define SW5  Key_F4
#define SW6  Key_F5
#define SW7  Key_F6
#define SW8  Key_F7
#define SW9  Key_F8
#define SW10 Key_F9
#define SW11 Key_F10
#define SW12 Key_F11
#define SW13 Key_F12
#define SW14 Key_PrintScrn
#define SW15 Key_ScrollLock
#define SW16 Key_Pause
#define SW17 Key_Tilde
#define SW18 Key_1
#define SW19 Key_2
#define SW20 Key_3
#define SW21 Key_4
#define SW22 Key_5
#define SW23 Key_6
#define SW24 Key_7
#define SW25 Key_8
#define SW26 Key_9
#define SW27 Key_0
#define SW28 Key_Hyphen
#define SW29 Key_Equal
#define SW30 Key_Backspace
#define SW31 Key_Insert
#define SW32 Key_Home
#define SW33 Key_PageUp
#define SW34 Key_Tab
#define SW35 Key_Q
#define SW36 Key_W
#define SW37 Key_E
#define SW38 Key_R
#define SW39 Key_T
#define SW40 Key_Y
#define SW41 Key_U
#define SW42 Key_I
#define SW43 Key_O
#define SW44 Key_P
#define SW45 Key_L_Bracket
#define SW46 Key_R_Bracket
#define SW47 Key_BackSlash
#define SW48 Key_Delete
#define SW49 Key_End
#define SW50 Key_PageDown
#define SW51 Key_CapsLock
#define SW52 Key_A
#define SW53 Key_S
#define SW54 Key_D
#define SW55 Key_F
#define SW56 Key_G
#define SW57 Key_H
#define SW58 Key_J
#define SW59 Key_K
#define SW60 Key_L
#define SW61 Key_SemiColon
#define SW62 Key_Quote
#define SW63 Key_Enter
#define SW64 Key_L_Shift
#define SW65 Key_Z
#define SW66 Key_X
#define SW67 Key_C
#define SW68 Key_V
#define SW69 Key_B
#define SW70 Key_N
#define SW71 Key_M
#define SW72 Key_camma
#define SW73 Key_period
#define SW74 Key_slash
#define SW75 Key_R_Shift
#define SW76 Key_UP
#define SW77 Key_L_Ctrl
#define SW78 Key_L_Win
#define SW79 Key_L_Alt
#define SW80 Key_Space
#define SW81 Key_R_Alt
#define SW82 Key_R_Win
#define SW83 Key_App
#define SW84 Key_R_Ctrl
#define SW85 Key_LT
#define SW86 Key_DN
#define SW87 Key_RT


/* キー名称とキーコードの対応を定義 */
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
#define Key_Tilde       0x60
#define Key_1           0x31
#define Key_2           0x32
#define Key_3           0x33
#define Key_4           0x34
#define Key_5           0x35
#define Key_6           0x36
#define Key_7           0x37
#define Key_8           0x38
#define Key_9           0x39
#define Key_0           0x30
#define Key_Hyphen      0x2D
#define Key_Equal       0x3D
#define Key_Backspace   0xB2
#define Key_Insert      0xD1
#define Key_Home        0xD2
#define Key_PageUp      0xD3
#define Key_Tab         0xB3
#define Key_Q           0x71
#define Key_W           0x77
#define Key_E           0x65
#define Key_R           0x72
#define Key_T           0x74
#define Key_Y           0x79
#define Key_U           0x75
#define Key_I           0x69
#define Key_O           0x6F
#define Key_P           0x70
#define Key_L_Bracket   0x5B
#define Key_R_Bracket   0x5D
#define Key_BackSlash   0x5C
#define Key_Delete      0xD4
#define Key_End         0xD5
#define Key_PageDown    0xD6
#define Key_CapsLock    0xC1
#define Key_A           0x61
#define Key_S           0x73
#define Key_D           0x64
#define Key_F           0x66
#define Key_G           0x67
#define Key_H           0x68
#define Key_J           0x6A
#define Key_K           0x6B
#define Key_L           0x6C
#define Key_SemiColon   0x3B
#define Key_Quote       0x27
#define Key_Enter       0xB0
#define Key_L_Shift     0x81
#define Key_Z           0x7A
#define Key_X           0x78
#define Key_C           0x63
#define Key_V           0x76
#define Key_B           0x62
#define Key_N           0x6E
#define Key_M           0x6D
#define Key_camma       0x2C
#define Key_period      0x2E
#define Key_slash       0x2F
#define Key_R_Shift     0x85
#define Key_UP          0xDA
#define Key_L_Ctrl      0x80
#define Key_L_Win       0x83
#define Key_L_Alt       0x82
#define Key_Space       0x20
#define Key_R_Alt       0x86
#define Key_R_Win       0x87
#define Key_App         0xED
#define Key_R_Ctrl      0x84
#define Key_LT          0xD8
#define Key_DN          0xD9
#define Key_RT          0xD7

/* GPIO初期化用配列 */
const uint8_t Scan[] = {Scan0, Scan1, Scan2, Scan3, Scan4, Scan5 };
const uint8_t Read[] = {Read0, Read1, Read2, Read3, Read4, Read5, Read6, Read7, Read8, Read9, Read10, Read11, Read12, Read13, Read14, Read15, Read16};

/* キーマトリクス操作用配列 */
const uint8_t keyMap[sizeof(Scan)][sizeof(Read)] = {
  {SW1 , Null, SW2 , SW3 , SW4 , SW5 , SW6 , SW7 , SW8 , SW9 , SW10, SW11, SW12, SW13, SW14, SW15, SW16},
  {SW17, SW18, SW19, SW20, SW21, SW22, SW23, SW24, SW25, SW26, SW27, SW28, SW29, SW30, SW31, SW32, SW33},
  {SW34, SW35, SW36, SW37, SW38, SW39, SW40, SW41, SW42, SW43, SW44, SW45, SW46, SW47, SW48, SW49, SW50},
  {SW51, SW52, SW53, SW54, SW55, SW56, SW57, SW58, SW59, SW60, SW61, SW62, Null, SW63, Null, Null, Null},
  {SW64, SW65, SW66, SW67, SW68, SW69, SW70, SW71, SW72, SW73, SW74, Null, Null, SW75, Null, SW76, Null},
  {SW77, SW78, SW79, Null, Null, SW80, Null, Null, Null, SW81, SW82, SW83, Null, SW84, SW85, SW86, SW87}};

/* キーマトリクスの状態保存用配列 */
volatile uint8_t Matrix[sizeof(Scan)][sizeof(Read)];

/* マルチコアの動作制御用変数 */
volatile bool isOK_readKey =  true;
volatile bool isOK_keyOut  = false;

void setup() {
#ifdef DEBUG
  /* デバッグ用シリアル通信を115200bpsで開始 */
  Serial.begin(115200);
#endif

  /* 読み取り線を入力にしてプルアップ */
  for(uint8_t i = 0; i < sizeof(Read); i++) {
    pinMode(Read[i], INPUT_PULLUP);
  }

  /* スキャン線を出力にしてすべてHIGH */
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    pinMode(Scan[i], OUTPUT);
    digitalWrite(Scan[i], HIGH);
  }
}

void setup1() {
#ifndef DISABLE_KEYOUT
  /* キーボードエミュレート開始 */
  Keyboard.begin();
#endif
}

void loop() {
  if(isOK_readKey) {
    isOK_readKey = false;
    readKeyPad();  // キーボードの状態を読み取り、配列を更新する:
    isOK_keyOut = true;
  }

  delayMicroseconds(4000);
}

void loop1() {
  if(isOK_keyOut) {
    isOK_keyOut = false;
    checkMatrix();  // 配列を参照し押されたかどうかを判断:
    isOK_readKey = true;
  }
}

void readKeyPad(void) {
  for(uint8_t i = 0; i < sizeof(Scan); i++) {     // スキャン線を順に切り替え:
    digitalWrite(Scan[i], LOW);                   // 読み取るところだけ落とす:
    delayMicroseconds(8);                         // ゴースト発生防止:
    for(uint8_t o = 0; o < sizeof(Read); o++) {   // 読み取って配列を更新:
      Matrix[i][o] = (Matrix[i][o] << 1) + (digitalRead(Read[o]) ? 0 : 1);
      delayMicroseconds(8);                       // ゴースト発生防止:
    }
    digitalWrite(Scan[i], HIGH);                  // 定常状態に戻す:
  }

#ifdef DEBUG_Matrix
  /* デバッグ表示 */
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    Serial.print(" | ");
    for(uint8_t o = 0; o < sizeof(Read); o++) {
      for(uint8_t b = 7; b > 0; b--) {            // 配列のデータを MSB から選択:
        if((Matrix[i][o] & 1 << b) == 0) {        // 配列のデータの対応するビットが 0 かどうかを判定:
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
  /* キーボード出力 */
  for(uint8_t i = 0; i < sizeof(Scan); i++) {
    for(uint8_t o = 0; o < sizeof(Read); o++) {
      if((Matrix[i][o] & 0b00001111) == 0b00000011) {
        keyOut(keyMap[i][o], MODE_Press);
      }else if((Matrix[i][o] & 0b00000111) == 0b00000100) {
        keyOut(keyMap[i][o], MODE_Release);
      }
    }
  }
}

void keyOut(const uint8_t key, const bool mode) {
#ifndef DISABLE_KEYOUT
  if(key == 0) {
  }else {
    if(mode) {
      Keyboard.press(key);
    }else {
      Keyboard.release(key);
    }
  }
#endif
}
