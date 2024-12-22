# DX_Ball_Project

TM4C123GH6PM Microcontroller
A microcontroller is a compact integrated circuit designed to govern a specific operation in an embedded system. A typical microcontroller includes a processor, memory and input/output (I/O) peripherals on a single chip.

Overview. The Tiva C Series microcontrollers. provide a broad portfolio of floating- point enabled ARM Cortex-M4F. MCUs.

The Tiva™ C Series TM4C123G LaunchPad Evaluation Board (EK-TM4C123GXL) is a low-cost evaluation platform for ARM® Cortex™-M4F-based microcontrollers. The Tiva C Series LaunchPad also features programmable user buttons and an RGB LED for custom applications.

Arm Cortex-M4F 32-bit Arm Cortex-M4F based MCU with 80 -MHz, 256 -KB Flash, 32 -KB RAM, 2 CAN, RTC, USB, 64-Pin LQF.

Programmable timers can be used to count or time external events that drive the Timer input pins. The TM4C123GH6PM General-Purpose Timer Module (GPTM) contains six 16/32-bit GPTM blocks and six 32/64-bit Wide GPTM blocks.

Memory. 256 kb Flash memory. 32 kb single-cycle SRAM with internal ROM loaded with TivaWare software.

Drivers
Timers: Timers control the speed of the ball's movement, ensuring smooth updates by delaying actions, like in Delay100ms().

UART (Universal Asynchronous Receiver/Transmitter): While not explicitly used in this code, UART would be essential for communication (e.g., sending data to a PC or debugging).

PortF (GPIO PortF): Used to control LEDs or buttons for game status indicators or user input (like life count or game-over signals).

Interrupts: Interrupts would manage asynchronous events, such as button presses or specific time intervals, allowing real-time interactions during the game.

Importance: These drivers and peripherals enable efficient game control, user interaction, and real-time feedback, making the game responsive and engaging on embedded systems.

GameLogic
Game Setup: Variables track the player's score, ball position, speed, and grid.

Ball and Paddle Collision: The ball’s direction changes based on where it hits the paddle.
Ball and Grid Collision: The ball destroys blocks on the grid, changing direction and increasing the score.

Boundary and Reset: The ball changes direction on screen boundaries and resets if it falls below the paddle, costing the player a life.

Game Over: The game ends if the player loses all lives or if all blocks are destroyed.
Rendering and Display: The game is visually updated on the Nokia5110 display, with ball movements and grid changes shown.

The hardware
Breadboard
Tiva-C kit
Nokia 5110 blue screen
2 LEDs
2 switches
2 resistors
jumpers
The software
the game code runs with interrupt, timer and drivers
the game has 3 levels with 3 life attempts











![WhatsApp Image 2024-12-22 at 16 25 39_8b0d67d8](https://github.com/user-attachments/assets/6c8f86ac-bf7c-4292-b290-cbc0f14e7526)




![WhatsApp Image 2024-12-22 at 16 25 02_b21dc5f0](https://github.com/user-attachments/assets/c127307e-1446-4919-9bb9-8b8fed9f8be0)






![WhatsApp Image 2024-12-22 at 16 25 06_ad4b00da](https://github.com/user-attachments/assets/cb99f4da-6413-48c7-9aba-11c8edf0493e)


