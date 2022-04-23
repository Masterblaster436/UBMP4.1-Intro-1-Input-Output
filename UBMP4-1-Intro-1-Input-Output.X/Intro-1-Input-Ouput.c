/*==============================================================================
 Project: Intro-1-Input-Output
 Date:    March 1, 2022
 
 This example UBMP4.1 input and output program demonstrates pushbutton input,
 LED (bit) output, port latch (byte) output, time delay functions, and simple
 'if' condition structures.
 
 Additional program analysis and programming activities demonstrate byte output,
 logical condition operators AND and OR, using delay functions to create sound,
 and simulated start-stop button functionality.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// The main function is required, and the program begins executing from here.

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        // If SW2 is pressed, make a flashy light pattern
        if(SW2 == 0)
        {
            LED3 = 1;
            __delay_ms(100);
            LED4 = 1;
            __delay_ms(100);
            LED5 = 1;
            __delay_ms(100);
            LED6 = 1;
            __delay_ms(100);
            LED3 = 0;
            __delay_ms(100);
            LED4 = 0;
            __delay_ms(100);
            LED5 = 0;
            __delay_ms(100);
            LED6 = 0;
            __delay_ms(100);
        }
        
        // Add code for your Program Analysis and Programming Activities here:

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Learn More - Program Analysis Activities
 * 
 * 1. How many times do the LEDs flash if SW2 is quickly pressed and released?
 *    Do the LEDs keep flashing when SW2 is held? Look at the program and
 *    explain why this happens when SW2 is held.
 * 
 * The LEDs flash 4 times when SW2 is quickly pressed and released. Yes, the LEDs keep flashing when SW2 is held because as long as SW2 is pressed, the LEDs will keep flashing.
 *
 *
 * 2. Explain the difference between the statements: LED3 = 0; and LED3 = 1;
 *
 * LED3 = 0; means that LED3 will never turn on even when SW2 is pressed and LED3 = 1; means that LED3 will turn on when SW2 is pressed.
 * 
 * 3. What voltage do you expect the microcontroller to output to LED D3 when
 *    the statement LED3 = 0; runs? What voltage do you expect the output to be
 *    when the statement LED3 = 1; runs?
 * 
 * 0 volts when LED3 = 0, 3 volts when LED3 = 1.
 *
 *    You can confirm the output voltage with a voltmeter if you have access
 *    to one. If you tried that, did the voltage match your prediction?
 * 
 * Yes, the voltage nearly matched my prediction because it was 0 volts when LED3 = 0 and about 3.5 volts when LED3 = 1.
 *
 * 4. The statement 'if(SW2 == 0)' uses two equal signs, while the statement
 *    'LED3 = 1;' uses a single equal sign. What operation is performed by one
 *    equal sign? What operation is performed by two equal signs?
 *
 * LED3 = 1 sets the value of LED3 to 1, which turns it on. SW2 == 0 checks whether SW2 being equal to 0 is true or false.
 * 
 * 5. The following program code includes instructions that write to the PORTC
 *    output latches directly. Try it by copying and pasting this code below
 *    the existing SW2 'if' structure, at the location shown by the comment.

        if(SW3 == 0)
        {
            LATC = 0b00000000;
            __delay_ms(100);
            LATC = 0b11110000;
            __delay_ms(100);
        }

 *    What happens when pushbutton SW3 is pressed? Identify at least one
 *    advantage and one disadvantage of controlling the LEDs using 'LATC' writes
 *    rather than through individual 'LEDn = x;' statements.
 * 
 * When SW3 is pressed, 4 LEDS turn on, though stay on until SW2 is pressed or is unplugged. LATC writes can control multiple LEDs at once, but keep running.
 *
 * 6. Next, compare the operation of 'if' and 'while' structures to simulate
 *    momentary buttons. Replace the code you added in 5, above, with this code:

        // Momentary button using if structure
        if(SW3 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

        // Momentary button using while structure
        while(SW4 == 0)
        {
            LED5 = 1;
        }
        LED5 = 0;

 *    First, try pressing and releasing SW3 and SW4 one at a time.
 * 
 *    Next, press and hold SW3 while pressing and releasing SW4. Does it work
 *    as expected?
 * 
 *    Yes, it works.
 *
 *    Next, try press and holding SW4 while pressing and releasing SW3. Does it
 *    work as expected? Explain the difference in operation between the 'if' and
 *    'while' structures making up the momentary button code.
 * 
 *    No, it does not work as expected. ‘if’ will run its chunk of code as long as the condition is true. ‘while’ will run its chunk of code until it makes the condition true.
 *
 * 7. Let's explore logical conditions using 'if' statements. Replace the code
 *    added in 6, above, with this nested if code to make a logical AND
 *    condition that will light LED D4 only if both SW3 and SW4 are pressed:

        // Nested if 'AND' code
        if(SW3 == 0)
        {
            if(SW4 == 0)
            {
                LED4 = 1;
            }
            else
            {
                LED4 = 0;
            }
        }
        else
        {
            LED4 = 0;
        }

 *    Test the code to ensure it works as expected. Does the order of the if
 *    conditions matter? (eg. swap the conditional checks for SW3 and SW4)
 * 
 *    No, the order does not matter.
 *
 * 8. Next, replace the code from 7 with the following code which implements a
 *    logical AND conditional operator composed of two ampersands '&&':
 
        // Conditional 'AND' code
        if(SW3 == 0 && SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Does '&&' work the same way as the nested if structures? Can you think of
 *    at least one advantage of using a logical conditional operator instead of
 *    nested if structures?
 * 
 *    Yes, ‘&&’ works the same way as the nested if structures. One advantage is that there is less code to type and read.
 *
 * 9. Replace the double ampersand '&&' with double vertical bars '||)' to make
 *    a logical OR conditional operator. Your code should look like this:
  
        // Conditional 'OR' code
        if(SW3 == 0 || SW4 == 0)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Describe the conditions under which LED4 turns on.
 * 
 *    If Switch 3 or Switch 4 is pressed.
 *
 * Programming Activities
 * 
 * 1. The statement '__delay_ms(100);' creates a 100ms delay. Try changing one
 *    or more of the delay values in the program to 500ms and see what happens.
 * 
 *    Can the delay be made even longer? Try 1000 ms. How big can the delay be
 *    before MPLAB-X produces an error message? (Hint: can you think of a fast
 *    and efficient way of guessing an unknown number?)
 * 
 *    Yes, the delay can be made even longer. The delay can be 4205ms long before MPLAB-X produces an error message.
 *
 * 2. The '__delay_ms();' function only accepts integers as delay values. To
 *    make delays shorter than 1ms, specify a delay in microseconds using the
 *    '__delay_us();' function. You won't be able to see such short LED flashes
 *    with your eyes, but you could measure them using an oscilloscope, or hear
 *    them if they are used to turn the piezo beeper on and off. Try this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = 1;
            __delay_us(567);
            BEEPER = 0;
            __delay_us(567);
        }

 *    Try changing the delay values in both of the __delay_us(); functions.
 *    Does the pitch of the tone increase or decrease if the delay value is
 *    made smaller?
 * 
 *    The pitch of the tone decreases when the delay value is made smaller.
 *
 * 3. This code demonstrates a more compact way of toggling the beeper output
 *    using a logical NOT operator '!'. Replace the code above, with this code:
 
        // Make a tone while SW5 is held
        if(SW5 == 0)
        {
            BEEPER = !BEEPER;
            __delay_us(567);
        }

 *    One difference between this code and the code in 2, above, is the state
 *    of the BEEPER pin when SW5 is released. What state will the BEEPER output
 *    be in after this code runs? While one advantage of this method is smaller
 *    code, can you think of one or more disadvantages based on its output when
 *    the button is released?
 * 
 *    The BEEPER output will be the opposite of what it originally was. Unfortunately, BEEPER will stay as !BEEPER until the button is pressed again.
 *
 * 4. Using modified versions of the original SW2 'if' structure, create a
 *    program that makes a unique LED flashing pattern for each pushbutton.
 *    
 *    if(SW2 == 0)
 *      {
 *          LED3 = 1;
 *          __delay_ms(100);
 *          LED5 = 1;
 *          __delay_ms(100);
 *          LED4 = 1;
 *          __delay_ms(100);
 *          LED6 = 1;
 *          __delay_ms(100);
 *          LED3 = 0;
 *          __delay_ms(100);
 *          LED5 = 0;
 *          __delay_ms(100);
 *          LED4 = 0;
 *          __delay_ms(100);
 *          LED6 = 0;
 *          __delay_ms(100);
 *      }
 *
 *      if(SW3 == 0)
 *      {
 *          LED3 = 1;
 *          __delay_ms(100);
 *          LED4 = 1;
 *          __delay_ms(100);
 *          LED5 = 1;
 *          __delay_ms(100);
 *          LED6 = 1;
 *          __delay_ms(100);
 *          LED3 = 0;
 *          __delay_ms(100);
 *          LED4 = 0;
 *          __delay_ms(100);
 *          LED5 = 0;
 *          __delay_ms(100);
 *          LED6 = 0;
 *          __delay_ms(100);
 *      }
 *
 *      if(SW4 == 0)
 *      {
 *          LED6 = 1;
 *          __delay_ms(100);
 *          LED5 = 1;
 *          __delay_ms(100);
 *          LED4 = 1;
 *          __delay_ms(100);
 *          LED3 = 1;
 *         __delay_ms(100);
 *          LED6 = 0;
 *          __delay_ms(100);
 *          LED5 = 0;
 *          __delay_ms(100);
 *          LED4 = 0;
 *         __delay_ms(100);
 *          LED3 = 0;
 *         __delay_ms(100);
 *      }
 *
 *      if(SW4 == 0)
 *      {
 *          LED4 = 1;
 *          __delay_ms(100);
 *           LED6 = 1;
 *           __delay_ms(100);
 *           LED5 = 1;
 *           __delay_ms(100);
 *           LED3 = 1;
 *           __delay_ms(100);
 *           LED4 = 0;
 *          __delay_ms(100);
 *          LED6 = 0;
 *          __delay_ms(100);
 *           LED5 = 0;
 *           __delay_ms(100);
 *           LED3 = 0;
 *           __delay_ms(100);
 *       }

 *
 *    Test each of your flashing patterns. Describe what happens when more than
 *    one button is held. Do all of the patterns try to flash the LEDs at the
 *    same time, or sequentially? Explain why this is.
 * 
 *    When more than one button is pressed, each pattern runs one at a time because a block of code needs to finish running before another block can start running.
 *
 * 5. Create a program that makes a different tone for each pushbutton.
 * 
 *    Test each tone by pressing each button individually. Next, press two or
 *    more buttons at the same time. Describe what the tone waveform would look
 *    like when more than one button is held.
 * 
 *    The tone waveform would look like multiple waves.
 *
 * 6. Use individual 'if' structures to simulate 'Start' and 'Stop' buttons for
 *    an industrial machine. LED D4 should turn on when SW3 is pressed, stay on
 *    even after SW3 is released, and turn off when SW4 is pressed. Test your
 *    program to make sure it works.
 * 
 *    if(SW3 == 0)
 *      {
           LED4 = 1;
          
 *      }
 *
 *      if(SW4 == 0)
 *      {
 *          LED4 = 0;
 *     }
 *
 *
 * 7. Running your program from 6, above, describe what happens when both SW3
 *    and SW4 are pressed. Does LED D4 stay on? If so, how does the brightness
 *    of LED D4 compare between its normal on state following SW3 being pressed
 *    to this new state when both SW3 and SW4 are bing held? Can you explain
 *    why it changes?
 * 
 *    When both SW3 and SW4 are pressed, LED4 continuously turns on and off. 
 *    It appears to remain on, though dimmer because it is turning on and off at such a fast rate that it looks like it is dimmer.
 *
 * 8. As you can imagine, an industrial machine that is able to turn on even
 *    while its 'Stop' button is pressed represents a significant safety hazard.
 *    Using a logical conditional operator, modify the start-stop program from
 *    activity 5 to make it safer. SW3 should only turn on LED D4 if SW4 is
 *    released.
 * 
 *    if(SW3 == 0 && SW4 == 1)
 *      {
 *          LED4 = 1;
 *      }
 * else
 *       (SW4 == 0)
 *      {
 *          LED4 = 0;
 *      }
 *
 *
 * 9. LED D1 is normally used to indicate that a program is running, but it can
 *    be controlled by your program as well. If you take a look at the UBMP4
 *    schematic, you will see that LED D1's cathode (or negative) pin is
 *    connected to the microcontroller instead of the anode (positive) pin as
 *    with the other LEDs. This means that you need to make D1's output a zero
 *    to turn D1 on. Try it! Make a program that controls or flashes LED D1.
 *
 *    if(SW2 == 0)
       {
           LED1 = 0;
			__delay_ms(100);
       }

 */
