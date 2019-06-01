#include "42sh.h"

void	free_vars(t_vars *vars)
{
	if (!vars)
		return ;
	ft_free_ntab(vars->env_vars);
	ft_free_ntab(vars->shell_vars);
}

t_vars	*get_vars(t_vars *new_vars)
{
	static t_vars *vars = NULL;

	if (new_vars)
		vars = new_vars;
	return (vars);
}