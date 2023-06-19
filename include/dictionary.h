#ifndef DICTIONARY_H
#define DICTIONARY_H
# include <sys/stat.h>
# include "minishell.h"

#ifndef SHELL_NAME
# define SHELL_NAME				"minishell: "
#endif
#ifndef FORK_ERR
# define FORK_ERR				"minishell: fork: "
#endif
#ifndef EXIT_SHELL
# define EXIT_SHELL				"minishell: exit"
#endif
#ifndef INVALID_INPT
# define INVALID_INPT			"minishell: the input fd is not the default"
#endif
#ifndef HERDOC_FILE
# define HERDOC_FILE			"/tmp/.heredoc_"
#endif
#ifndef ERR_TOKEN
# define ERR_TOKEN				"minishell: syntax error near unexpected token : "
#endif
#ifndef ERR_EXVE
# define ERR_EXVE				"minishell: execve: faillure"
#endif
#ifndef ERR_CMD
# define ERR_CMD				"minishell: command not found: "
#endif
#ifndef ERR_AMBGIS
# define ERR_AMBGIS				"minishell: ambiguous redirect\n"
#endif
#ifndef ERR_FILE
# define ERR_FILE				"minishell: no such file or directory: "
#endif
#ifndef ERR_SNTX
# define ERR_SNTX				"minishell: syntax error near unexpected token : "
#endif
#ifndef ERR_O_SNTX
# define ERR_O_SNTX				"minishell: syntax error near unexpected token\n"
#endif
#ifndef ERR_AND
# define ERR_AND				"minishell: syntax error near unexpected token `&&'"
#endif
#ifndef ERR_1AND
# define ERR_1AND				"minishell: syntax error near unexpected token `&'\n"
#endif
#ifndef ERR_OR
# define ERR_OR					"minishell: syntax error near unexpected token `||'"
#endif
#ifndef ERR_PIPE
# define ERR_PIPE				"minishell: syntax error near unexpected token `|'"
#endif
#ifndef ERR_UNCLSDP
# define ERR_UNCLSDP			"minishell: syntax error near unexpected token `('\n"
#endif
#ifndef ERR_ClSD_PARNETHISE
# define ERR_ClSD_PARNETHISE	"minishell: syntax error near unexpected token `)'\n"
#endif
#ifndef ERR_UNXPTD_EOF
# define ERR_UNXPTD_EOF			"unexpected EOF while looking for matching \"\'\n"
#endif
#ifndef ERR_FOUND_EOF
# define ERR_FOUND_EOF			"minishell: syntax error: unexpected end of file\n"
#endif
#ifndef READLINE
# define READLINE				"\033[1;32mminishell\033[34m$ \033[0m"
#endif
#ifndef HERDOC
# define HERDOC					"\033[37mHeredoc\033[34m> \033[0m"
#endif
#ifndef CMDAND
# define CMDAND					"\033[37mcmdand\033[34m> \033[0m"
#endif
#ifndef CMDOR
# define CMDOR					"\033[37mcmdor\033[34m> \033[0m"
#endif
#ifndef CMDPIPE
# define CMDPIPE				"\033[37mpipe\033[34m> \033[0m"
#endif
#ifndef CMPLTQUOTE
# define CMPLTQUOTE				"\033[37mquote\033[34m> \033[0m"
#endif
#ifndef CMPLTDQUOTE
# define CMPLTDQUOTE			"\033[37mdquote\033[34m> \033[0m"
#endif
#ifndef CWD_ERR
# define CWD_ERR				"cd: error retrieving current directory: getcwd: cannot access parent directories: "
#endif
#ifndef DR_ERR
# define DR_ERR					": No such file or directory"
#endif

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

typedef enum e_set_get
{
	SET			= 0b0,
	SET_PWD		= 0b10,
	GET			= 0b1,
	GET_ENV 	= 0b10,
	GET_PATH 	= 0b100,
	GET_HOME	= 0b1000,
	GET_PWD		= 0b10000,
	FREE		= 0b11111111,
}	enum_set_get;

typedef enum e_token
{
	E_SUBSH 	= 0b1,
	E_DQUOTE 	= 0b10,
	E_QUOTE 	= 0b100,
	E_AND 		= 0b1000,
	E_OR 		= 0b10000,
	E_PIPE 		= 0b100000,
	E_HEREDOC 	= 0b1000000,
	E_OUTRED	= 0b10000000,
	E_INRED		= 0b100000000,
	E_APPEND	= 0b1000000000,
	E_STR		= 0b10000000000,
	E_SPACE 	= 0b100000000000,
	E_FD_NAME 	= 0b1000000000000,
	E_EMPTY		= 0b10000000000000,
}	enum_token;

#endif