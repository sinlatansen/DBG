/**
 * @file     DBG.h
 * @brief    一个基于FreeRTOS的线程安全的日志库的头文件
 *
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-04-01
 *
 */

#ifndef DBG_H_INCLUDED
#define DBG_H_INCLUDED

#include "FreeRTOS.h"
#include "queue.h"
#include "stm32f4xx_hal.h"
#include "task.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 日志队列配置
#define LOG_QUEUE_LENGTH    10
#define LOG_QUEUE_ITEM_SIZE sizeof(LogMessage_t)
#define LOG_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE * 4)

typedef enum Log_Levle_e
{
    LOG_LEVEL_NONE  = -1,
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_ERROR = 3
} Log_Levle_e;


// 颜色配置
#define DEBUG_COLOR "\033[0;36m"
#define INFO_COLOR  "\033[0;32m"
#define WARN_COLOR  "\033[0;33m"
#define ERROR_COLOR "\033[0;31m"
#define COLOR_RESET "\033[0m"

// 是否开启彩色
#define COLOR 1

// 定义默认的日志等级
#ifndef CURRENT_LOG_LEVEL
#    define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif
extern int current_log_level;

// 日志消息结构
typedef struct
{
    char msg[256];   // 增加缓冲区大小以适应更长的消息
} LogMessage_t;

/********************************   函数   ********************************/
void InitLogSystem(void);
void LogMessage(int level, const char* file, int line, const char* format, ...);

// 定义日志宏
#define DBG(format, ...)                                 \
    LogMessage(LOG_LEVEL_DEBUG,                          \
               __FILE__,                                 \
               __LINE__,                                 \
               DEBUG_COLOR "DEBUG: " format COLOR_RESET, \
               ##__VA_ARGS__)
#define DBGI(format, ...)                              \
    LogMessage(LOG_LEVEL_INFO,                         \
               __FILE__,                               \
               __LINE__,                               \
               INFO_COLOR "INFO: " format COLOR_RESET, \
               ##__VA_ARGS__)
#define DBGW(format, ...)                              \
    LogMessage(LOG_LEVEL_WARN,                         \
               __FILE__,                               \
               __LINE__,                               \
               WARN_COLOR "WARN: " format COLOR_RESET, \
               ##__VA_ARGS__)
#define DBGE(format, ...)                                \
    LogMessage(LOG_LEVEL_ERROR,                          \
               __FILE__,                                 \
               __LINE__,                                 \
               ERROR_COLOR "ERROR: " format COLOR_RESET, \
               ##__VA_ARGS__)

#endif /* DBG_H_INCLUDED */
