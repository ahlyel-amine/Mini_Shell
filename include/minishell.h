
#ifndef MINISHELL_H
#define MINISHELL_H

# include "/Users/aelbrahm/.brew/opt/readline/include/readline/readline.h"
# include "/Users/aelbrahm/.brew/opt/readline/include/readline/history.h"
// # include "/Users/aahlyel/homebrew/opt/readline/include/readline/readline.h"
// # include "/Users/aahlyel/homebrew/opt/readline/include/readline/history.h"
# include "../lib/libft/include/libft.h"
# include "dictionary.h"
# include "tree_tools.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <limits.h>
# include <dirent.h>

typedef struct s_lsttoken t_lsttoken;

typedef struct s_token
{
	int			type;
	char		*line;
	int			start;
	int			len;
	t_lsttoken	*down;
}	t_token;

typedef struct s_components
{
	int	infile;
	int	outfile;
	unsigned int is_pipe:1;
	int	*fd;
}	t_components;

struct s_lsttoken
{
	t_token				t_;
	struct s_lsttoken	*next;
};




void	print_tokens(t_lsttoken *head);

int	glo_exit;
int	in_cmd;
int	out;
int	Ctrl_c;
int	is_sig;
int	is_pipe;

typedef struct s_hold{
	t_list	*lst;
	int		size:16;
}	t_hold;

typedef struct s_globe
{
	char	**backup;
	t_hold	*s_env;
}	t_globe;

t_globe	e_globe;

void	*set__get_option_variables(void *env, int set__get_option);
////-/__________________________________________________________//
///-/                      VAR_EXPENDER                        //
//-/__________________________________________________________//
char    *nodes_join_b(t_arguments *lst);
char    *nodes_join(t_list *lst);
t_list  *expander(char *var);
char    *replace_str(char *var, char *lst_cnt);
int		replace(t_list **lst, char *var);
int		dolr_check(t_list **lst, char *str, int iter);
void    expend_line(t_cmd *cmd);

////-/__________________________________________________________//-|
///-/                          TOOLS                           //--|
//-/__________________________________________________________//---|

void	sp_free(char **splt);
char	*app_dup(char *arg);
void	env_exp_print(t_list *sort_lst, int (*print)(const char*, ...));

t_list	*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t));
t_list	*lst_dup(t_list *lst);
int		valid_id(char *var);

void	ft_list_remove(t_list **lst_tmp, char *data, int (*cmp)());

void		var_expand(t_arguments *arg);
int			tt_pwd(void);


/*			dont touch this			*/
void		controll_line(char **line);
void		read_line(void);
void		complete_line(char **line, int *brea);
void		free_line(t_cmd *cmd);
void		wild_cards(t_arguments **args);
# include "parsing.h"
# include "parsing_tools.h"
# include "executer.h"
# include "builtin.h"
# include "execute.h"
# include "tokenizer.h"
/*									*/

// void	tilde_expansion(t_arguments *arg);
// char	*tilde_expansion(char *arg, unsigned short type);
void	expand_line(t_arguments *arg);
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