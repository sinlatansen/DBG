# DBG

一款线程安全的FreeRTOS（cmsis_os2）的日志调试库，基于STM32F4_HAL。

![image-20240401180207986](./README.assets/image-20240401180207986.png)



## 使用方法：

1. 在`uart.c`中重写`fputc`函数。
2. 在系统初始化阶段调用`InitLogSystem();`。
3. 在`DBG.h`中配置参数：
   - `COLOR`：是否开启彩色
   - `CURRENT_LOG_LEVEL`：调整日志等级
4. 如同使用`printf`一样使用`DBG, DBGI, DBGW, DBGE`，Just enjoy it！: )



> [!note]
>
> 如果不想使用串口1或者是别的STM32型号，可以进行简单的修改。FreeRTOS部分通用。