/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:33:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 02:24:17 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

int				cmd_sig_check(int status);
int				builtin_executer(t_arguments **args, int outfile, int falg);
char			**child_vars(void);
int				redirection(t_lsttoken *front, t_lsttoken *back, \
t_components comp);
int				pipe_(t_lsttoken *front, t_lsttoken *back, t_components comp);
int				operator(t_lsttoken *front, t_lsttoken *back, \
t_components comp);
t_arguments		*get_cmd(t_lsttoken *front, t_lsttoken *back, int is_builtin);
void			subsh_call(t_lsttoken *head, t_components comp);
void			pipe_call(t_2ptr_t_lsttoken a, t_lsttoken *head, \
t_lsttoken *prev, t_components comp);
size_t			get_lenght(t_lsttoken *front);
char			*get_line(t_lsttoken *front, size_t len);
int				is_builtin(char *word);
char			*get_path(char *cmd);
int				cmd_executers(char *path, char **cmd, t_components comp);
char			*get_command_name(t_lsttoken **front, t_lsttoken *back);
t_components	get_red(t_lsttoken *redir, t_components comp, int *in);
int				pipe_left(t_lsttoken *head, t_lsttoken *back);
t_arguments		*skip_echo_option(t_arguments *front, int *has_option);
t_lsttoken		*skip_space_front_token(t_lsttoken *front);
int				last_operaotr(t_lsttoken *front, t_lsttoken *back);
void			init_2ptr(t_lsttoken **head, t_lsttoken **prev, \
t_lsttoken *front);
t_lsttoken		*skip_tokens(t_lsttoken *head, t_lsttoken *back, int *start, \
int *end);
int				has_slash(char *cmd);
char			*is_dir(char *cmd);
void			child_exit(void);
int             find_space(char *str);

#endif