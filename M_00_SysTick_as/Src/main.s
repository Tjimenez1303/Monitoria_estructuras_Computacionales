/*
 * main.s
 *  Created on: Aug 28, 2023
 *      Author: saaci
 */
    .section .text
    .syntax unified
    .thumb
    .global main
    .global SysTick_Handler

/** The LD2 of the NUCLEO is connected to PA5
    Steps to control the Green LED:
    1. Enable the GPIOA Clock
    2. Set the Pin as Output
    3. Set/Reset the bit 5 in the output register
*/

/* The RCC (Reset and Clock Control) is the
   subsystem to Enable/Disable any clock */
.equ RCC_BASE,           0x40021000 @ RM0351 page 79
.equ RCC_AHB2_OFFSET,    0x4C       @ RM0351 page 251
.equ RCC_AHB2_GPIOA,     0x00000001 @ LSB of AHB2 clk enable register

/* The systick is part of the peripherals of the processor
   thus it is in memory region 0xE0000000 (RM0351 page 76) */
.equ 	SYSTICk_BASE,	 0xE000E010
.equ 	SYSTICk_CTRL_OFFSET,	0x0		// SysTick Control and Status Register
.equ 	SYSTICk_LOAD_OFFSET,	0x4		// SysTick reload Value Register
.equ 	SYSTICk_VAL_OFFSET,	    0x8		// SysTick Current Value Register
.equ 	SYSTICk_CALIB_OFFSET,	0xC		// SysTick Calibration Register


.equ GPIOA_BASE,         0x48000000 @ RM0351 page 78

.equ GPIOA_MODER_OFFSET, 0x00       @ RM0351 page 303
.equ GPIOA_MODER_MASK,   0x03       @ This is to clear the bits
.equ GPIOA_MODER_OUTPUT, 0x01       @ This is to set as output

.equ GPIOA_ODR_OFFSET,   0x14       @ RM0351 page 306
.equ GPIOA_PIN_ODR_MASK, 0x01       @ a single bit per pin

.equ GPIO_PIN_5,         5


init_systick:
	ldr r0, = SYSTICk_BASE

	ldr r1, = (4000 - 1)
	str r1, [r0, #SYSTICk_LOAD_OFFSET]
	ldr r1, = 0
	str r1, [r0, #SYSTICk_VAL_OFFSET]
	ldr r1, [r0, SYSTICk_CTRL_OFFSET]
	ldr r2, = 0b111
	orr r1, r1, r2
	str r1, [r0, SYSTICk_CTRL_OFFSET]

	ldr r7, = 0
	bx lr

.type	SysTick_Handler,%function
SysTick_Handler:
	push {lr}
	add r7,#1
	pop {pc}

gpioa_clk_en:
	@ Enable the GPIOA Clock
	ldr r6, = RCC_BASE             @ load the RCC address into R6
	ldr r5, [r6, RCC_AHB2_OFFSET]  @ read the current value of the AHB2 CLK enable reg
	orr r5, RCC_AHB2_GPIOA         @ set the bit 0 to enable GPIOA
	str r5, [r6, RCC_AHB2_OFFSET]  @ write the updated value into the AHB2 CLK enable reg
	bx lr

gpio_config_pin:
	@ Configure the Pin 5 of GPIOA as output
	lsl r1, r1, #1                   @ r1 = r1 * 2 (PA5 -> bits 10 and 11) RM0351 page 303
	ldr r2, [r0, GPIOA_MODER_OFFSET] @ read the current value of MODER
	ldr r3, = GPIOA_MODER_MASK       @ load the mask (0x11 for 2 bits)
	lsl r3, r3, r1                   @ move the mask to the correct position
	bic r2, r3                       @ clear the bytes for pin
	ldr r3, = GPIOA_MODER_OUTPUT     @ load the value to set as output (0x00: Input, 0x01: Output)
	lsl r3, r3, r1                   @ move the value to the correct bits (PA5 -> bits 10 and 11)
	orr r2, r3                       @ set the value as output for pin 5
	str r2, [r0, GPIOA_MODER_OFFSET] @ write the updated value in MODER
	bx lr

gpio_toggle_pin:
	@ Toggle Pin 5
	ldr r2, [r0, GPIOA_ODR_OFFSET] @ read the current value of the output register
	ldr r3, = GPIOA_PIN_ODR_MASK   @ r3 = 0x1 (ths mask is 1 bit wide)
	lsl r3, r3, r1                 @ r3 = r3 << r1 (PA5 -> 0x1 << 5)
	eor r2, r3                     @ set the value of the bit
	str r2, [r0, GPIOA_ODR_OFFSET] @ write the updated value in the output register
	bx lr

main:
	bl init_systick
	bl gpioa_clk_en

	ldr r0, = GPIOA_BASE @ preload the port address as first argument
	ldr r1, = GPIO_PIN_5 @ preload the pin as second argument
	bl gpio_config_pin

loop:
	ldr r0, = GPIOA_BASE @ preload the port address as first argument
	ldr r1, = GPIO_PIN_5 @ preload the pin as second argument
	bl gpio_toggle_pin

	b loop               @ Stay in this loop forever
