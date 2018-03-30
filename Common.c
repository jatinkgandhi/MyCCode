/* Common C Algorithms etc.., */

int ifloor( float x )
{
    if (x >= 0)
    {
        return (int)x;
    }
    else
    {
        int y = (int)x;
        return ((float)y == x) ? y : y - 1;
    }
}

int ma_ceil(float num)
{   int a = num;
    if ((float)a != num)
        return num+1;

    return num;
}

