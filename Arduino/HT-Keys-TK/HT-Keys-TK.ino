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
#define MODE_Press    true
#define MODE_Release false

/* 使用するGPIOを定義 */
#define Scan0   5
#define Scan1   6
#define Scan2   7
#define Scan3   8
#define Scan4  13
#define Scan5  14

#define Read0  16
#define Read1  17
#define Read2  21
#define Read3  29

/* 各キースイッチと識別番号の対応を定義 */
#define SW1   1
#define SW2   2
#define SW3   3
#define SW4   4
#define SW5   5
#define SW6   6
#define SW7   7
#define SW8   8
#define SW9   9
#define SW10 10
#define SW11 11
#define SW12 12
#define SW13 13
#define SW14 14
#define SW15 15
#define SW16 16
#define SW17 17
#define SW18 18
#define SW19 19
#define SW20 20
#define SW21 21
#define SW22 22
#define SW23 23


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

#define Key_NumLock     0xDB
#define Key_Num_Slash   0xDC
#define Key_Num_Aster   0xDD
#define Key_Num_Plus    0xDF
#define Key_Num_Minus   0xDE
#define Key_Num_Enter   0xE0
#define Key_Num_1       0xE1
#define Key_Num_2       0xE2
#define Key_Num_3       0xE3
#define Key_Num_4       0xE4
#define Key_Num_5       0xE5
#define Key_Num_6       0xE6
#define Key_Num_7       0xE7
#define Key_Num_8       0xE8
#define Key_Num_9       0xE9
#define Key_Num_0       0xEA
#define Key_Num_Dot     0xEB

/* GPIO初期化用配列 */
const uint8_t Scan[] = {Scan0, Scan1, Scan2, Scan3, Scan4, Scan5};
const uint8_t Read[] = {Read0, Read1, Read2, Read3};

/* キーマトリクス操作用配列 */
const uint8_t keyMap[sizeof(Scan)][sizeof(Read)] = {{SW1 , SW2 , SW3 , SW4 },
                                                    {SW5 , SW6 , SW7 , SW8 },
                                                    {SW9 , SW10, SW11, SW12},
                                                    {SW13, SW14, SW15, SW16},
                                                    {SW17, SW18, SW19, SW20},
                                                    {SW21, SW22, SW23, Null}};

/* キーマトリクスの状態保存用配列 */
volatile uint8_t Matrix[sizeof(Scan)][sizeof(Read)];

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

#ifndef DISABLE_KEYOUT
  /* キーボードエミュレート開始 */
  Keyboard.begin();
#endif
}

void setup1() {
}

void loop() {
  readKeyPad();   // キーボードの状態を読み取り、配列を更新する:
  checkMatrix();  // 配列を参照し押されたかどうかを判断:

  delayMicroseconds(4000);
}

void loop1() {
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
  // キーボード出力:
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
  switch(key) {
    case Null: 
      // なにもしない:
      break;

    case SW1:   // C1:
      break;

    case SW2:   // C2:
      break;

    case SW3:   // C3:
      break;

    case SW4:   // C4:
      break;

    case SW5:   // NumLock:
      if(mode) {
        Keyboard.press(Key_NumLock);
      }else {
        Keyboard.release(Key_NumLock);
      }
      break;

    case SW6:   // Slash:
      if(mode) {
        Keyboard.press(Key_Num_Slash);
      }else {
        Keyboard.release(Key_Num_Slash);
      }
      break;

    case SW7:   // Asterisk:
      if(mode) {
        Keyboard.press(Key_Num_Aster);
      }else {
        Keyboard.release(Key_Num_Aster);
      }
      break;

    case SW8:   // Backspace:
      if(mode) {
        Keyboard.press(Key_Backspace);
      }else {
        Keyboard.release(Key_Backspace);
      }
      break;

    case SW9:   // 7:
      if(mode) {
        Keyboard.press(Key_Num_7);
      }else {
        Keyboard.release(Key_Num_7);
      }
      break;

    case SW10:  // 8:
      if(mode) {
        Keyboard.press(Key_Num_8);
      }else {
        Keyboard.release(Key_Num_8);
      }
      break;

    case SW11:  // 9:
      if(mode) {
        Keyboard.press(Key_Num_9);
      }else {
        Keyboard.release(Key_Num_9);
      }
      break;

    case SW12:  // Plus:
      if(mode) {
        Keyboard.press(Key_Num_Plus);
      }else {
        Keyboard.release(Key_Num_Plus);
      }
      break;

    case SW13:  // 4:
      if(mode) {
        Keyboard.press(Key_Num_4);
      }else {
        Keyboard.release(Key_Num_4);
      }
      break;

    case SW14:  // 5:
      if(mode) {
        Keyboard.press(Key_Num_5);
      }else {
        Keyboard.release(Key_Num_5);
      }
      break;

    case SW15:  // 6:
      if(mode) {
        Keyboard.press(Key_Num_6);
      }else {
        Keyboard.release(Key_Num_6);
      }
      break;

    case SW16:  // Minus:
      if(mode) {
        Keyboard.press(Key_Num_Minus);
      }else {
        Keyboard.release(Key_Num_Minus);
      }
      break;

    case SW17:  // 1:
      if(mode) {
        Keyboard.press(Key_Num_1);
      }else {
        Keyboard.release(Key_Num_1);
      }
      break;

    case SW18:  // 2:
      if(mode) {
        Keyboard.press(Key_Num_2);
      }else {
        Keyboard.release(Key_Num_2);
      }
      break;

    case SW19:  // 3:
      if(mode) {
        Keyboard.press(Key_Num_3);
      }else {
        Keyboard.release(Key_Num_3);
      }
      break;

    case SW20:  // Enter:
      if(mode) {
        Keyboard.press(Key_Num_Enter);
      }else {
        Keyboard.release(Key_Num_Enter);
      }
      break;

    case SW21:  // 0:
      if(mode) {
        Keyboard.press(Key_Num_0);
      }else {
        Keyboard.release(Key_Num_0);
      }
      break;

    case SW22:  // 00:
      if(mode) {
        Keyboard.press(Key_Num_0);
        delayMicroseconds(4000);
        Keyboard.release(Key_Num_0);
        delayMicroseconds(4000);
        Keyboard.press(Key_Num_0);
        delayMicroseconds(4000);
        Keyboard.release(Key_Num_0);
      }
      break;

    case SW23:  // Dot:
      if(mode) {
        Keyboard.press(Key_Num_Dot);
      }else {
        Keyboard.release(Key_Num_Dot);
      }
      break;

    default:
      // 何もしない:
      break;
  }
#endif
}
