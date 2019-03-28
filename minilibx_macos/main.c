#include <unistd.h>
#include "mlx.h"

void ft_putchar(char c)
{
  write(1, &c, 1);
}

int deal_key(void *key, void *param)
{
  int a;
  int b;

  a = 0;
  b = 0;
  ft_putchar('X');
  while (a < 400 && b < 400)
    {
    mlx_pixel_put(key, param, a, b, 134);
    a++;
    b++;
    }
  return(1);
}

int main()
{
  void *mlx_ptr;
  void *win_ptr;
  int a;

  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, 600, 800, "sonia");
  mlx_key_hook(win_ptr, deal_key, (mlx_ptr,win_ptr));
  mlx_loop(mlx_ptr);
  return(0);
}
