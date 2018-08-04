#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "pins_arduino.h"
#include "HardwareSerial.h"

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)

  HardwareSerial  Serial ( UARTA );   // UARTx = 0, 1, 2, or undefined (-1). Values
  HardwareSerial  Serial1( UARTB );   // set in variant 'pins_arduino.h' file
  HardwareSerial  Serial2( UARTC );

#endif  // 'no globals'

HardwareSerial::HardwareSerial(int uart_nr) : _uart_nr(uart_nr), _uart(NULL) {}

void HardwareSerial::changeUartNumber( int uart_nr )
{
    if(_uart) {
        end();
    }
    _uart_nr = uart_nr;
}

void HardwareSerial::begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
{
    if ( (-1 > _uart_nr) || (_uart_nr > 2) ) {
        log_e("Serial number is invalid, please use 0, 1, 2, or undefined (-1)");
        return;
    }
    if(_uart) {
        end();
    }

    // Use 'variant' file RX/TX pin values if:
    //   a) The physical UART number is defined (0,1, or 2), and
    //   b) Both the given RX/TX pins are undefined (-1)

    if ( (_uart_nr >= 0) && (rxPin < 0) && (txPin < 0) )
    {
       if(_uart_nr == UARTA ) {
           rxPin = RX;
           txPin = TX;
       }
       if(_uart_nr == UARTB ) {
           rxPin = RXB;
           txPin = TXB;
       }
       if(_uart_nr == UARTC ) {
           rxPin = RXC;
           txPin = TXC;
       }

       if ( (rxPin < 0) && (txPin < 0) ) {
          log_e( "Variant file RX/TX cannot both be undefined (-1)" );
       }
    } //end-if, set defaults

    // 'uartBegin()' handles an undefined:
    //   a) Physical UART number (returns NULL)
    //   b) RX/TX pin pair       (returns NULL)
    //   c) RX or TX pin         ('half'  UART config)

    _uart = uartBegin(_uart_nr, baud, config, rxPin, txPin, 256, invert);
}

void HardwareSerial::end()
{
    if(uartGetDebug() == _uart_nr) {
        uartSetDebug(0);
    }
    uartEnd(_uart);
    _uart = 0;
}

void HardwareSerial::setDebugOutput(bool en)
{
    if(_uart == 0) {
        return;
    }
    if(en) {
        uartSetDebug(_uart);
    } else {
        if(uartGetDebug() == _uart_nr) {
            uartSetDebug(0);
        }
    }
}

int HardwareSerial::available(void)
{
    return uartAvailable(_uart);
}
int HardwareSerial::availableForWrite(void)
{
    return uartAvailableForWrite(_uart);
}

int HardwareSerial::peek(void)
{
    if (available()) {
        return uartPeek(_uart);
    }
    return -1;
}

int HardwareSerial::read(void)
{
    if(available()) {
        return uartRead(_uart);
    }
    return -1;
}

void HardwareSerial::flush()
{
    uartFlush(_uart);
}

size_t HardwareSerial::write(uint8_t c)
{
    uartWrite(_uart, c);
    return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
    uartWriteBuf(_uart, buffer, size);
    return size;
}
uint32_t  HardwareSerial::baudRate()

{
	return uartGetBaudRate(_uart);
}
HardwareSerial::operator bool() const
{
    return true;
}
