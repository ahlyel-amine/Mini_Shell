#ifndef MINISHELL_H
#define MINISHELL_H

# include "/Users/aelbrahm/.brew/opt/readline/include/readline/readline.h"
# include "/Users/aelbrahm/.brew/opt/readline/include/readline/history.h"
# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include  <stdlib.h>
# include  <fcntl.h>
# include  <string.h>
# include <errno.h>
# include "dictionary.h"

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_hold{
	t_list	*lst;
	int		size : 16;
}	t_hold;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

t_cmd	*pipe_constructor(t_cmd *left, t_cmd *right);
void	pipe_destructor(t_cmd *structor);

typedef struct s_and
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_and;

t_cmd	*and_constructor(t_cmd *left, t_cmd *right);
void	and_destructor(t_cmd *structor);

typedef struct s_or
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_or;

t_cmd	*or_constructor(t_cmd *left, t_cmd *right);
void	or_destructor(t_cmd *structor);

typedef struct s_execcmd
{
	int		type;
	char	**cmd;
}	t_execcmd;

t_cmd	*execcmd_constructor(char **cmds);
void	execcmd_destructor(t_cmd *structor);

typedef struct s_assignement
{
	int		type;
	char	*key;
	char	*value;
}	t_assignement;

t_cmd	*assignement_constructor(char *key, char *value);
void	assignement_destructor(t_cmd *structor);

typedef struct s_builtin
{
	int		type;
	char	*builtin;
	char	*cmd;
	int		has_option:1;
}	t_builtin;

t_cmd	*builtin_constructor(char *str, int has_option, char *cmd);
void	builtin_destructor(t_cmd *structor);

typedef struct s_invalid
{
	int		type;
	char	*str;
}	t_invalid;

t_cmd	*invalid_constructor(char *str);
void	invalid_destructor(t_cmd *structor);

typedef struct s_redir_content
{
	int		type;
	char	*file_name;
	char	*efile_name;
	int		mode;
	int		fd;
}	t_redir_content;

typedef struct s_redir
{
	int				type;
	t_redir_content	red;
	t_cmd			*cmd;
}	t_redir;

t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content);
void	redir_destructor(t_cmd *structor);

# include "parsing.h"

void	*set__get_option_variables(t_hold *env, int set__get_option);
////-/__________________________________________________________//
///-/                      VAR_EXPENDER                        //
//-/__________________________________________________________//
char    *nodes_join(t_list *lst);
t_list  *expander(char *var);
char    *replace_str(char *var, char *lst_cnt);
int    replace(t_list **lst, char *var);
int dolr_check(t_list **lst, char *str, int iter);
////-/__________________________________________________________//-|
///-/                           EXEC                           //--|
//-/__________________________________________________________//---|
void	echo(t_cmd *cmd);
void	cd(t_cmd *cmd);
#endif