#ifndef MINISHELL_H
#define MINISHELL_H

// # include "/Users/aelbrahm/.brew/opt/readline/include/readline/readline.h"
// # include "/Users/aelbrahm/.brew/opt/readline/include/readline/history.h"
# include "/Users/aahlyel/homebrew/opt/readline/include/readline/readline.h"
# include "/Users/aahlyel/homebrew/opt/readline/include/readline/history.h"
# include "../lib/libft/include/libft.h"
# include "dictionary.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>

typedef struct s_lsttoken t_lsttoken;

typedef struct s_arguments{
	char				*str;
	unsigned short		q:1;
	unsigned short		type:6;
	struct s_arguments	*down;
	struct s_arguments	*next;
}	t_arguments;

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

typedef struct s_hold{
	t_list	*lst;
	int		size:16;
}	t_hold;

typedef struct s_globe
{
	char	**backup;
	t_hold	*s_env;
	int		exit_val;
	int		in_cmd;
	int		out;
	int		Ctrl_c;
	int		is_sig;
	int		is_pipe;
}	t_globe;

t_globe	e_glb;

void		*set__get_option_variables(void *env, int set__get_option);
void		sp_free(char **splt);
char		*app_dup(char *arg);
void		env_exp_print(t_list *sort_lst, int (*print)(const char*, ...));
t_list		*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t));
t_list		*lst_dup(t_list *lst);
void		controll_line(char **line);
void		read_line(void);
void		complete_line(char **line, int *brea);
void		wild_cards(t_arguments **args);

# include "parsing.h"
# include "parsing_tools.h"
# include "executer.h"
# include "builtin.h"
# include "tokenizer.h"

#endif