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


typedef enum allo
{
	infile,
	outfile,
	errorfile,
}	t_alo;

typedef struct s_cmd
{
	char	**cmd;
	int 	infile;
	int		outfile;
	int		errorfile;
}	t_cmd;

typedef struct s_arg
{
	char			*token;
	short			x_token:4;
	// t_cmd			cmd;
	struct s_arg	*next;
}	t_arg;

// cmd word operators redirections 
typedef struct s_tree
{
	char			*data;
	struct s_tree	*prev;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

# include "parsing.h"
// | || && word    {}   cmd herdoc ( < "built-in cmd"  


#endif