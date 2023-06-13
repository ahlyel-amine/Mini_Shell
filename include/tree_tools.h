#ifndef TREE_TOOLS_H
#define TREE_TOOLS_H

# include "minishell.h"

typedef struct s_arguments{
	char				*str;
	unsigned short		q:1;
	unsigned short		type:6;
	struct s_arguments	*down;
	struct s_arguments	*next;
}	t_arguments;

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
	int			type;
	t_arguments	*cmd;
	t_arguments	*options;
}	t_execcmd;

t_cmd	*execcmd_constructor(t_arguments *cmds, t_arguments *options);
void	execcmd_destructor(t_cmd *structor);

typedef struct s_builtin
{
	int				type;
	char			*builtin;
	t_arguments		*arguments;
	unsigned short	has_option:1;
}	t_builtin;

t_cmd	*builtin_constructor(char *str, unsigned short has_option, t_arguments *arguments);
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
	int			type;
	t_arguments	*file_name;
	char		*delimiter;
	int			mode;
	int			fd;
}	t_redir_content;

typedef struct s_redir
{
	int				type;
	t_redir_content	red;
	t_cmd			*cmd;
}	t_redir;

t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content);
void	redir_destructor(t_cmd *structor);

#endif
