#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "task.h"

#define TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define MY_INT_GPIO 15
#define GLOBAL_DEBOUNCE_DELAY 2000

// set up globals
TaskHandle_t mainTaskHandle;
volatile uint32_t last_interrupt_time = 0;

// led toggler
bool toggle_led(bool led_state)
{
    gpio_put(PICO_DEFAULT_LED_PIN, led_state);
    return !led_state;
}

// interrupt handler
void handleInterruptPin15(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    bool shouldFireDebounce = (current_time - last_interrupt_time) > GLOBAL_DEBOUNCE_DELAY;

    if ((events & GPIO_IRQ_EDGE_FALL) && shouldFireDebounce)
    {
        last_interrupt_time = current_time;
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTaskNotifyIndexedFromISR(mainTaskHandle, 0, 0, eSetBits, &xHigherPriorityTaskWoken);
    }
}

// main task
void mainTask(void *params)
{
    const unsigned delays[2] = {500, 1000};
    int delay_idx = 0;
    bool toggled = false;

    for (;;)
    {
        BaseType_t ret = xTaskNotifyWait(0x0, 0xffffffff, NULL, delays[delay_idx]);

        if (ret)
        {
            delay_idx = 1 - delay_idx;
        }

        toggled = toggle_led(toggled);
    }
}

int main()
{
    // init led
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // init GPIO
    gpio_init(MY_INT_GPIO);
    gpio_set_dir(MY_INT_GPIO, GPIO_IN);
    gpio_pull_up(MY_INT_GPIO);
    gpio_set_irq_enabled_with_callback(MY_INT_GPIO, GPIO_IRQ_EDGE_FALL, true, &handleInterruptPin15);

    xTaskCreate(mainTask, "MainThread", 500, NULL, TASK_PRIORITY, &mainTaskHandle);

    // start task scheduler
    vTaskStartScheduler();
}