#include <stdio.h>
#include <stdlib.h>

  
unsigned char isEnvVarOn(char *VarName)
{
        unsigned char return_val;
        char *pEnvVar;
		
        pEnvVar = NULL;
        return_val = 0;
        pEnvVar = getenv(VarName);
        if(NULL != pEnvVar)
        {
            if(0 == strcasecmp(pEnvVar,"on"))
            {
                /* fprintf(stderr,"jating: %s is ON\n",VarName); */
                return_val = 1;
            }
        }
        return return_val;
}


int main(int argc, char **argv)
{
        printf("Env: %s is %s\n","JATIN", isEnvVarOn("JATIN") ? "ON": "OFF");
        return 0;
}
