#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/gpio.h"
#include "pico/time.h"

const uint PIR_PIN = 10;
const uint LED_PIN = 11;  // LED that signals motioin detection
const uint BUSY_PIN = 25; // Built-in LED of Pico     
const uint CALIBRATION_TIME = 6;

//
// IRQ handler called when rising or falling edge is detected
//
void pir_irq_handler(uint gpio, uint32_t event) {
    if (event == GPIO_IRQ_EDGE_RISE) // rising edge => detection of movement
      gpio_put(LED_PIN, 1); // turn LED on
    else // falling edge
      gpio_put(LED_PIN, 0);
}


//
// function used to calibrate PIR sensor
//
void calibrate () {
    for (uint counter = 0; counter < CALIBRATION_TIME; counter++){
      gpio_put(BUSY_PIN, 1);
      sleep_ms(500);
      gpio_put(BUSY_PIN, 0);
      sleep_ms(500);
    }    
    puts("Calibration completed");
}

int main()
{
    stdio_init_all();
    gpio_init(LED_PIN); // init LED Pin: used to signal motion detection
    gpio_set_dir(LED_PIN, GPIO_OUT); // LED Pin is an output pin
    gpio_init(BUSY_PIN); // init BUSY Pin: used to blink during calibration
    gpio_set_dir(BUSY_PIN, GPIO_OUT); // BUSY Pin is an output pin

     // Calibrate PIR for CALIBRATION_TIME seconds
    calibrate();
   
    // Enable interrupt handling for PIR Pin:
    // Interrupt hanling for rising or falling edges
    gpio_set_irq_enabled_with_callback(PIR_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &pir_irq_handler);
    while(true); // wait forever
    return 0;
}
