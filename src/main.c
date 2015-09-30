#include <fdf.h>
#include "mlx.h"
#include "mlx_int.h"
#include <stdio.h>
#include <fcntl.h>

void draw_line2(t_coord p1, t_coord p2, void *mlx, void *win){
	float	a;
	float	b;

	a =  (p1.y - p2.y) / (p1.x - p2.x);
	b = p1.y - a * p1.x;
	while (p1.x != p2.x)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
		p1.x += (p1.x > p2.x) ? -1 : 1;
		p1.y = a * p1.x + b;
	} 
}

void draw_line(t_coord p1, t_coord p2, void *mlx, void *win){
	float	a;
	float	b;

	a =  (p1.y - p2.y) / (p1.x - p2.x);
	b = p1.y - a * p1.x;
	while (p1.x != p2.x)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0x00ff00);
		p1.x += (p1.x > p2.x) ? -1 : 1;
		p1.y = a * p1.x + b;
	} 
}

int	color_lines2(void *mlx, void *win, t_coord map_c, int i, int *line)
{
	t_coord p2;

	p2.x = map_c.x - 20;
	p2.y = map_c.y + 20 - line[i] + line[i];
	draw_line(map_c, p2, mlx, win);

	return 1;
}

int	color_lines(void *mlx, void *win, t_coord map_c, int i, int *line)
{
	t_coord p2;

	p2.x = map_c.x + 20;
	p2.y = map_c.y + 20 - (line[i + 1] + line[i]);
	draw_line2(map_c, p2, mlx, win);
	return 1;
}

void draw_w(void *mlx, void *win, t_coord coord, int i, int *line)
{
	t_coord p2;

	p2.x = coord.x + 20;
	p2.y = coord.y + 20 - (line[i + 1] - line[i]);
	draw_line2(coord, p2, mlx, win);
}

void	draw_map(t_map *map_list, void *mlx, void *win)
{
	size_t	i;
    int temp_x;
    int temp_y;
	static t_coord	map_coord;
 
	map_coord.x = 200;
	map_coord.y = 100;
	if (map_list->next == NULL){
		return ;
	}
	draw_map(map_list->next, mlx, win);
	temp_x = map_coord.x;
	temp_y = map_coord.y;
	i = 0;
	while (i != map_list->len)
	{
		map_coord.x +=  20;
		if (i > 0)
				map_coord.y += 20 - map_list->line[i] + map_list->line[i + 1];
		else{
				map_coord.y += 20 - map_list->line[i];
		}
		if (map_list->line[i + 1])
			color_lines(mlx, win, map_coord, i, map_list->line);
		if (map_list->next)
			color_lines2(mlx, win, map_coord, i, map_list->line);
		draw_w(mlx, win, map_coord, i, map_list->line);
		if (i >= map_list->len)
			draw_w(mlx, win, map_coord, i, map_list->line);

		i++;	
	}
 	map_coord.x = temp_x - 20;
	map_coord.y = temp_y + 20;
}

void	push(t_map **map, t_map *element)
{
	element->next = *map;
	*map = element;
	element = *map;
}

void parse_map(char *line, int (*f)(const char *), t_map **map)
{
	int 	i;
	t_map	*new_line;
	char	**temp_line;

	i = 0;
	new_line = (t_map *)malloc(sizeof(t_map));
	temp_line = ft_strsplit(line, ' ');
	new_line->line = (int *)malloc(sizeof(int) * ft_fast_strlen(line) + 1);
	new_line->len = 0;
	while (temp_line[i] != NULL)
	{
		new_line->line[i] = f(temp_line[i]);
		new_line->len++;
		new_line->next = NULL;
		i++;
	}
	new_line->line[i] = 0x00;
	push(map, new_line);
}

void	print_map(t_map *map_list, t_env_graph *env)
{
	size_t 	i;

	i = 0;
	if (map_list->next == NULL){
		return ;
	}
	print_map(map_list->next, env);
	while (i != map_list->len)
	{
			printf("%d ", map_list->line[i]);
			i++;
	}
	printf("%zu \n", map_list->len);
}

void get_map(char *file, t_env_graph *env)
{
	int 			fd;
	char 			*line;
	t_map			*map_list;

	env->line_list = NULL;
	env->len_map = 0;
	map_list = malloc(sizeof(t_map));
	map_list->len = 0;
	map_list->next = env->line_list;
	if (map_list == NULL)
	{
		perror("No memory\n");
	}
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		env->len_map++;
		parse_map(line, ft_atoi, &map_list);
	}
	env->line_list = map_list;
}

int main (int ac, char **av)
{
	t_env_graph env;

	if (ac == 2)
	{
		get_map(av[1], &env);
		if (!(env.mlx = mlx_init()))
		{
			ft_putendl(" !! KO !!");
			exit(1);
		}
		if (!(env.win = mlx_new_window(env.mlx, WIN_SX, WIN_SY,"fdf")))
		{
			ft_putendl(" !! KO !!");
			exit(1);
		}
		draw_map(env.line_list, env.mlx, env.win);
		sleep(5);
		mlx_clear_window(env.mlx, env.win);
	}
	else
	{
		perror("Use: [./fdf[ <file>\n");
		exit(0);
	}
	return (0);
}
