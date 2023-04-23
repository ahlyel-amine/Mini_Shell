#ifndef DICTIONARY_H
#define DICTIONARY_H

# include "minishell.h"

# define S_EXP 		"export"
# define S_PWD 		"pwd"
# define S_ECHO		"echo"
# define S_UNSET	"unset"
# define S_ENV 		"env"
# define S_CD		"cd"
# define S_CMDAND 	"&&"
# define S_CMDOR 	"||"
# define S_CMDPIPE	"|"

typedef enum s_token
{
	T_CMD,
	T_BILTN,
	T_WORD,
	T_HEREDOC,
	T_VARIABLE,
	T_OPERATOR,
	T_HERDOC,
	T_REDIRECTION,
	T_PARENTHESIS,
}	t_token;

#endif