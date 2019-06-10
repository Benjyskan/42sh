#ifndef HEREDOC_H
# define HEREDOC_H

# include "ftsh.h"
# include "lexer.h"

# define HEREDOC_PROMPT "heredoc> "
# define HEREDOC_FILENAME "/tmp/.tmp_heredoc"
# define MAX_INT_LEN 10
# define UINT_MAX 4294967295
# define ERR_PARSE_EOF 2

char	*eof_join(char *eof, t_token *token);
int		parse_heredoc(t_token *token_head, t_vars *vars);
char	*get_doc(char *eof, unsigned char is_eof_quoted, t_vars *vars);
char	*write_heredoc_in_file(char **txt);
char	*concatenate_heredoc_txt(t_st_cmd *st_cmd, t_st_cmd *start);
char	*free_get_doc(char *txt, char *eof);
#endif
