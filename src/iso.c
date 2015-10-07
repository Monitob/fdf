#include <fdf.h>
#include "mlx.h"
#include "mlx_int.h"

static void draw_line2(t_coord p1, t_coord p2, void *mlx, void *win){
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

// static void draw_line(t_coord p1, t_coord p2, void *mlx, void *win){
// 	float	a;
// 	float	b;

// 	a =  (p1.y - p2.y) / (p1.x - p2.x);
// 	b = p1.y - a * p1.x;
// 	while (p1.x != p2.x)
// 	{
// 		mlx_pixel_put(mlx, win, p1.x, p1.y, 0x00ff00);
// 		p1.x += (p1.x > p2.x) ? -1 : 1;
// 		p1.y = a * p1.x + b;
// 	} 
// }

// static int	color_lines2(void *mlx, void *win, t_coord map_c, int i, int *line)
// {
// 	t_coord p2;

// 	p2.x = map_c.x - 20;
// 	p2.y = map_c.y + 20 - line[i] + line[i];
// 	draw_line(map_c, p2, mlx, win);

// 	return 1;
// }

// static int	color_lines(void *mlx, void *win, t_coord map_c, int i, int *line)
// {
// 	t_coord p2;

// 	p2.x = map_c.x + 20;
// 	p2.y = map_c.y + 10 - (line[i + 1] + line[i]);
// 	draw_line2(map_c, p2, mlx, win);
// 	return 1;
// }

static void draw_w(void *mlx, void *win, t_coord coord, int i, int *line)
{
	t_coord p2;

	p2.x = coord.x + 20;
	p2.y = coord.y + 10 - (line[i + 1] - line[i]);
	draw_line2(coord, p2, mlx, win);
}

static void draw_h(void *mlx, void *win, t_coord *coord, int i, t_map *map_list)
{
	coord->x +=  20;
	coord->y += 10 - map_list->line[i] + map_list->line[i + 1];
	printf("[%d]", map_list->line[i]);
	if (map_list->line[i + 1])
	{
		if (map_list->line[i] == 0)
		{
			ft_putstr("is 0\n" );

			draw_w(mlx, win, *coord,i, map_list->line);
		}
		else if (map_list->line[i] > 0)
		{
			ft_putstr("is 1\n" );
//			draw_w(mlx, win, *coord,i, map_list->line);
		}
	}
	printf("\n");
}

void	draw_map(t_map *map_list, void *mlx, void *win)
{
	size_t	i;
    int temp_x;
    int temp_y;
	static t_coord	map_coord;
 
	map_coord.x = 300;
	map_coord.y = 50;
	if (!map_list)
	{
		return ;
	}
	draw_map(map_list->next, mlx, win);
	temp_x = map_coord.x;
	temp_y = map_coord.y;
	i = 0;
	while (i != map_list->len)
	{
		draw_h(mlx, win, &map_coord, i, map_list);
		i++;
	}
	map_coord.x = temp_x - 20;
	map_coord.y = temp_y + 10;
}
