/**
 * @file     DBG.c
 * @brief    一个基于FreeRTOS的线程安全的日志库
 *
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-04-01
 *
 */


#include "DBG.h"


QueueHandle_t logQueue;

int current_log_level = LOG_LEVEL_DEBUG;


static void LogTask(void* parameters)
{
    LogMessage_t receivedMsg;
    for (;;)
    {
        if (xQueueReceive(logQueue, &receivedMsg, portMAX_DELAY) == pdPASS)
        {
            printf("%s", receivedMsg.msg);
        }
    }
}

void InitLogSystem(void)
{
    logQueue = xQueueCreate(LOG_QUEUE_LENGTH, LOG_QUEUE_ITEM_SIZE);
    if (logQueue != NULL)
    {
        xTaskCreate(LogTask,
                    "LogTask",
                    LOG_TASK_STACK_SIZE,
                    NULL,
                    tskIDLE_PRIORITY + 1,
                    NULL);
    }
}

void LogMessage(int level, const char* file, int line, const char* format, ...)
{
    if (level < current_log_level || logQueue == NULL)
        return;

    char     timeBuffer[30];
    uint32_t ticks        = HAL_GetTick();
    uint32_t seconds      = ticks / 1000;
    uint32_t milliseconds = ticks % 1000;
    snprintf(timeBuffer,
             sizeof(timeBuffer),
             "[%lu.%03lu]",
             seconds,
             milliseconds);

    char    logBuffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(logBuffer, sizeof(logBuffer), format, args);
    va_end(args);

    LogMessage_t message;
    snprintf(message.msg,
             sizeof(message.msg),
             "%s %s[%d]: %s\n",
             timeBuffer,
             file,
             line,
             logBuffer);

    xQueueSend(logQueue, &message, portMAX_DELAY);
}
