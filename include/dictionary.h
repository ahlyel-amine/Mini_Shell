#ifndef DICTIONARY_H
#define DICTIONARY_H

# include "minishell.h"


# define SET		00
# define SET_PWD	010
# define GET		01
# define GET_ENV	010
# define GET_PATH	0100
# define GET_HOME	01000
# define GET_PWD	010000
# define FREE		011111111

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

#endif