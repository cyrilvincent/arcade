// Clavier PS/2 -> prise clavier Amstrad PCW
// Arduino Uno / Nano (ATmega328P, 5 V)
//
// Le PCW reçoit en boucle l'état complet du clavier : 17 mots de 12 bits
// (4 bits d'offset + 8 bits de données), voir seasip.info/Unix/Joyce/pcwkbd.html
// et le log Hackaday "PCW Keyboard timings" (James Ots).
//
// ATTENTION : polarités et timings du bus PCW à valider avec un analyseur
// logique sur un vrai clavier PCW (constantes marquées "A VALIDER").
//
// Câblage :
//   PS/2 CLK  -> D3 (INT1)      PS/2 DATA -> D4   (pull-up 10 k vers 5 V sur chaque)
//   PCW  CLK  -> D6 via 100 ohm  PCW  DATA -> D7 via 100 ohm
//   GND commun ; +5 V PS/2 depuis l'Arduino

#include <avr/pgmspace.h>

#define PCW_CLK 6
#define PCW_DAT 7

// ---------- A VALIDER ----------
#define PRESSED_IS_ONE 1   // 1 : bit à 1 = touche appuyée (0 : logique inversée)
#define T_SETUP   3        // us : DATA stable avant le front montant de CLK
#define T_HI      10       // us : CLK haut
#define T_LO      11       // us : CLK bas (~21 us entre impulsions d'après J. Ots)
#define T_EXTRA4  27       // us en plus après le 4e bit (~48 us entre bit 4 et 5)
#define T_TOGGLE  10       // us : les 2 bascules de DATA avant chaque mot
#define T_WORD    60       // us entre deux mots
#define T_FRAME   2000     // us entre deux trames
// -------------------------------

#define IDLE (PRESSED_IS_ONE ? 0x00 : 0xFF)

// Numéros de touches PCW (table "CP/M key numbers" de John Elliott).
// La touche 49 est notée "S" sur sa page, mais c'est le "5" (le 5 n'existe nulle part ailleurs).
enum {
  K_F3F4, K_KP0, K_F1F2, K_PASTE, K_KP9, K_KP6, K_KP3, K_KP2,        // 0-7
  K_EXIT, K_PTR, K_CUT, K_COPY, K_KP8, K_KP4, K_KP5, K_KP1,          // 8-15
  K_DELR, K_RBRK, K_RETURN, K_GT, K_KP7, K_SHIFT, K_HALF, K_PLUSB,   // 16-23
  K_EQ, K_MINUS, K_LBRK, K_P, K_LT, K_SEMI, K_QUEST, K_DOT,          // 24-31
  K_0, K_9, K_O, K_I, K_L, K_K, K_M, K_COMMA,                        // 32-39
  K_8, K_7, K_U, K_Y, K_H, K_J, K_N, K_SPACE,                        // 40-47
  K_6, K_5, K_R, K_T, K_G, K_F, K_B, K_V,                            // 48-55
  K_4, K_3, K_E, K_W, K_S, K_D, K_C, K_X,                            // 56-63
  K_1, K_2, K_STOP, K_Q, K_TAB, K_A, K_SHLOCK, K_Z,                  // 64-71
  K_DELL, K_F5F6, K_EXTRA, K_CANCEL, K_MINUSB, K_F7F8, K_KPENTER, K_KPDOT, K_ALT  // 72-80
};

struct Map { uint8_t code, key; };

// PS/2 set 2 (position physique des touches) -> touche PCW
const Map NORMAL[] PROGMEM = {
  {0x1C,K_A},{0x32,K_B},{0x21,K_C},{0x23,K_D},{0x24,K_E},{0x2B,K_F},{0x34,K_G},{0x33,K_H},
  {0x43,K_I},{0x3B,K_J},{0x42,K_K},{0x4B,K_L},{0x3A,K_M},{0x31,K_N},{0x44,K_O},{0x4D,K_P},
  {0x15,K_Q},{0x2D,K_R},{0x1B,K_S},{0x2C,K_T},{0x3C,K_U},{0x2A,K_V},{0x1D,K_W},{0x22,K_X},
  {0x35,K_Y},{0x1A,K_Z},
  {0x16,K_1},{0x1E,K_2},{0x26,K_3},{0x25,K_4},{0x2E,K_5},{0x36,K_6},{0x3D,K_7},{0x3E,K_8},
  {0x46,K_9},{0x45,K_0},
  {0x29,K_SPACE},{0x5A,K_RETURN},{0x66,K_DELL},{0x0D,K_TAB},{0x76,K_STOP},
  {0x12,K_SHIFT},{0x59,K_SHIFT},{0x11,K_ALT},{0x58,K_SHLOCK},
  // symboles : correspondance approximative, à ajuster selon ton clavier
  {0x0E,K_HALF},{0x4E,K_MINUS},{0x55,K_EQ},{0x54,K_LBRK},{0x5B,K_RBRK},
  {0x5D,K_GT},{0x61,K_LT},{0x4C,K_SEMI},{0x41,K_COMMA},{0x49,K_DOT},{0x4A,K_QUEST},
  // F1..F8 -> 4 touches doubles PCW ; F9..F12 -> Cut, Copy, Paste, PTR
  {0x05,K_F1F2},{0x06,K_F1F2},{0x04,K_F3F4},{0x0C,K_F3F4},
  {0x03,K_F5F6},{0x0B,K_F5F6},{0x83,K_F7F8},{0x0A,K_F7F8},
  {0x01,K_CUT},{0x09,K_COPY},{0x78,K_PASTE},{0x07,K_PTR},
  // pavé numérique
  {0x70,K_KP0},{0x69,K_KP1},{0x72,K_KP2},{0x7A,K_KP3},{0x6B,K_KP4},{0x73,K_KP5},
  {0x74,K_KP6},{0x6C,K_KP7},{0x75,K_KP8},{0x7D,K_KP9},
  {0x71,K_KPDOT},{0x79,K_PLUSB},{0x7B,K_MINUSB}
};

// Touches préfixées E0
const Map EXT[] PROGMEM = {
  {0x5A,K_KPENTER},{0x71,K_DELR},
  {0x75,K_KP8},{0x72,K_KP2},{0x6B,K_KP4},{0x74,K_KP6},   // flèches -> KP 8/2/4/6
  {0x11,K_EXTRA},{0x69,K_EXIT},{0x6C,K_CANCEL}            // AltGr, Fin, Origine
};

uint8_t keys[16];
bool led = false;      // LED Shift Lock (octet 0xD, bit 6)
bool tick = false;     // bit 6 de l'octet 0xF, bascule à chaque trame

// ---------- Lignes PCW en collecteur ouvert (émulé via DDRD) ----------
static inline void lineLow(uint8_t b)  { DDRD |=  _BV(b); }   // sortie à 0
static inline void lineHigh(uint8_t b) { DDRD &= ~_BV(b); }   // relâchée (pull-up PCW)

// ---------- Réception PS/2 (interruption sur front descendant de CLK) ----------
volatile uint8_t rb[32];
volatile uint8_t rh, rt;

ISR(INT1_vect) {
  static uint8_t n, d, p;
  static uint32_t last;
  uint32_t now = micros();
  if (now - last > 400) n = 0;               // resynchronisation
  last = now;
  uint8_t b = (PIND >> 4) & 1;               // D4
  if (n == 0)      { d = 0; p = 0; }         // bit start
  else if (n <= 8) { d |= b << (n - 1); p ^= b; }
  else if (n == 9) { p ^= b; }               // parité impaire : p doit valoir 1
  else {                                     // bit stop
    if (p) { rb[rh] = d; rh = (rh + 1) & 31; }
    n = 255;
  }
  n++;
}

static int8_t lookup(const Map* t, uint8_t n, uint8_t c) {
  for (uint8_t i = 0; i < n; i++)
    if (pgm_read_byte(&t[i].code) == c) return pgm_read_byte(&t[i].key);
  return -1;
}

static void setKey(uint8_t k, bool on) {
  uint8_t i, bit;
  if (k <= 71)      { i = k >> 3; bit = k & 7; }
  else if (k == 72) { i = 9;      bit = 7; }
  else              { i = 10;     bit = k - 73; }
  if (on == (PRESSED_IS_ONE != 0)) keys[i] |=  (1 << bit);
  else                             keys[i] &= ~(1 << bit);
}

static void ps2Process() {
  static bool brk, ext;
  while (rh != rt) {
    uint8_t c = rb[rt]; rt = (rt + 1) & 31;
    if (c == 0xE0) { ext = true; continue; }
    if (c == 0xF0) { brk = true; continue; }
    int8_t k = ext ? lookup(EXT, sizeof(EXT) / sizeof(Map), c)
                   : lookup(NORMAL, sizeof(NORMAL) / sizeof(Map), c);
    if (k >= 0) setKey(k, !brk);
    if (!ext && !brk && c == 0x58) led = !led;   // Verr Maj -> bascule la LED
    brk = ext = false;
  }
}

// ---------- Émission vers le PCW ----------
static void sendWord(uint16_t w) {           // 12 bits, MSB en premier
  lineHigh(PCW_DAT); delayMicroseconds(T_TOGGLE);   // 2 bascules de DATA
  lineLow(PCW_DAT);  delayMicroseconds(T_TOGGLE);
  for (int8_t i = 11; i >= 0; i--) {
    if ((w >> i) & 1) lineHigh(PCW_DAT); else lineLow(PCW_DAT);
    delayMicroseconds(T_SETUP);
    lineHigh(PCW_CLK); delayMicroseconds(T_HI);
    lineLow(PCW_CLK);  delayMicroseconds(T_LO);     // DATA lue sur ce front descendant
    if (i == 8) delayMicroseconds(T_EXTRA4);        // pause après le 4e bit
  }
  lineLow(PCW_DAT);
  delayMicroseconds(T_WORD);
}

static void sendFrame() {
  uint8_t s[16];
  for (uint8_t i = 0; i <= 10; i++) s[i] = keys[i];
  s[0xB] = IDLE & 0x3F;                              // touches "joystick" non gérées
  s[0xC] = IDLE & 0x3F;
  s[0xD] = (IDLE & 0x3F) | 0x80 | (led ? 0x40 : 0);  // bit 7 : lien LK2 absent (logique inversée)
  s[0xE] = IDLE & 0x3F;                              // LK1 / LK3 absents
  tick = !tick;
  sendWord(((uint16_t)0xF << 8) | 0x80 | (tick ? 0x40 : 0));   // début de trame
  for (uint8_t o = 0; o <= 0xE; o++) sendWord(((uint16_t)o << 8) | s[o]);
  sendWord(((uint16_t)0xF << 8) | (tick ? 0x40 : 0));          // fin de trame
}

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  lineLow(PCW_CLK);                  // repos : lignes à 0 (observé par J. Ots) - A VALIDER
  lineLow(PCW_DAT);
  for (uint8_t i = 0; i < 16; i++) keys[i] = IDLE;
  EICRA = _BV(ISC11);                // INT1 sur front descendant
  EIMSK = _BV(INT1);
}

void loop() {
  ps2Process();
  sendFrame();
  delayMicroseconds(T_FRAME);
}
