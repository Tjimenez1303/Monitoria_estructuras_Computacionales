.equ MY_CARNET, 1002655707  @ Número de carnet en formato decimal

.section .text
.syntax unified
.thumb
.global main

.equ MEM_LOC, 0x20000000

main:
	// Paso 1: Escribir el código de estudiante en memoria
    //Supongamos que la dirección de memoria es 0x200002000
    ldr r0, = MEM_LOC // Dirección de memoria
    ldr r1, = MY_CARNET    // Tu código de estudiante
    str r1, [r0]         // Escribir el código en memoria

    // Paso 2: Decrementar el valor hasta que sea menor que 0
    // Utilizar mes y día de nacimiento: 1303
    ldr r2, =1303        // Mes y día de nacimiento
    ldr r3, [r0]         // Cargar el valor de memoria en R3
decrement_loop:
    sub r3, r3, r2       // Restar mes y día de nacimiento
    cmp r3, #0           // Comparar con 0
    ble iterations_done  // Si es menor o igual que 0, salir del bucle
    add r7, r7, #1       // Incrementar contador de iteraciones
    b decrement_loop      // Volver al bucle

iterations_done:
    // Paso 3: Guardar la cantidad de iteraciones en R7
    // R7 ya contiene la cantidad de iteraciones

    // Paso 4: Saltar a un bucle infinito
infinite_loop:
    B infinite_loop



