#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
int	close_quote(t_arguments **arguments, char *line, int i);
int	close_dquote(t_arguments **arguments, char *line, int i);
void	merge_arguments(t_arguments **arguments, int is_dquote);

void		controll_line(char **line);
void		tokenizer(char **words);
void		read_line(void);
t_cmd		*parse_line(char *line);
void		complete_line(char **line, int *brea);
char		*get_prompt_line(void);
void		free_line(t_cmd *cmd);
char		*remove_unused_parenthesis(char *line);

/*	tokenizers*/

t_cmd		*get_token_builtins(char *line, int j);
t_cmd		*get_token_cmd(char *line, int j);
t_cmd		*get_token_and(char *line);
t_cmd		*executable_parser(char *line);
t_cmd		*get_token_operator_pipe(char *line);
t_cmd		*redirections_parser(char *line);
t_cmd		*get_token_variable_assignement(char *line);
t_cmd		*and_parser(char *line);

/*helpers*/
char		*skip_quotes(char *line, int *i, int j, int is_word);
void		check_out_of_quotes(char c, t_var *var);
void		expand_dollar(char *line, int *i, int *k, char **tmp);
int	check_for_syntax(char **line, int i);                                
		// in redirect token file and used in parenthises operators token file
int	fill_redir_content(char *line, int i, t_redir_content *red, int ref);
		// in redirect token file and used in parenthises operators token file
t_arguments	*get_argument(char *line, int i);
size_t		ft_double_strlen(char **str);

void		something_wrong(char *error, void *to_free);
t_arguments	*arguments_constructor(t_arguments *arguments, char *str,
				unsigned short type, unsigned short q);
t_arguments	*ft_split_str_to_args(char *str, int is_dquote);

/*	tools	*/
char		**ft_split_char(char const *s, char c);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_chrpos(char *line, char c);
int			skip_spaces_front(char *line);
void		panic_recursive(char *error, char **ptr);
void		pr_custom_err(char *error, void *ptr, char *custom);

// void	*wild_cards(t_arguments *args, char *word);
int			ft_isvariable(char c);
void		var_expand(t_arguments *arg);
/*			for debugging			*/
void		print_arguments(t_arguments *args, char *ref);
void		print_cmd(t_cmd *cmd);
void		tokenize_variables(t_arguments **arguments);
int			close_parenthise(char *line);
t_cmd		*call_pipe(char **line, int i);
t_cmd		*pipe_parser(char *line);
t_cmd		*or_parser(char *line);
t_cmd		*redirections_parser_has_parenthesis(char *line);
t_cmd		*check_for_redirections(char *line, int i);
void		replace_arg(t_arguments **head, t_arguments **old,
				t_arguments *new);
void		arguments_add_back(t_arguments **head, t_arguments *new);
void		arguments_destructor(t_arguments **arguments);
int			tt_pwd(void);

char		*args_to_str(t_arguments *args);
char		**args_to_dblstr(t_arguments *args);
char		**args_to_cmd_dstr(t_arguments *args, char *cmd);
void		args_move_next_down(t_arguments **args, t_arguments **prev);
void		args_move_down(t_arguments **args, t_arguments **prev);
void		wild_cards(t_arguments **args);
void		args_join(t_arguments **args);
void		transform_args(t_arguments **args);
t_cmd	*check_redirect_herdoc(char **line, int i, int *quit);
void	check_redirect_inred(char **line, int i, int *quit);
t_cmd	*check_redirect_append(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_herdoc_after(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_outred(char **line, int i, t_var var, int *quit);
t_cmd	*check_redirect_inred_after(char **line, int i, t_var var, int *quit);

int	get_name(char *line, t_redir_content *red, int type);
t_arguments	*get_names(char *line, int *i);
char	*skip_quote_heredoc_delimiter(char *line, int *j, int i, int *q);
size_t	args_len(t_arguments *args);
size_t	args_strslen(t_arguments *args);
void	down_to_str(t_arguments *args, char **str, size_t *len);
t_arguments	*still_args(char *str, int *j, int *i, t_arguments *args);
void	replace_arg_first_element(t_arguments **head, \
t_arguments **old, t_arguments *new, \
t_arguments *replace_old);

// void	args_move_down(t_arguments **args);
// t_arguments	*args_move_one_down(t_arguments *args, t_arguments *prev);

#endif