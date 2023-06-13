#ifndef PARSINGH_H
# define PARSINGH_H

# include "minishell.h"

int     check_parsing(t_cmd *cmd);
t_cmd	*parse_line(char *line);
t_cmd	*and_parser(char *line);
t_cmd	*or_parser(char *line);
t_cmd	*pipe_parser(char *line);
t_cmd	*call_pipe(char **line, int i);
t_cmd	*redirections_parser_has_parenthesis(char *line);
t_cmd	*check_redirect_append(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_herdoc_after(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_outred(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_inred_after(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_herdoc(char **line, int i, int *quit);
void	check_redirect_inred(char **line, int i, int *quit);
t_cmd	*redirections_parser(char *line);
t_cmd	*executable_parser(char *line);
t_cmd	*get_token_builtins(char *line, int j);
t_cmd	*get_token_cmd(char *line, int j);
char	*remove_unused_parenthesis(char *line);

#endif