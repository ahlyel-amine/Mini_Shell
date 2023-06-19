#ifndef TREE_TOOLS_H
#define TREE_TOOLS_H

# include "minishell.h"
# include "stdbool.h"

typedef struct s_arguments{
	char				*str;
	unsigned short		q:1;
	unsigned short		type:6;
	struct s_arguments	*down;
	struct s_arguments	*next;
}	t_arguments;


#endif
