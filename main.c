/*Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. 
Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

void *const timer_id;
TimerHandle_t my_timer_handler;

//-------Timer Callback Function Started-------//
void myTimerCallback(TimerHandle_t xTimer)
{
    printf("Inside OneShot Timer callback\n");
}
//-------Timer Callback Function Ended---------//

void Task1_task(void *data)
{
    while(1)
    {
        printf(" task1 started \n");
        //...............//
        printf(" task1 ended \n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);

    }
}

void Task2_task(void *data)
{
    while(1)
    {
        printf(" task2 started \n");
        //...............//
        printf(" task2 ended \n");
        vTaskDelay(2000/ portTICK_PERIOD_MS);

    }
}

void Task3_task(void *data)
{

   printf("Created task 3, Periodicity = 5000ms\n");
   
    while(1)
    {
        printf(" task3 started \n");
        
        //---------Software Timer to Trigger Callback Function after 10,000 ms--------//

        my_timer_handler = xTimerCreate("my_timer",(10000 / portTICK_PERIOD_MS),pdFALSE,timer_id, myTimerCallback);
        /(timer name, timer tick period, autoreload, timer id, timer call back function)/
   
        xTimerStart(my_timer_handler, 1);  //Here we are starting the Timer
    
        //----------------------------------------------------------------------------//

        printf(" task3 ended \n");
        vTaskDelay(5000/ portTICK_PERIOD_MS);

    }
   //vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(Task1_task, "T1_tsk", 2048, NULL, 1, NULL);
    xTaskCreate(Task2_task, "T2_tsk", 2048, NULL, 2, NULL);
    xTaskCreate(Task3_task, "T3_tsk", 2048, NULL, 3, NULL);
   
   while(1)
   {
      vTaskDelay(5000 / portTICK_PERIOD_MS);
   }
   
}
