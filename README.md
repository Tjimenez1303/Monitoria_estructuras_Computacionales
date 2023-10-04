# Monitoria_estructuras_Computacionales
This repository serves as support material for the monitoring of the subject of computational structures. It explains, through step-by-step examples, how to attack different peripherals of the STM32 card NUCLEOL476RG.

## Assambler Programs
* [M_00_Led_Toggle](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_00_Led_Toggle) : In this first example we will initialize the LED 2 of the NUCLEOL476RG card to later change the state of the LED from high to low and vice versa.
* [M_00_Load_Date_and_Decrement_as](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_00_Load_Date_and_Decrement_as) : This program contains the code of a UNAL student card in memory to decrease its value in memory until it is less than 0. In addition, save the number of iterations in R7. 
* [M_00_SysTick_as](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_00_SysTick_as) : This example we will initialize the SysTick of the card in assembly language. 

## C Programs
* [M_01_Ejemplo_c](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_01_Ejemplo_c) : In this example we will learn how to initialize the step-by-step port of the STM card NUCLEOL476RG.
* [M_02_Input_Button_c](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_02_Input_Button_c) : We will initialize a pin as output (LD2) and a pin as input (USER-B1). Thus, when we press the button the output pin will change state (turn on).

## HAL Programs
### Interrupts
* [M_03_Interrupts_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_03_Interrupts_HAL) : In this project, a button is initialized as an interrupt using the HAL graphical interface in which the button is pressed, throws the interrupt and proceeds to make a toggle of PA5 (LD2).

### UART
* [M_04_UART_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_04_UART_HALL) : In this project we learn how to initialize the USART 2 of the NUCLEOL476RG card and then send a Hello World! by the UART peripheral.
* [M_05_UART_2_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_05_UART_2_HAL) : In this project we learn how to initialize the USART 2 of the NUCLEOL476RG card and then send count by printf by the UART peripheral.
* [M_07_UART_DMA_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_07_UART_DMA_HAL) : In this project we receive by interruptions of the UART a one byte and we implement the printf through the write function with transmission by DMA for its comprobation.
* [M_08_UART_DMA_Rx_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_08_UART_DMA_Rx_HAL) : In this project we receive by DMA 4 bytes activating a flag when it is received completely. Likewise, when receiving completely, two checks are made: one to transmit without DMA and another to transmit with DMA seeing the state in which the UART is to transmit.

### Timers
* [M_09_Timer_HAL](https://github.com/Tjimenez1303/Monitoria_estructuras_Computacionales/tree/main/M_09_Timer_HAL) : In This project consists of initializing two timers. Timer 1 is used for a PWM signal and Timer 7 to increment a counter periodically to be printed by UART.
