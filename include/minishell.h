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
# include <limits.h>
#include <dirent.h>
# include "dictionary.h"
// # include "parsing.h"
// # include "execute.h"
#define ENV 0
#define EXP 1
typedef struct s_hold{
	t_list	*lst;
	int		size:16;
}	t_hold;

typedef struct s_arguments{
	char				*str;
	unsigned short		type:4;
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


void	*set__get_option_variables(t_hold *env, int set__get_option);
////-/__________________________________________________________//
///-/                      VAR_EXPENDER                        //
//-/__________________________________________________________//
char    *nodes_join_b(t_arguments *lst);
char    *nodes_join(t_list *lst);
t_list  *expander(char *var);
char    *replace_str(char *var, char *lst_cnt);
int    replace(t_list **lst, char *var);
int dolr_check(t_list **lst, char *str, int iter);
void    expend_line(t_cmd *cmd);
////-/__________________________________________________________//-|
///-/                           EXEC                           //--|
//-/__________________________________________________________//---|


////-/__________________________________________________________//-|
///-/                          TOOLS                           //--|
//-/__________________________________________________________//---|
void	sp_free(char **splt);
char	*app_dup(char *arg);
void	env_exp_print(t_list *sort_lst, int (*print)(const char*, ...));
void	echo(t_cmd *cmd);
int		tt_cd(t_cmd *cmd);
int		tt_unset(t_cmd *cmd);
t_list	*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t));
t_list	*lst_dup(t_list *lst);
int		valid_id(char *var);

void	ft_list_remove(t_list **lst_tmp, char *data, int (*cmp)());
int		tt_export(t_cmd *cmd);

// #endif


// int	tt_cd(t_cmd *cmd);
// // void	cd(t_cmd *cmd);
# include "parsing.h"
# include "execute.h"
void	tilde_expansion(t_arguments *arg);
void	*expand_line(t_arguments *arg);
char    *get_owd(char *env_var);
char    *ft_strndup(const char *s, size_t n);
#endif

//Tilde expansion
// If the input string is empty, return it.

// If the first character of the input string is not a tilde (~), return the input string as is.

// If the first character of the input string is a tilde, look for the first slash (/) character after the tilde.

// If there is no slash character after the tilde, replace the tilde character with the path to the current user's home directory and return the resulting string.

// If there is a slash character after the tilde, extract the username from the input string. The username is the substring between the tilde and the slash character.

// If the username is empty, replace the tilde character with the path to the current user's home directory and append the rest of the input string after the slash character.

// If the username is not empty, look up the home directory path for that user and replace the tilde and username with the home directory path. If the user is not found or does not have a home directory, return an error.

// If there are multiple tilde characters in the input string, repeat steps 3-7 for each tilde character.

// If the input string ends with a tilde character, append the path to the current user's home directory to the input string.

// echo $PWD$OLD
// export $PWD$PA=alo
// unset "$VAR $VAR1 $VAR2" != unset $VAR $VAR1 $VAR2
// [echo "$PWD $VAR"]
// [echo "$PWD $VAR"]
// [1]    52519 segmentation fault  ./minishell;