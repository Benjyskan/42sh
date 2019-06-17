#include "jobs.h"

static int	mark_process_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		j = g_first_job;
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
						p_>stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED(status))
							ft_dprintf(2, "%d: Terminated by signal %d/\n",
								(int)pid, WTERMSIG(p->status));
					}
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
		ft_dprintf(2, "No child process %d.\n", (int)pid);
		return (-1);
	}
	else if (pid == 0)
		return (-1);
	else
	{
		ft_dprintf(2, SHELL_NAME ": error: waitpid failed\n");
		return (-1);
	}
}

void	update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, &status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}
