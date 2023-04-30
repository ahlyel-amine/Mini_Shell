#ifndef DICTIONARY_H
#define DICTIONARY_H

# include "minishell.h"


# define SET		0b0
# define SET_PWD	0b10
# define GET		0b1
# define GET_ENV	0b10
# define GET_PATH	0b100
# define GET_HOME	0b1000
# define GET_PWD	0b10000
# define FREE		0b11111111


# define F_HEREDOC	0b100
# define F_APPEND	0b101
# define F_IN_RED	0b10
# define F_OUT_RED	0b11


enum s_type
{
	EXEC = 1,
	REDIR,
	BUILTIN,
	AND,
	OR,
	PIPE,
	ASSIGNEMENT,
	INVALID
};

enum s_redir_type
{
	HEREDOC = 1,
	IN_REDIR,
	OUT_REDIR,
	APPEND
};

typedef struct s_var
{
	int	quote:1;
	int	dquote:1;
}	t_var;

#endif