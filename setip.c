#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include <stdio.h>


void SetIP(const char *interface, const char *ip, const char *mask)
{
        struct ifreq ifr;
        struct sockaddr_in* addr;
        char * name;
        int fd;

        if(NULL == interface || NULL == ip || NULL == mask)
        {
                printf("Invlid param., \n");
                return;
        }

        fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

        strncpy(ifr.ifr_name, interface, IFNAMSIZ);

        ifr.ifr_addr.sa_family = AF_INET;
        addr = (struct sockaddr_in*)&ifr.ifr_addr;
        inet_pton(AF_INET, ip, &addr->sin_addr);
        ioctl(fd, SIOCSIFADDR, &ifr);

        inet_pton(AF_INET, mask, &addr->sin_addr);
        ioctl(fd, SIOCSIFNETMASK, &ifr);

        ioctl(fd, SIOCGIFFLAGS, &ifr);
        strncpy(ifr.ifr_name, name, IFNAMSIZ);
        ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

        ioctl(fd, SIOCSIFFLAGS, &ifr);



}

int main(int argc, const char *argv[]) {
        SetIP("usb0:1","192.168.7.7","255.255.255.0");
        return 0;
}
