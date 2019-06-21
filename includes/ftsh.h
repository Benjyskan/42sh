#ifndef FTSH_H
# define FTSH_H

# include "structures.h"
# include "libft.h"
# include "libterm.h"
# include <sys/types.h>

# define SHELL_NAME "42sh"

/*
**	t_vars utility functions
*/

t_vars		*get_vars(t_vars *new_vars);
void		free_vars(t_vars *vars);
int			init_vars(t_vars *vars, int argc, char **argv, char **env);
void		reset_copy_vars(t_vars *vars);
void		ft_memdel_ntab(char ***ntab);

/*
**	File descriptors funcs
*/

void		save_reset_stdfd(int mode);

/*
**	String tool
*/

void		print_introduction(void);
int			is_full_of_whitespaces(const char *input);
void		clean_exit(int exitno, int malloc_error);

/*
**	Debug
*/

void		magic_print(char *buf);

#endif
