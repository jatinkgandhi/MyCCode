#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


int expect(char *value, int max_charwait);
/* TEST CODE */
void GSM_MODEM_SendSMS(char *number, char *sms)
{
    /* GSM Modem dummy function To Send SMS */
}
int main()
{
    int exp;
    char *what;
    int within_how_many_characters;
    int retries;

    printf("Testing the expect() functionality\n");

    GSM_MODEM_SendSMS("9999999999", "OK");

    /* We sent the command to GSM modem via serial and expect OK!..,*/
    what = "OK!";
    within_how_many_characters = 10;
    retries = 5;
    while(retries--)
    {
        printf("Please enter expect string : ");
        exp = expect(what,within_how_many_characters);
        if(exp)
        {
            printf("Found %s within %d characters\n",what, within_how_many_characters);
        }else
        {
            printf("%s Not found within %d characters\n",what, within_how_many_characters);
        }
    }
    return 0;
}

/* FIXME: Enhancements
a) "TIMEOUT"
b) If expected value is part of some other string e.g., expecting OK, and we got "Not OK",
still it will give false positive. Add fix for handing such cases OK != NOK, OK != N OK
We have to buffer the characters received so far and if found, we have to go back in past and
check for negative cases..,

*/

/*
 * Returns 0 if not found and 1 if found
 * IGNORES case.., can be  configured to either ignore or
 not to ignore.
*/
/* FIXME: Not suitable for Micro-controllers with less RAM. Optimize this */
int expect(char *value, int max_charwait)
{
    char ch;
    static char local_stream[255];
    int local_stream_idx;
    static char expected_str[255];
    int    expected_str_idx;
    int index;
    index = 0;
    if(NULL == value || '\0' == value[0]) return 0;

    if(0 >= max_charwait) max_charwait = 40;

    memset(expected_str,0,sizeof(expected_str));

    for(expected_str_idx = 0; expected_str_idx < strlen(value); expected_str_idx++)
    {
        ch = value[expected_str_idx];
        expected_str[expected_str_idx] = (ch >='A' && ch<='Z') ? (ch + 32) : (ch);
    }

    memset(local_stream, 0, sizeof(local_stream));
    local_stream_idx = 0;

    while(1 && (0 != max_charwait--))
    {
        ch = getch(); /* FIXME: replace actual stream e.g. UART etc.., */

        if(local_stream_idx < sizeof(local_stream))
        {
            /* Buffer locally only if we have space !!!!!*/
            /* Store upper case converted.., only */
            local_stream[local_stream_idx++] = (ch >='A' && ch<='Z') ? (ch + 32) : (ch);
            printf("%s\n",local_stream);
        }
        if(ch ==  expected_str[index])
        {
            index++;
            if(index == strlen(expected_str))
            {
                /* Found whole string */
                /* Check for negative scenario */
                if(NULL != strstr(local_stream, "not") &&
                   NULL == strstr(expected_str, "not")
                )
                {
                    /* We found "NOT" in the input stream,
                       also "NOT" is absent in the expected stream..,
                       So its clearly Not <Expected stream>
                       like expecting OK, but got Not OK */
                    return 0;
                }else
                {
                        return 1;
                }

            }
        }else
        {
            index = 0;
        }
    }
    return 0;
}


