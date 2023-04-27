#ifndef DICTIONARY_H
#define DICTIONARY_H

# include "minishell.h"


# define SET 0
# define GET 1
# define GET_ENV 010
# define GET_PATH 0100
# define GET_HOME 01000

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