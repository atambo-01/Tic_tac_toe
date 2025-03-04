#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>


int f_atoi(const char *nptr)
{
    int     sign = 1;
    long    res = 0;
	int		dig = 0;

    while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
        nptr ++;
    if (*nptr == '-')
	{
        sign = -1;
        nptr ++;
    }
    else if (*nptr == '+')
        nptr ++;
    while (*nptr >= '0' && *nptr <= '9')
    {
        res = res * 10 + ((char)(*nptr) - '0');
        if ((res * sign > 2147483647) || (res * sign < -2147483648))
            return (0);
        nptr++;
		dig++;
    }
	if (*nptr != '\0' || dig == 0)
		return (-1);
    return ((int)(res * sign));
}


int main()
{
	int i = 0;
	int n = 0;
	int error = 0;
	char *line = malloc(1);
	char grid[3][6] = {{"X__"}, {"___"}, {"___"}};
	while(1)
	{
		system("clear");
		free(line);
		if(error != 0)
		{
			if 		(error == 1)
				printf("Bad input! Try again\n");
			else if (error == 2) 
				printf("Square is ocupied! try again\n");
			else 
				printf("-----------------------------\n");
			error = 0;
		}
		i = 0;
		printf("-----------------------------\n");
		while(i < 3)
		{
			printf("\t%c|%c|%c\n", grid[i][0], grid[i][1], grid[i][2]);
			i++;
		}
		printf("\n");
		line = readline	(	"Choose where to place 'X'\n\n"
							"\t0|1|2\n\t3|4|5\n\t6|7|8\n> ");
		n = f_atoi(line);
		printf("selected %d = [%d][%d]\n", n, n/3, n%3);
		if (n < 0 || n > 8)
		{
			error = 1;
			continue;
		}
		else if (grid[n/3][n%3] != '_')
		{
			error = 2;
			continue;
		}
		grid[n/3][n%3] = 'O';
		usleep(100000);
	}
}
