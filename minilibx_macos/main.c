
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

char **creating_newmass(char *arg, int fd, char **new, int x, int y)
{
	int ch;

	ch = 0;
	new = (char**)malloc(sizeof(char*)*x);
	while (ch < x)
	{
		new[ch] = (char *)malloc(sizeof(char)*(y));
		ft_bzero(new[ch], y);
		get_next_line(fd, &(new[ch]));
		ch++;
	}
	new[ch] = "\0";
	return(new);
}

int ** matrix_transform(char **new, int **mass, char *arg, int x, int y)
{
	int i;
	int cnt;
	int cnt2;
	char **a;

	cnt = 0;
	cnt2 = 0;
	a = malloc(sizeof(char *) * 10000);
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	i = 0;
	while (i < (x - 1))
	{
		//a = malloc(sizeof(char *) * 1000);
		a = ft_strsplit(new[i], ' ');
		while(cnt < y)
		{
			//printf("%d\n", cnt);
			mass[cnt2][0] = i;
			mass[cnt2][1] = cnt;
			mass[cnt2][2] = ft_atoi(a[cnt]);
			printf("%d, %d, %d\n", mass[cnt2][0], mass[cnt2][1], mass[cnt2][2]);
			cnt++;
			cnt2++;
		}
		//free(a);
		cnt = 0;
		//printf("%d\n", i);
		i++;
	}
	return(mass);
}

int ** create_int_mass(int **mass, char *arg, int x, int y)
{
	int size;

	x = ft_mass_size(arg);
	printf("x = %d\n", x);
	size = ((x - 1)	*(max_words(arg)));
	printf("%d\n", size);
	mass = (int **)malloc(sizeof(int *) * size);
	x = 0;
	while (x < size)
	{
		mass[x] = (int *)malloc(sizeof(int) * 4);
		mass[x][0] = 0;
		mass[x][1] = 0;
		mass[x][2] = 0;
		x++;
	}
	return(mass);
}

int main(int argv, char **argc)
{
	int fd;
	void *mlx_ptr;
	void *win_ptr;
	int **mass;
	char **new;
	int x;
	int y;
	int i;
	if (argv == 2)
	{
		fd = open(argc[1], O_RDONLY);
		x = ft_mass_size(argc[1]);
		y = max_words(argc[1]);
		new = creating_newmass(argc[1], fd, new, x, y);
		i = 0;
		while  (new[i] != '\0')
		{
			printf("%s\n", new[i]);
			i++;
		}
		close(fd);
		mass = create_int_mass(mass, argc[1], x, y);
		mass = matrix_transform(new, mass, argc[1], x, y);
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
