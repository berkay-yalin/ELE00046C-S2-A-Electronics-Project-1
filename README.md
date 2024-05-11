meow tehe,

WARNING: project only runs with a STM32CubeMX extension as i havent embedded such libraries into the project as of yet.
//this is a public repository dedicated to a year 1 game project


mbed-tools new ELE00046C-S2-A-Electronics-Project-1

mbed-tools detect

mbed-tools configure -m NUCLEO_G071RB -t ARM

mbed-tools compile -m NUCLEO_G071RB -t GCC_ARM
