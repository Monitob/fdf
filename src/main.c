#include <fdf.h>
#include "mlx.h"
#include "mlx_int.h"
#include <stdio.h>
#include <fcntl.h>

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
	new_line->line = (int *)malloc(sizeof(int) * ft_fast_strlen(line) + 2);
	new_line->len = 0;
	while (temp_line[i] != NULL)
	{
		new_line->line[i] = f(temp_line[i]);
		new_line->len++;
		new_line->next = NULL;
		i++;
	}
	new_line->len++;
	new_line->line[i] = f(temp_line[i - 1]);
	new_line->line[i + 1] = 0x00;
	push(map, new_line);
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
	env->len_map++;
	parse_map(line, ft_atoi, &map_list);
	close(fd);
	env->line_list = map_list;
}

int main (int ac, char **av)
{
	t_env_graph env;

	if (ac == 2)
	{
		get_map(av[1], &env);
		start_mlx(&env);
	}
	else
	{
		perror("Use: [./fdf[ <file>\n");
	}
	return (0);
}
