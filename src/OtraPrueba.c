#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 3; i++)
    {
        printf("N: ");
        int n;
        scanf("%d", &n);
        if (n == 1)
        {
            i--;
        }
        printf("Vuelta %d\n", i);
        
    }
    return 0;
}
