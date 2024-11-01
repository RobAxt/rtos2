#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "app.h"
#include "task_led.h"

void task_ui(void* argument)
{
    int event;
    while (true)
    {
        if (xQueueReceive(ui_queue, &event, portMAX_DELAY) == pdPASS)
        {
        	led_event_t led_event = LED_NONE;
            switch (event)
            {
                case BUTTON_TYPE_PULSE:
                	led_event = LED_RED_BLINK;
                    xQueueSend(led_red_queue, &event, ( TickType_t ) 0);
                    break;
                case BUTTON_TYPE_SHORT:
                	led_event = LED_YELLOW_BLINK;
                    xQueueSend(led_yellow_queue, &event, ( TickType_t ) 0);
                    break;
                case BUTTON_TYPE_LONG:
                	led_event = LED_BLUE_BLINK;
                    xQueueSend(led_blue_queue, &event, ( TickType_t ) 0);
                    break;
                default:
                    break;
            }
        }
    }
}
