#include "ftsh.h"
#include "builtins.h"
#include "auto_completion.h"

/*
**	Parses FC flags, while preventing bad flag association.
**	Returns (1) if an error occurs.
**	Else, returns (i), the index of the first operand.
*/

static int		fc_parse_flags(t_st_fc *st_fc, char **argv)
{
	int			i;
	int			j;
	int			k;
	int			is_val;

	i = 0;
	while (argv[++i] && argv[i][0] == '-' && ft_strncmp(argv[i], "--", 3))
	{
		j = 0;
		k = -1;
		while (argv[i][++j])
		{
			if (!is_valid_option(argv[i][j]))
				return (error_fc(argv[i], j, invalid_option, st_fc));//return error directement
			if (((is_val = is_valid_mix(st_fc->flag, argv[i][j]))) == 1)
				st_fc->flag[++k] = argv[i][j];
			else if (is_val == -1)
				return (error_fc(argv[i], j, invalid_mix, st_fc));
		}
	}
	if (!ft_strcmp(argv[i], "--"))
		i++;
	return (i);
}

static int		fc_parse_operands(t_st_fc *st_fc, char **argv, int i)
{
	int			i_editor;

	if (ft_strchr(st_fc->flag, 'e'))
	{
		if ((i_editor = (parse_editor_fc(argv, i))) == -1)
			return (-1);
		if (!(st_fc->editor = ft_strtrim(argv[i_editor])))
			clean_exit(1, 1);
		get_first_and_last(st_fc, argv, i_editor + 1);
	}
	else if (st_fc->flag[0] == 's')
	{

		return (parse_case_s_fc(st_fc, argv, i));
	}
	else
		get_first_and_last(st_fc, argv, i);
	return (0);
}

static int	find_index_fc(t_hist_list *histo, char *to_find)
{
	int			i;
	int			nb;
	int			len;

	i = 0;
	if (histo)
	{
		if (ft_isdigit(to_find[0]) || to_find[0] == '-')
		{
			if (to_find[0] == '-')
			{
				i = 0;
				while (to_find[++i] && ft_isdigit(to_find[i]))
					;
				if (to_find[i])
					return (error_fc(to_find, i, invalid_option, NULL));//invalid option -> considere comme une opton
			}
			nb = ft_atoi(to_find);
			if (nb < 0 && histo->len + nb >= 0)
				nb += histo->len;
			else if (histo->len + nb < 0)
				nb = 0;
			return (nb);
		}
		i = histo->len;
		len = ft_strlen(to_find);
		while (hist->prev && i-- > 0)// a checker 
		{
			if (!ft_strncmp(to_find, hist->txt, len))
				break ;
			hist = hist->prev;
		}
	}
	return (i);
}

static int		fc_parse_index(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	if (st->fc[0] == 's')
	{
		if (!st_fc->first)
			st_fc->i_first = 99; //Hist_len - 1, last cm
		else
			st_fc->i_first = find_index_fc(st_cmd->hist_lst, st_fc->first);
	}
	else
	{
		if (st_fc->first)
			st_fc->i_first = find_index_fc(st_cmd->hist_lst, st_fc->first);
		else
		{
			if (ft_strchr(st_fc->flag, 'l'))
			{
				if (st_cmd->hist_lst->len > 15)
					st_fc->i_first = st_cmd->hist_lst->len - 15;
				else
					st_fc->i_first = 0;
			}
			else
				st_fc->i_last = st_cmd->histo_lst->len - 1;
		}
		if (st_fc->last)
			st_fc->i_last = find_index_fc(st_cmd->hist_lst, st_fc->last);
		else if (ft_strchr(st_fc->flag, ft_strchr('l')))
			st_fc->i_last = st_cmd->hist_lst->len - 1;
		else
			st_fc->i_last = st_fc->i_first;

	}
}

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			start_operand;

	i = 5;
	if (!isatty(TERM_FD))
		return (1)
	while (--i > -1)
		(*st_fc).flag[i] = '.';
	if ((start_operand = fc_parse_flags(st_fc, argv)) == -1)
		return (1);
	if ((fc_parse_operands(st_fc, argv, start_operand)) == -1)
		return (1);
	fc_parse_index(st_cmd, st_fc);
	/*
	ft_dprintf(2, "%s\n%s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "%s\n%s\n", st_fc->old_ptrn, st_fc->new_ptrn);
	ft_dprintf(2, "%s\n", st_fc->editor);
	*/

	return (0);
}
