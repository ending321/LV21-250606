#include <stdint.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <getopt.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <linux/types.h> 
#include <linux/spi/spidev.h> 

static const char *device = "/dev/spidev0.0";
static uint8_t mode; 
static uint8_t bits = 8; 
static uint32_t speed = 400000; 

static void pabort(const char *s) 
{ 
    perror(s); 
    abort(); 
} 
int main(int argc, char *argv[]) 
{ 
    int ret = 0; 
    int fd; 

    if(argc != 2) {
        printf("%s <num>\n", argv[0]);
        return -1;
    }
    fd = open(device, O_RDWR); //打开设备文件 
    if (fd < 0) 
        pabort("can't open device");

    /*
     * spi mode //设置 spi 设备模式
     */ 
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode); //写模式 
    if (ret == -1) 
        pabort("can't set spi mode"); 

    /*
     * bits per word //设置每个字含多少位
     */ 
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits); //写每个字含多少位 
    if (ret == -1) 
        pabort("can't set bits per word"); 

    /*
     * max speed hz //设置速率
     */ 
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed); //写速率 
    if (ret == -1) 
        pabort("can't set max speed hz"); 

    //打印模式,每字多少位和速率信息 

    int i = 0;
    unsigned char num[20] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 
                             0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
    int pos = 0;
    unsigned int num1;
    unsigned char buf[2] = {};
    int t = 300;
    while(t--) { 
        if(sscanf(argv[1], "%04x", &num1) != 1) {
            printf("argment error.\n");
            continue;
        }
        for(i = 0; i < 4; i++) {
            pos = 1 << i;
            buf[0] = pos;
            //buf[1] = num[ (num1 & (0xf << (i*4))) >> (i*4)];
            buf[1] = num[(num1 >> ((4-i)*4)) & 0xf];
            if (write(fd, buf, 2) < 0)
                perror("write");
            usleep(300000);
        }
    } 
    buf[1] = 0x0;
    write(fd, buf, 2);
    close(fd);
    return ret; 
} 
