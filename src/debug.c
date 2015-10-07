#include <fdf.h>

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
		ft_putnbr((int)map_list->line[i]);
		i++;
	}
	ft_putnbr((int)map_list->len);
	ft_putendl("-- ** end line **--");
}

void	print_map2(t_map *map_list)
{
	size_t 	i;

	i = 0;
	if (map_list->next == NULL){
	
		return ;
	}
	print_map2(map_list->next);
	while (i != map_list->len)
	{
		ft_putnbr((int)map_list->line[i]);
		ft_putstr(" ");
		i++;
	}
	ft_putnbr((int)map_list->len);
	ft_putendl("-- ** end line **--");
}