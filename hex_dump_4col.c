
void dump_hex(unsigned char *p,int len)
{
        int i;
        printf("\n");
        for(i = 0; i < len; i++)
        {
                printf("%s",(i != 0 && i % 16 == 0)? "\n" : "") ;
                printf("%s",( i != 0 &&  i % 4 == 0 && i % 16 != 0) ? "  " : "");
                printf("%02X ",p[i]) ;

        }

        printf("\n");
}
