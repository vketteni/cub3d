#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
//# include "MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "structs.h"
# include <stdio.h>      // printf
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // write, access, fork, execve, dup2, pipe, etc.
# include <errno.h>      // perror, strerror
# include <stdlib.h>     // getenv
# include <stddef.h>	 // Null
# include <math.h>
# include <string.h>

/* Map Parsing */
int		check_map_cub(char *file);
int		walls_check(t_game *game);
int		map_input_check(t_game *game);
char	*get_from_cub(char *line, const char *direction);
void	which_color(t_game *game);
void	cub_input(t_game *game);
void	open_map(t_game *game, char *file);
void	space_cub(t_game *game, int fd);
void	get_cub(t_game *game, int fd);
void	print_map(t_game *game);
void	free_data(t_game *game);
void	actual_map(t_game *game);
void	free_cub(t_game *game);





# endif
