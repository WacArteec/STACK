#include <stdio.h>
#include <StacK.h>
#include <string.h>

int main()
{
    for(int i = 0; i<100; i++)
    {
        SPush(i);
    }
    printf("\nlook = %d \n", SLook(12));

    for(int i = 0; i<100; i++)
    {
        printf("%d \n", SPull());
    }
    return 0;
}
