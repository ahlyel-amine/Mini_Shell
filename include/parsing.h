#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"
void	set_zero_var(t_var *var);


void		controll_line(char **line);
char		*read_until_chr(char *line, char c);
void		tokenizer(char **words);
void		read_line();
t_cmd		*parse_line(char *line);
void		complete_line(char **line);
char		*get_prompt_line();
void		free_line(t_cmd *cmd);
char		*remove_unused_parenthesis(char *line);

/*	tokenizers*/

t_cmd	*get_token_builtins(char *line, int j);
t_cmd	*get_token_cmd(char *line, int j);
t_cmd	*get_token_and(char *line);
t_cmd	*executable_parser(char *line);
t_cmd	*get_token_operator_pipe(char *line);
t_cmd	*redirections_parser(char *line);
t_cmd	*get_token_variable_assignement(char *line);
t_cmd	*and_parser(char *line);

/*helpers*/
char	*skip_quotes(char *line, int *i, int j, int is_word);
void	check_out_of_quotes(char c, t_var *var);
void	expand_dollar(char *line, int *i, int *k, char **tmp);
int		check_for_syntax(char **line, int i); // in redirect token file and used in parenthises operators token file
 int	fill_redir_content(char *line, int i, t_redir_content *red, int ref); // in redirect token file and used in parenthises operators token file
t_arguments	*get_argument(char *line, int *j, int i, int is_word);
size_t ft_double_strlen(char **str);

void	something_wrong(char *error, void *to_free);
t_arguments	*arguments_constructor(t_arguments *arguments, char *str, unsigned short type);
t_arguments	*ft_split_str_to_args(char *str, int is_dquote);

/*	tools	*/
char		**ft_split_char(char const *s, char c);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_chrpos(char *line,  char c);
int	skip_spaces_front(char *line);
void	panic_recursive(char *error, char **ptr);
void	pr_custom_err(char *error, void *ptr, char *custom);

// void	*wild_cards(t_arguments *args, char *word);
int	ft_isvariable(char c);
void	var_expand(t_arguments *arg);
/*			for debugging			*/
void	print_arguments(t_arguments *args);
void	print_cmd(t_cmd *cmd);
void	tokenize_variables(t_arguments **arguments);
int	close_parenthise(char *line);
t_cmd	*call_pipe(char **line, int i);
t_cmd	*pipe_parser(char *line);
t_cmd	*or_parser(char *line);
t_cmd	*redirections_parser_has_parenthesis(char *line);
t_cmd	*check_for_redirections(char *line, int i);
void	replace_arg(t_arguments **head, t_arguments **old, t_arguments *new);
void	arguments_add_back(t_arguments **head, t_arguments *new);
void	arguments_destructor(t_arguments **arguments);
int	tt_pwd();




char	*args_to_str(t_arguments *args);
char	**args_to_dblstr(t_arguments *args);
char	**args_to_cmd_dstr(t_arguments *args, char *cmd);
void	args_move_next_down(t_arguments **args, t_arguments **prev);
void	args_move_down(t_arguments **args, t_arguments **prev);
void	wild_cards(t_arguments **args);

// void	args_move_down(t_arguments **args);
// t_arguments	*args_move_one_down(t_arguments *args, t_arguments *prev);

#endif