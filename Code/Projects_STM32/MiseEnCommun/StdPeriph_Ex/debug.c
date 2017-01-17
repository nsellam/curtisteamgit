#include <stdio.h>
#include <stm32f10x.h>
#include "debug.h"

struct __FILE {int handle;/* Add whatever you need here */};

FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  ITM_SendChar(ch);
  return(ch);
}
