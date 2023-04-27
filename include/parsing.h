#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"


void		parse_line(char *line);
void		spliter(char *line);
char		**set_splited(char *line, int count_inc, int call_count);
int			quote_handler(char **line, int i);
int			dquote_handler(char **line, int i);
char		**strings_handler(char **line, int *i, int ref, int *set_call_counter);
char		**check_last(char **words);
char		**check_last_pipe(char **words);
void		heredoc_controll();
char		**parser(char **words);
void		read_until_chr(char **line, char c);
void		tokenizer(char **words);
t_arg		*new_arg(char *token, t_token x_token, int ref);

void	read_line(char	**line);
void	complete_line(char **line);
char	*get_prompt_line(char *old_pwd);

/*	tokenizers*/

t_cmd	*get_token_builtins(char *line, int i, int j);
t_cmd	*get_token_cmd(char *line, int j);
t_cmd	*get_token_operator(char *line);
t_cmd	*get_token_order(char *line);
t_cmd	*get_token_operator_pipe(char *line);
t_cmd	*get_token_redir(char *line);
t_cmd	*get_token_variable_assignement(char *line, int j);

/*helpers*/
char	*quotes(char *line, int i);
void	check_out_of_quotes(char c, int *quote, int *dquote);
void	something_wrong(char *error);

/*	tools	*/
char		**ft_split_char(char const *s, char c);
char		**parenthesis_checker(char **words);
int			ft_isprint_nspc(int c);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_chrpos(char *line,  char c);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);
int			ft_strnstrpos(const char *haystack, const char *needle);

#endif