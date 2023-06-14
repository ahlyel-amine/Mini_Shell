#ifndef DICTIONARY_H
#define DICTIONARY_H
# include <sys/stat.h>
# include "minishell.h"


# define SET		0b0
# define SET_PWD	0b10
# define GET		0b1
# define GET_ENV	0b10
# define GET_PATH	0b100
# define GET_HOME	0b1000
# define GET_PWD	0b10000
# define FREE		0b11111111

#define ENV 0
#define EXP 1

# define F_HEREDOC	0b100
# define F_APPEND	0b101
# define F_IN_RED	0b10
# define F_OUT_RED	0b11

# define SHELL_NAME				"minishell: "
# define HERDOC_FILE			"/tmp/.heredoc_"
# define ERR_TOKEN				"minishell: syntax error near unexpected token : "
# define ERR_EXVE				"minishell: execve: faillure"
# define ERR_CMD				"minishell: command not found: "
# define ERR_AMBGIS				"minishell: ambiguous redirect\n"
# define ERR_FILE				"minishell: no such file or directory: "
# define ERR_SNTX				"minishell: syntax error near unexpected token : "
# define ERR_O_SNTX				"minishell: syntax error near unexpected token\n"
# define ERR_AND				"minishell: syntax error near unexpected token `&&'"
# define ERR_1AND				"minishell: syntax error near unexpected token `&'\n"
# define ERR_OR					"minishell: syntax error near unexpected token `||'"
# define ERR_PIPE				"minishell: syntax error near unexpected token `|'"
# define ERR_UNCLSDP			"minishell: syntax error near unexpected token `('\n"
# define ERR_ClSD_PARNETHISE	"minishell: syntax error near unexpected token `)'\n"
# define ERR_UNXPTD_EOF			"unexpected EOF while looking for matching \"\'\n"
# define ERR_FOUND_EOF			"minishell: syntax error: unexpected end of file\n"
# define READLINE				"\033[1;32mminishell\033[34m$ \033[0m"
# define HERDOC					"\033[37mHeredoc\033[34m> \033[0m"
# define CMDAND					"\033[37mcmdand\033[34m> \033[0m"
# define CMDOR					"\033[37mcmdor\033[34m> \033[0m"
# define CMDPIPE				"\033[37mpipe\033[34m> \033[0m"
# define CMPLTQUOTE				"\033[37mquote\033[34m> \033[0m"
# define CMPLTDQUOTE			"\033[37mdquote\033[34m> \033[0m"

typedef struct s_two_ptr
{
	int	*i;
	int	*k;
}	t_2ptr_int;

enum s_type
{
	EXEC = 1,
	REDIR,
	BUILTIN,
	AND,
	OR,
	PIPE,
	ASSIGNEMENT,
	SUBSH,
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
	unsigned int	quote:1;
	unsigned int	dquote:1;
}	t_var;


typedef enum s_arguments_type
{
	QUOTE 		= 0b1,
	IS_STR 		= 0b10,
	IS_VARIABLE = 0b100,
	DQUOTE 		= 0b1000,
	IS_SEPARTOR = 0b10000,
	IS_FILE		= 0b100000
} t_arguments_type;

#endif