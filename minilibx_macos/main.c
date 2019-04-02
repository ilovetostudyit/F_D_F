
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "mlx.h"
#include "libft/libft.h"
#include "get_next_line.h"

void ft_putchar(char c)
{
  write(1, &c, 1);
}

int deal_key(void *key, void *param)
{
  int a;
  int color;
			color = rand() % 255255255;
			printf("%d\n", color);
			a = 0;
			//1 square
				while (a < 101)
			{
				mlx_pixel_put(key, param, a+200, 300, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, 200, 300+a, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, 300, 300+a, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, a+200, 400, color);
				a++;
			}
			//2 square
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, a+150, 350, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, 150, 350+a, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, 250, 350+a, color);
				a++;
			}
					a = 0;
					while (a < 101)
			{
				mlx_pixel_put(key, param, a+150, 450, color);
				a++;
			}
					//lines
					a = 0;
					while (a < 51)
			{
				mlx_pixel_put(key, param, 200-a, 300+a, color);
				a++;
			}
					a = 0;
					while (a < 51)
			{
				mlx_pixel_put(key, param, 300-a, 300+a, color);
				a++;
			}
					a = 0;
					while (a < 51)
			{
				mlx_pixel_put(key, param, 200-a, 400+a, color);
				a++;
			}
					a = 0;
					while (a < 51)
			{
				mlx_pixel_put(key, param, 300-a, 400+a, color);
				a++;
			}
return(1);
}

int line_size(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\n')
		i++;
	return(i);
}

int matrix_size(char *str)
{
	int i;
	int a;
	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			a++;
		i++;
	}
	return(a+1);
}

char *ft_matrix_transform(int **mass, char *str)
{
	int i;
	int x;
	int y;
	int size;
	int count;
	int count2;

	i = line_size(str);
	x = 0;
	y = 0;
	count = 0;
	count2 = 0;
	size = matrix_size(str);
	while (y < size)
	{
		mass[count2][0] = x;
		mass[count2][1] = y;
		//mass[count2][2] = ft_atoi(str[count]);
		x++;
		count++;
		count2++;
		if (x == i)
		{
			x = 0;
			y++;
			count++;
		}
	}
	return(0);
}

int **ft_create_matrix(int **mass, int x, int y)
{
	int size;
	int cnt;
	int i;

	i = 0;
	cnt = 0;
	size = (x * y) + 1;
	mass = (int **)malloc(sizeof(int*) * size);
	while (cnt < (size - 1))
	{
		mass[cnt] =(int *)malloc(sizeof(int) * 4);
		while (i < 4)
		{
			mass[cnt][i] = 0;
			i++;
		}
		i = 0;
		cnt++;
	}
	mass[cnt] = 0;
	return(mass);
}

int ft_mass_size(char *file)
{
	int a;
	int fd;
	char *new;

	a = 0;
	fd = open(file, O_RDONLY);
	new = (char *)malloc(sizeof(*new) * 1);
	while (new)
	{
		get_next_line(fd, &new);
		a++;
	}
	close(fd);
	return(a);
}

int max_words(char *file)
{
	int a;
	int b;
	int fd;
	char *arg;

	fd = open(file, O_RDONLY);
	get_next_line(fd, &arg);
	a = 0;
	b = 0;
	while(arg[a] != '\0')
	{
		if (arg[a] == ' ')
		{
			b++;
			while (arg[a] && arg[a] == ' ')
				a++;
		}
		a++;
	}
	close(fd);
	return(b);
}

char **creating_newmass(char *arg, int fd, char **new)
{
	int x;
	int y;
	int ch;

	y = max_words(arg);
	ch = 0;
	fd = open(arg, O_RDONLY);
	x = ft_mass_size(arg);
	close(fd);
	fd = open(arg, O_RDONLY);
	new = (char**)malloc(sizeof(char*)*x);
	while (ch <= y)
	{
		new[ch] = (char *)malloc(sizeof(char)*x);
		get_next_line(fd, &new[ch]);
		ch++;
	}
	return(new);
}

int main(int argv, char **argc)
{
	int fd;
	void *mlx_ptr;
	void *win_ptr;
	char *b;
	int **mass;
	char **new;

	if (argv == 2)
	{
		fd = open(argc[1], O_RDONLY);
		new = creating_newmass(argc[1], fd, new);
		b = "00000\n01110\n01210\n01110\n00000";
		mass = ft_create_matrix(mass, line_size(b), matrix_size(b));
		ft_matrix_transform(mass, b);
		mlx_ptr = mlx_init();
		win_ptr = mlx_new_window(mlx_ptr, 600, 600, "sonia");
		mlx_key_hook(win_ptr, deal_key, (mlx_ptr,win_ptr));
		mlx_loop(mlx_ptr);
	}
	else
	{
		ft_putstr("error \n");
	}

	return(0);
}
