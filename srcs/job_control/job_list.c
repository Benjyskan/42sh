#include "jobs.h"

int		get_last_num(t_job *j)
{
	if (!j)
		return (0);
	while (j->next)
		j = j->next;
	return (j->num);
}

t_job	 *create_job(t_ast *root, int fg, int num)
{
	t_job *j;

	if (!(j = malloc(sizeof(t_job))))
		clean_exit(1, 1);
	ft_bzero(j, sizeof(t_job));
	j->command = copy_job_tokens(root);
	j->fg = fg;
	j->num = num; // care overflow on int ? 
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	return (j);
}

/*
**	Appends the to_add process to the list of processes.
**	Returns the last process appended for faster insertion.
*/

t_job	*append_job(t_job **first_job, t_job *to_add)
{
	t_job	*probe;

	if (!to_add)
		return (*first_job);
	if (!(probe = *first_job))
		*first_job = to_add;
	else
	{
		while (probe->next)
			probe = probe->next;
		probe->next = to_add;
	}
	return (to_add);
}
