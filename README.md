# register

register library is the header only library which provides access to the hardware registers and manipulation of their bits. The inspiration for the library is "Modern C++ White paper:
Making things do stuff" written by Glennan Carnie.

The library supports different sizes of registers(8, 16, 32 and 64) and the access modifiers(read-write, read-only and write-only). 
Based on the size, register library uses appropriate type for data and (uint8_t, uint16_t, uint32_t or uint64_t, respectively):
```cpp
// 8bit long register at 0x1234 address
reg::register_t<8, reg::access_modes::read_write> reg { 0x1234 }
reg::uint8_t data = reg; // reading the data from the register
reg |= 0x10; // bit-wise OR
reg &= 0x11; // bit-wise AND
```
 The some operations can be disabled based on the access modifiers. For example, is not possible to read from register with read-only access modifier: 
```cpp
reg::register_t<16, reg::access_modes::read_only> ro_reg {0x1234};
reg::uint16_t data {0xFFFF};
ro_reg = data; // error: static assertion failed: Register doesn't provide write access.
```

The situation is same for the write-only registers:
```cpp
reg::register_t<16, reg::access_modes::write_only> wo_reg {0x1234};
reg::uint16_t data  {0xFFFF};
wo_reg = data; //OK!
reg::uint16_t value = wo_reg; // static assertion failed: Register doesn't provide read access.
```
Additionally, the register library supports the individual bits manipulation with the index operator:
```cpp
reg::register_t<8, reg::access_modes::read_write> reg { 0x1234 }
reg[5] = 1;
reg::uint8_t one = reg[5];
```

## Types
In order to simplify usage, the library provides the following types (aliases):
Name  | Description
------------- | -------------
reg8_rw_t  | 8bit read-write register
reg8_ro_t  | 8bit read-only register
reg8_wo_t  | 8bit write-only register
reg16_rw_t  | 16bit read-write register
reg16_ro_t  | 16bit read-only register
reg16_wo_t  | 16bit write-only register
reg32_rw_t  | 32bit read-write register
reg32_ro_t  | 32bit read-only register
reg32_wo_t  | 32bit write-only register
reg64_rw_t  | 64bit read-write register
reg64_ro_t  | 64bit read-only register
reg64_wo_t  | 64bit write-only register


## From C to Modern C++
The LED blink example implemented in C:
```cpp
 #define BLINK_DELAY_MS 5000
 #define F_CPU 16000000
 #include <util/delay.h>

 #define DDRB (*(volatile uint8_t*) 0x24)
 #define PORTB (*(volatile uint8_t*) 0x25)

 int main ()
 {
   // Arduino digital pin 13 (pin 5 of PORTB) for output
   DDRB |= 0B100000; // PORTB5

    while(1) {
     // turn LED on
     PORTB |= 0B100000; // PORTB5
     _delay_ms(BLINK_DELAY_MS);

     // turn LED off
     PORTB &= ~ 0B100000; // PORTB5
     _delay_ms(BLINK_DELAY_MS);
   }
 }
```
Can be rewritten in C++ with the register library in the following way:
```cpp

 int main ()
 {
   reg::reg8_rw_t ddrb  { 0x24 };
   reg::reg8_rw_t portb { 0x25 };
   
   ddrb[5] = 1; // PORTB5

   while(true) {
      // turn LED on
      portb[5] = 1; // PORTB5
      _delay_ms(BLINK_DELAY_MS);
      // turn LED off
      portb[5] = 0; // PORTB5
      _delay_ms(BLINK_DELAY_MS);
   }
 }

```
With the zero abstraction cost: [Compiler Explorer](https://godbolt.org/z/sKcsP69z7)

## Porting
For the platforms which compiler doesn't support standard library (AVR for example), the following have to be defined:
*  uint8_t, uint16_t, uint32_t and uint64_t need to be defined in [type.hpp](https://github.com/aDakic/register/blob/main/include/register/common/types.hpp).
* The header with the assert definition need to be included in [assert.hpp](https://github.com/aDakic/register/blob/main/include/register/common/assert.hpp).
