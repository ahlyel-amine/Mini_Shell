#ifndef MINISHELL_H
#define MINISHELL_H

# include "/Users/aahlyel/homebrew/opt/readline/include/readline/readline.h"
# include "/Users/aahlyel/homebrew/opt/readline/include/readline/history.h"
# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include  <stdlib.h>
# include  <fcntl.h>
# include  <string.h>
# include "dictionary.h"

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef struct s_and
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_and;

typedef struct s_or
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_or;

typedef struct s_execcmd
{
	int		type;
	char	**cmd;
}	t_execcmd;

typedef struct s_assignement
{
	int		type;
	char	*key;
	char	*value;
}	t_assignement;

typedef struct s_builtin
{
	int		type;
	char	*builtin;
	char	*cmd;
	int		has_option:1;
}	t_builtin;

typedef struct s_invalid
{
	int		type;
	char	*str;
}	t_invalid;

typedef struct s_redir_content
{
	char	*file_name;
	char	*efile_name;
	int		mode;
	int		fd;
	int		type;
}	t_redir_content;

typedef struct s_redir
{
	int				type;
	t_redir_content	red;
	t_cmd			*cmd;
}	t_redir;

# include "parsing.h"

void	*set__get_option_variables(char	**env, int set__get_option);
t_cmd	*builtin_constructor(char *str, int has_option, char *cmd);
t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content);
t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content);
t_cmd	*assignement_constructor(char *key, char *value);
t_cmd	*pipe_constructor(t_cmd *left, t_cmd *right);
t_cmd	*and_constructor(t_cmd *left, t_cmd *right);
t_cmd	*or_constructor(t_cmd *left, t_cmd *right);
t_cmd	*execcmd_constructor(char **cmds);
t_cmd	*invalid_constructor(char *str);

void	echo(t_cmd *cmd);
#endif