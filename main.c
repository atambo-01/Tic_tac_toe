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

int	get_rand(int min, int max)
{
	return(min + rand() % (max - min  + 1));
}

int check_game(char  ***p_grid, char c)
{
	int 	h = 0;
	int 	v = 0;
	int 	d1 = 0;
	int 	d2 = 0;

	int 	i = 0;
	int  	j = 0;
	char 	**grid = *p_grid;

	i = 0;
	while(i < 3)
	{
		j = 0;
		h = 0;
		while(j < 3)
		{
			if (grid[i][j] == c)
				h++;
			if (grid[j][i] == c)
				v++;
			if (i == j && grid[i][j] == c)
				d1++;
			if ((i + j == 2) && grid[i][j] == c)
				d2++;
			if (h == 3 || v == 3 || d1 == 3 || d2 == 3)
				return (1);
			j++;
		}
		i++;	
	}
	return(0);
}

void game_over(char c, char  ***p_grid, char **line)
{
	int		i = 0;
	char	**grid = *p_grid;

	if (c == 'X')
		printf("Game over! 'X' has won!\n");
	else
		printf("Game over! 'O' has won!\n");
	free(*line);
	while(i < 4)
	{
		free(grid[i]);
		i++;
	}
	free(*p_grid);
	exit(0);
}

void f_play(char ***p_grid, int *p_n, char  **line)
{
	int		n = *p_n;
	int 	m = 0;
	int 	set = 0;
	char  	**grid = *p_grid;
	
	grid[n/3][n%3] = 'X';
	if (check_game(p_grid, 'X') == 1)
		game_over('X', p_grid, line);
	while(set == 0)
	{
		m = get_rand(0, 8);
		if (grid[m/3][m%3] == '_')
		{
			grid[m/3][m%3] = 'O';
			set = 1;
			if (check_game(p_grid, 'O') == 1)
				game_over('O', p_grid, line);
		}
	}
}


int main()
{
	int i = 0;
	int n = 0;
	int error = -1;
	char *line = NULL;
	char **grid = malloc(sizeof(char *) * 4);
	
	grid[0] = strdup("___");
	grid[1] = strdup("___");
	grid[2] = strdup("___");
	grid[3] = NULL;

	while(1)
	{
		system("clear");
		if (line)
			free(line);
		if 		(error == 1)
			printf("Bad input! Try again\n");
		else if (error == 2) 
			printf("Square is ocupied! try again\n");
		else 
			printf("\n");
		error = 0;
		i = 0;
		printf("------------------------\n\n");
		while(i < 3)
		{
			printf("\t%c|%c|%c\n", grid[i][0], grid[i][1], grid[i][2]);
			i++;
		}
		printf("\n");
		line = readline	(	"Choose where to place 'X'\n\n"
							"\t0|1|2\n\t3|4|5\n\t6|7|8\n "
							"\n------------------------\n> "	);
		n = f_atoi(line);
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
		f_play((char ***)(&grid), &n, &line);
		usleep(100000);
	}
}
