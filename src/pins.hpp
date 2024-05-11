#ifndef MY_STM32_LIBRARY_PINS_HPP
#define MY_STM32_LIBRARY_PINS_HPP

namespace STM32 {
  constexpr uint8_t LCD_REG = PB2; // LCD register select pin
    constexpr uint8_t LCD_EN = PB1; // LCD enable pin
    constexpr uint8_t LCD_D4 = PA4; // LCD data pin 4
    constexpr uint8_t LCD_D5 = PA5; // LCD data pin 5
    constexpr uint8_t LCD_D6 = PA6; // LCD data pin 6
    constexpr uint8_t LCD_D7 = PA7; // LCD data pin 7

    constexpr uint8_t BUTTON_1 = PD0; // Button 1 pin
    constexpr uint8_t BUTTON_2 = PD1; // Button 2 pin
    constexpr uint8_t BUTTON_3 = PD2; // Button 3 pin
    constexpr uint8_t BUTTON_4 = PD3; // Button 4 pin

    constexpr uint8_t IR_REMOTE_RX = PE0; // IR remote receiver pin
}

#endif
