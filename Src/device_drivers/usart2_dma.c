//
// Created by Ethan Fischer on 11/10/26.
//

#include "device_drivers/usart2_dma.h"

#define USART_BRR(clk, baud) (((clk) + (baud / 2U)) / (baud))

volatile uint8_t usart2_rx;
volatile bool usart2_rx_cplt;

void usart2_dma_init(void)
{

    // Configure USART2:

    // turn on GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // configure GPIO pins
    GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW, GPIO_PULL_NONE);
    GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_ALTERNATE, GPIO_OTYPE_PUSHPULL, GPIO_OSPEED_LOW, GPIO_PULL_NONE);
    GPIO_SetAlternateFunction(GPIOA, GPIO_PIN_2, GPIO_AF7); // AF7 on PA2 is USART2_TX
    GPIO_SetAlternateFunction(GPIOA, GPIO_PIN_3, GPIO_AF7); // AF7 on PA3 is USART2_RX

    // enable USART2 peripheral
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // set oversample to 16, word length to 8 data bits, and no parity control
    USART2->CR1 &= ~(USART_CR1_OVER8 | USART_CR1_M | USART_CR1_PCE);

    usart2_dma_ioctl(SET_BAUDRATE, USART2_BAUDRATE);

    // enable USART, transmitter, receiver, and rx interrupt
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;

    // Configure DMA1:
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN; // turn on DMA clock
    DMA1_Stream5->CR &= DMA_SxCR_EN; // disable DMA stream5
    while ((DMA1_Stream5->CR & DMA_SxCR_EN)) {} // wait till DMA stream is disabled
    // clear stream5 interrupt flags
    DMA1->HIFCR = DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTCIF5;


    NVIC_EnableIRQ(USART2_IRQn);
}

void dma1_stream5_usart2_rx_config(void) {


}


void usart2_dma_close(void) {
    NVIC_DisableIRQ(USART2_IRQn);
    USART2->CR1 = 0UL; // Reset value disables USART, transmitter, receiver, and rx interrupt
    RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN; // disable USART2 peripheral
}

void usart2_dma_write(const uint8_t tx)
{
    // make sure transmit data register is empty
    while (!(USART2->SR & USART_SR_TXE)) {}

    // write to transmit data register
    USART2->DR = tx;
}

void usart2_dma_write_buf(const uint8_t* buf, const uint16_t len)
{
    if (len > MAX_BUF_LEN) { return; }
    for (uint16_t i = 0; i < len; i++) {
        usart2_dma_write(buf[i]);
    }
}

char usart2_dma_read(void)
{
    // wait for data in rx data register
    while (!(USART2->SR & USART_SR_RXNE)) {}
    return ((char)USART2->DR);
}

void usart2_dma_ioctl(const USART_IOCTL_t cmd, const uint32_t data) {
    switch (cmd) {
        case SET_BAUDRATE:
            USART2->BRR = USART_BRR(PERIPH_CLK_SPEED, data);
            break;
        default:
            break;
    }
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & (USART_SR_RXNE | USART_SR_ORE)) {
        // ignore overrun error for now - a cmd will be lost but not a problem in this context
        usart2_rx = USART2->DR; // read SR then DR clears ORE flag
        usart2_rx_cplt = true;
    }
}
