#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t LED_BUILTIN = 27;
#define BUILTIN_LED  LED_BUILTIN // backward compatibility

static const uint8_t  UARTA =  0,  RX  =  3,  TX  =  1;
static const uint8_t  UARTB = -1,  RXB =  9,  TXB = 10;
static const uint8_t  UARTC = -1,  RXC = 16,  TXC = 17;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t SS    = 5;
static const uint8_t MOSI  = 23;
static const uint8_t MISO  = 19;
static const uint8_t SCK   = 18;

#endif /* Pins_Arduino_h */
