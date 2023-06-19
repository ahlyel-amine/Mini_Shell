#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_2ptr_t_lsttoken
{
	t_lsttoken  *front;
	t_lsttoken  *back;
}   t_2ptr_t_lsttoken;

int				cmd_sig_check(char *path, int status);
int				builtin_executer(t_arguments *args, char *cmd, int outfile, int echo_has_option);
char			**child_vars(void);
int				redirection(t_lsttoken *front, t_lsttoken *back, t_components comp);
int				pipe_(t_lsttoken *front, t_lsttoken *back, t_components comp);
int				operator(t_lsttoken *front, t_lsttoken *back, t_components comp);
t_arguments		*get_cmd(t_lsttoken *front, t_lsttoken *back);
void			subsh_call(t_lsttoken *head, t_components comp);
void			pipe_call(t_2ptr_t_lsttoken a, t_lsttoken *head, t_lsttoken *prev, t_components comp);
size_t			get_lenght(t_lsttoken *front, t_lsttoken *back);
char			*get_line(t_lsttoken *front, t_lsttoken *back, size_t len);
int				is_builtin(char *word);
char			*get_path(char *cmd);
int				cmd_executers(char *path, char **cmd, t_components comp);
char			*get_command_name(t_lsttoken **front, t_lsttoken *back);
t_components	get_red(t_lsttoken *redir, t_components comp);
int				pipe_left(t_lsttoken *head, t_lsttoken *back);

#endif