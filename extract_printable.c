/* Function to extract printable characters 
   Useful to dump packets.., as %s in printf will stop after '\0' */
   
static char *extract_printable (char *data, int len)
{
        int index, index2;
        static char buff[255];
        if(NULL == data || 0 == len)
        {
                return "";
        }

        memset(buff, 0, 255);
        for(index = 0, index2 = 0; index < len; index++)
        {
                if(index2 >= 255)
                {
                        break;
                }

                if(data[index] >= 0x20 && data[index] <= 0x7E)
                {
                        /* Printable character */
                        buff[index2] = data[index];
                        index2++;
                }
        }

        return buff;
}
