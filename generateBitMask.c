include <stdio.h>

#define BITS_PER_BYTE   ((unsigned int)(8))

unsigned int GenMask(unsigned int par1, unsigned int par2)
{
    unsigned int Mask;
    unsigned int begin,end,index;

    if((par1 >= (sizeof(unsigned int) * BITS_PER_BYTE)) ||
       (par2 >= (sizeof(unsigned int) * BITS_PER_BYTE))
       )
    {
            return 0x00000000;
    }

    begin = (par1 <= par2) ? par1 : par2;
    end   = (par1 > par2)  ? par1 : par2;

    Mask = 0x00000001UL << begin;

    for(index = begin; index <= end; index++)
    {
        Mask |= (1 <<  index);
    }
    return Mask;
}

/* Test code */
int main(int argc, char **argv)
{
    printf("Mask : 0x%08x\n",GenMask(2,9));
    printf("Mask : 0x%08x\n",GenMask(0,21));
    printf("Mask : 0x%08x\n",GenMask(0,31));
    printf("Mask : 0x%08x\n",GenMask(0,7));
    printf("Mask : 0x%08x\n",GenMask(8,15));
    printf("Mask : 0x%08x\n",GenMask(16,23));
    printf("Mask : 0x%08x\n",GenMask(1,12));
    printf("Mask : 0x%08x\n",GenMask(1,10));
    printf("Mask : 0x%08x\n",GenMask(10,1));
    printf("Mask : 0x%08x\n",GenMask(24,31));
    printf("Mask : 0x%08x\n",GenMask(0,32));  /* -Ve Test  */
    return 0;
}
