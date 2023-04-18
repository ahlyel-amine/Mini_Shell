#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"


void	parsing_controll(t_tree **tree, char *line);
char	**spliter(char *line, int ref);
char	**set_splited(char *line, int j, int count_inc, int call_count);
char	**quote_handler(char **line, int *i, int ref, int *set_call_counter);
char	**dquote_handler(char **line, int *i, int ref, int *set_call_counter);
char	**strings_handler(char **line, int *i, int ref, int *set_call_counter);

/*	tools	*/


int			ft_isprint_nspc(int c);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_chrpos(char *line,  char c);



#endif