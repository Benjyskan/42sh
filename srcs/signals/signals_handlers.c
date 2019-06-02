#include "input.h"
#include "line_editing.h"
#include "signals.h"
#include "history.h"

/*
** Handler function for terminating (aka dangerous) signals
*/

 void		sig_handler(int signo)
{
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	ft_dprintf(STDERR, "Interrupted by signal: %d\n", signo);
	exit(signo);
}

/*
**	SIGINT
**	Puts a \x03 at the beginning of txt.
**	Sets the last cmd_value to 1 (error)
**	Prints a newline on terminal
*/

void			sigint_handler(int signo)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	(void)signo;
	st_cmd = get_st_cmd(NULL);
	*st_cmd->st_txt->txt = '\x03';
	go_to_end(st_cmd);
	reposition_cursor(st_cmd);
	vars = get_vars(NULL);
	vars->cmd_value = 1;
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	write(0, "\n", 1);
	execute_str(CLEAR_BELOW);
}

/*
**	SIGWINCH
**	Simply writes back the st_cmd on screen
*/

void		sigwinch_handler(int signo)
{
	t_st_cmd	*st_cmd;

	(void)signo;
	st_cmd = get_st_cmd(NULL);
	update_window_struct(st_cmd->window);
	go_back_to_start(st_cmd);
	st_cmd = get_first_st_cmd(st_cmd);
	write_from_start(st_cmd);
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
	signal(SIGWINCH, sigwinch_handler);
}

/*
**	SIGCONT
**	Setups terminal settings, and writes back the st cmd.
*/

void		sigcont_handler(int signo)
{
	t_st_cmd	*st_cmd;

	(void)signo;
	if (setup_terminal_settings() == 0)
		clean_exit(1);
	st_cmd = get_st_cmd(NULL);
	st_cmd = get_first_st_cmd(st_cmd);
	write_from_start(st_cmd);
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
}

/*
**	SIGTSTP
**	Clears the screen and resets terminal settings. Then resets the default
**	behavior for signal and simulates the signal with ioctl
*/

void			sigtstp_handler(int signo)
{
	(void)signo;
	execute_str(CLEAR_BELOW);
	reset_terminal_settings();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN, TIOCSTI, "\x1a"); // non-interactive ?
}
