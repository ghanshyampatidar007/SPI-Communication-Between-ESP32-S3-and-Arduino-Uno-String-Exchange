#include "spi.h"

#define SPI_NODE DT_NODELABEL(spi3)

int main(void)
{
    const struct device *spi_dev = DEVICE_DT_GET(SPI_NODE);
    const char msg[max] = "Hello arduniooo";     // Send string
    uint8_t rx_buf[max] = {0};        // Buffer to store received string
   
    spi_tx_rx(spi_dev,msg,rx_buf);
  
   return 0;
}


