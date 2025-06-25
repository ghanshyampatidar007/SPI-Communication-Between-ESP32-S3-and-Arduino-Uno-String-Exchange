#include "spi.h"

//#define CS_GPIO_CONTROLLER DT_NODELABEL(gpio0)

LOG_MODULE_REGISTER(spi_master, LOG_LEVEL_INF);

void spi_tx_rx(const struct device *spi_dev,const char *msg,char *rx_buf){
    gpio_pin_t CS_PIN;
    const struct device *cs_gpio;
    if(spi_dev->name[8]=='4'){
        CS_PIN=10;
        cs_gpio = DEVICE_DT_GET( DT_NODELABEL(gpio0));
    }
    else{
        CS_PIN=38;
        cs_gpio = DEVICE_DT_GET( DT_NODELABEL(gpio1));
    }

    
    
    if (!device_is_ready(spi_dev) || !device_is_ready(cs_gpio)) {
        LOG_ERR("Device not ready");
        return;
    }
    
    //spi@60024000  spi@60025000
    printk("%s  %c\n",spi_dev->name,spi_dev->name[8]);
    printk("%s \n",cs_gpio->name);

    gpio_pin_configure(cs_gpio, CS_PIN, GPIO_OUTPUT_HIGH);

    struct spi_config spi_cfg = {
        .frequency = 1000000,
        .operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB,
        .slave = 0,
    };

    size_t len = max;
    
    while (1) {
        for (size_t i = 0; i < len; ++i) {
            struct spi_buf txb = { .buf = (void *)&msg[i], .len = 1 };
            struct spi_buf rxb = { .buf = &rx_buf[i], .len = 1 };
            struct spi_buf_set tx = { .buffers = &txb, .count = 1 };
            struct spi_buf_set rx = { .buffers = &rxb, .count = 1 };

            gpio_pin_set(cs_gpio, CS_PIN, 0);
            int ret = spi_transceive(spi_dev, &spi_cfg, &tx, &rx);
            gpio_pin_set(cs_gpio, CS_PIN, 1);

            if (ret) {
                LOG_ERR("SPI transceive failed: %d", ret);
                break;
            }

        
        }

        LOG_INF("Received from slave: %s", rx_buf);
        k_sleep(K_SECONDS(2));
    }
}