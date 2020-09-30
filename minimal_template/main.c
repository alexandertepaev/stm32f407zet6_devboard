#define SRAM_BASE       0x20000000U
#define PERIPH_BASE     0x40000000U
 
#define SRAM_SIZE       128*1024 
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
 
#define RCC_BASE        (PERIPH_BASE + 0x00023800)
#define RCC_AHB1ENR     (*(volatile unsigned long*)(RCC_BASE + 0x30))

#define GPIOF_CLK_BIT	5

#define GPIOF_BASE      (PERIPH_BASE + 0x00020000 + 0x00001400)
#define GPIOF_MODER     (*(volatile unsigned long*)(GPIOF_BASE + 0x00))
#define GPIOF_ODR       (*(volatile unsigned long*)(GPIOF_BASE + 0x14))

#define LED0_PIN         9
#define LED1_PIN         10

// busy-wait sleep
void sleep(unsigned long time)
{
    while(time--);
}

int main()
{
    // Enable clock on GPIOF
    RCC_AHB1ENR |= 1 << GPIOF_CLK_BIT;

    // Put GPIOE9 into output mode
    GPIOF_MODER |= (0x01 << LED0_PIN*2) | (0x01 << LED1_PIN*2);

    // turn LED0 on, low active
    GPIOF_ODR = (1 << LED0_PIN);

    while(1)
    {
        sleep(400000);
        GPIOF_ODR ^= (1<<LED0_PIN | 1<<LED1_PIN); // toggle leds
    }
}

unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)SRAM_END,   // stack pointer -> end of SRAM 

    (unsigned long *)main        // jump directly to main after reset
};