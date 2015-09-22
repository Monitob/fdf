
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#ifndef FDF_H
# define FDF_H


#define	WIN_SX		1000
#define	WIN_SY		1000



typedef struct s_map
{
	int *line;
	size_t	len;
	struct s_map *next;
} t_map;

typedef struct s_coord
{
	int x;
	int y;
}t_coord;

typedef struct s_env_graph 
{
	void	*mlx;
	void	*win;
	struct s_map *line_list;
	int		len_map;
} t_env_graph;



#endif 
