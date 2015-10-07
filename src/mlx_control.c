#include <fdf.h>
#include <stdio.h>
#include "mlx.h"
#include "mlx_int.h"

int	key_control(int key)
{
	printf("tecla : %d\n",key);
	if (key==0xFF1B)
		exit(0);
	return (0);
}

void	*expose_win(t_env_graph *env)
{
	mlx_loop(env->mlx);
	mlx_clear_window(env->mlx, env->win);
	return (void *)env;
}

void start_mlx(t_env_graph *env)
{
	if (!(env->mlx = mlx_init()))
	{
		perror(" !! KO !!");
		exit(1);
	}
	if (!(env->win = mlx_new_window(env->mlx, WIN_SX, WIN_SY,"fdf")))
	{
		perror(" !! KO !!");
		exit(1);
	}
	draw_map(env->line_list, env->mlx, env->win);
	mlx_key_hook(env->win,key_control,0);
	mlx_expose_hook(env->mlx,expose_win(env), 0);
}