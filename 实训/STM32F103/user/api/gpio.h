#ifndef _GPIO_H_
#define _GOIO_H_


#define LED1(X) X?(GPIOB->ODR &= ~(0x1 << 5)):(GPIOB->ODR |=  (0x1 << 5))
#define LED2(X) X?(GPIOE->ODR &= ~(0x1 << 5)):(GPIOE->ODR |=  (0x1 << 5))
#define LED3(X) X?(GPIOA->ODR &= ~(0x1 << 5)):(GPIOA->ODR |=  (0x1 << 5))
#define LED4(X) X?(GPIOA->ODR &= ~(0x1 << 6)):(GPIOA->ODR |=  (0x1 << 6))
void gpio_Init(void);

#endif


