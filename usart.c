#pragma import(__use_no_semihosting)
struct __FILE {
  int handle;
};                               // 标准库需要的支持函数
FILE __stdout;                   // FILE 在stdio.h文件
void _sys_exit(int x) { x = x; } // 定义_sys_exit()以避免使用半主机模式

int fputc(int ch,
          FILE *f) // 重定向fputc函数，使printf的输出，由fputc输出到UART,
                   // 这里使用串口1(USART1)
{
  // if(xFlag.PrintfOK == 0) return 0;  //
  // 判断USART是否已配置，防止在配置前调用printf被卡

  while ((USART1->SR & 0X40) == 0)
    ;                       // 等待上一次串口数据发送完
  USART1->DR = (uint8_t)ch; // 写DR,串口1将发送数
  return ch;
}
