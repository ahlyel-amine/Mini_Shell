/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:34:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 14:34:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

t_lsttoken	*tokenize(char *line, char *endline, int i);
int			a_check(t_lsttoken	*new);
t_lsttoken	*new_token(t_token t_);
t_lsttoken	*ft_lstokenlast(t_lsttoken *lst);
void		ft_lstokenadd_back(t_lsttoken **lst, t_lsttoken *new);
t_lsttoken	*check_tokenize(t_lsttoken *new);
void		free_lsttoken(t_lsttoken *new);
int			get_fds(t_lsttoken	*fds);
int			red_right_token(t_lsttoken **head, char *line, int *i);
int			red_left_token(t_lsttoken **head, char *line, int *i);
void		str_token(t_lsttoken **head, char *line, int *i);
int			close_dquote(t_arguments **arguments, char *line, int i);
int			close_quote(t_arguments **arguments, char *line, int i);
void		arguments_destructor(t_arguments **arguments);
void		arguments_add_back(t_arguments **head, t_arguments *new);
void		down_to_str(t_arguments *args, char **str, size_t *len);
void		transform_args(t_arguments **args);
char		*args_to_str(t_arguments *args);
char		**args_to_cmd_dstr(t_arguments *args, char *cmd);
char		**args_to_dblstr(t_arguments *args);
void		args_join(t_arguments **args);
void		args_move_down(t_arguments **args, t_arguments **prev);
void		replace_arg(t_arguments **head, t_arguments **old, \
t_arguments *new);
void		merge_arguments(t_arguments **arguments, int is_dquote);
void		args_join_down(t_arguments **args);
void		tokenize_variables(t_arguments **arguments);
size_t		args_len(t_arguments *args);
size_t		args_strslen(t_arguments *args);
t_arguments	*ft_split_str_to_args(char *str, int is_dquote);
t_arguments	*still_args(char *str, int *j, int *i, t_arguments *args);
t_arguments	*get_argument(char *line, int i, int flg);
t_arguments	*arguments_constructor(t_arguments *arguments, char *str,
				unsigned short type, unsigned short q);
t_arguments	*get_argument_no_tknz(char *line, int i);
t_arguments	*get_arguments(char *line, int i, int flg);
#endif