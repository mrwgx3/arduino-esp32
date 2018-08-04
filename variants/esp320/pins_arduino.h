#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 11
#define NUM_DIGITAL_PINS        12
#define NUM_ANALOG_INPUTS       5

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t LED_BUILTIN = 5;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t  UARTA =  0,  RX  =  3,  TX  =  1;
static const uint8_t  UARTB = -1,  RXB =  9,  TXB = 10;
static const uint8_t  UARTC = -1,  RXC = 16,  TXC = 17;

static const uint8_t SDA = 2;
static const uint8_t SCL = 14;

static const uint8_t SS    = 15;
static const uint8_t MOSI  = 13;
static const uint8_t MISO  = 12;
static const uint8_t SCK   = 14;

#endif /* Pins_Arduino_h */
