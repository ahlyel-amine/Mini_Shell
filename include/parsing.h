#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"


void		parsing_controll(char *line);
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
t_arg	*new_arg(char *token, t_token x_token, int ref);
void	*env_variables(char	**env, int ref);

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