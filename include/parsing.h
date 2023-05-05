#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"


void		parse_line(char **line);
char		*read_until_chr(char *line, char c);
void		tokenizer(char **words);
void		read_line(t_list **env_var);
void		complete_line(char **line);
char		*get_prompt_line();
t_cmd		*tokenize_line(char *line);
void		free_line(t_cmd *cmd);
char	*remove_unused_parenthesis(char *line);

/*	tokenizers*/

t_cmd	*get_token_builtins(char *line, int i, int j);
t_cmd	*get_token_cmd(char *line, int j);
t_cmd	*get_token_operator(char *line);
t_cmd	*get_token_order(char *line);
t_cmd	*get_token_operator_pipe(char *line);
t_cmd	*get_token_redir(char *line);
t_cmd	*get_token_variable_assignement(char *line);
t_cmd	*get_token_parenthesis_operator(char *line);

/*helpers*/
char	*quotes(char *line, int i);
void	check_out_of_quotes(char c, t_var *var);
void	set_zero_var(t_var *var);

void	something_wrong(char *error, void *to_free);

/*	tools	*/
char		**ft_split_char(char const *s, char c);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_chrpos(char *line,  char c);
int	skip_spaces_front(char *line);
void	panic_recursive(char *error, void *ptr);
void	pr_custom_err(char *error, void *ptr);


#endif