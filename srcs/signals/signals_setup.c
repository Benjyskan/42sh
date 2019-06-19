#include "input.h"
#include "line_editing.h"
#include "signals.h"
#include "jobs.h"

/*
** Handler function for terminating (aka dangerous) signals
*/

void			sig_handler(int signo)
{
	execute_str(CLEAR_BELOW);
	restore_init_cursor();
	reset_terminal_settings();
	ft_dprintf(STDERR_FILENO, "Interrupted by signal: %d\n", signo);
	exit(signo);
}

/*
** Setting up signal functions.
** KILL and STOP are not handled, and WILL leave you with a messy terminal
** Terminating (aka dangerous) signals reset the terminal, and then exit.
** All non-terminating signals are left untouched, except WINCH and CONT
** INT signal does NOT exit the program.
*/

/*void	sigtstp_handler(int signo)
{
	(void)signo;
	ft_dprintf(2, "hey\n");
	put_last_job_in_background();
}*/

void		signals_setup(void)
{
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGCONT, sigcont_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGILL, sig_handler);
	signal(SIGTRAP, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGEMT, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGBUS, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGSYS, sig_handler);
	signal(SIGALRM, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGXCPU, sig_handler);
	signal(SIGXFSZ, sig_handler);
	signal(SIGVTALRM, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGPROF, sig_handler);
}

void	reset_signals(void)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		signal(i, SIG_DFL);
		i++;
	}
}
