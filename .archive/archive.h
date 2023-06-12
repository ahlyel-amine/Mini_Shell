#ifndef ARCHIVE_H
#define ARCHIVE_H

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


typedef struct s_arg
{
	char			*token;
	short			x_token:4;
	// t_cmd			cmd;
	struct s_arg	*next;
}	t_arg;

int			count_arguments(char *line);
char		**select_arguments(char *line, int count);
char		*get_delimiter(char *word, int j);
void		write_herdoc(char *delemiter);
void		check_for_heredoc(t_arg *arg);
void		heredoc_controll();
char		**check_last_pipe(char **words);
char		**check_last(char **words);
void		count_parenthesis(char **words, int *open_prnths, int *close_prnths);
char		**parenthesis_checker(char **words);
int			ft_isprint_nspc(int c);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);
int			ft_strnstrpos(const char *haystack, const char *needle);
char		**quote_handler(char **line, int *i, int ref, int *set_call_counter);
char		**dquote_handler(char **line, int *i, int ref, int *set_call_counter);
char		**strings_handler(char **line, int *i, int ref, int *set_call_counter);
char		**alloc_for_words(int words_nbr);
char		**set_splited(char *line, int count_inc, int call_count);
char		**spliter(char *line, int ref);
t_arg		*new_arg(char *token, t_token x_token, int ref);
char		*read_until_chr(char *line, char c);
char		*get_variables(char *line, int ref);
int			dquote_handler(char **line, int i);
int 		dquote_handler(char **line, int i);
int			nonquote_handler(char *line, int i);
void		spliter(char *line);
int			check_operator_call(t_arg *arg, char *word);
int			check_biltn_call(t_arg *arg, char *word);
void		tokenizer(char **words);
char		**split_to_3(char *word, char *separater, int befor_sep);
char		**split_to_2(char *word, char *separater, int befor_sep);
char		**separate_word(char *word, char *separater);
char		**check_for_args(char	*word);
char		**replace_pointer(char **words, char **new_words, int i);
char		**parser(char **words);

#endif