/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:40:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 21:14:48 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"

void		*set__get_option_variables(void *env, \
int set__get_option);
////-/__________________________________________________________//-|
///-/                          TOOLS                           //--|
//-/__________________________________________________________//---|

void		sp_free(char **splt);
char		*app_dup(char *arg);
void		env_exp_print(t_list *sort_lst, void (*print)(char *, int));

t_list		*sort_list(t_list *lst, int (*cmp)(const char *, \
const char *, size_t));
t_list		*lst_dup(t_list *lst);
void		ft_list_remove(t_list **lst_tmp, char *data, \
int (*cmp)());
void		controll_line(char **line);
void		read_line(void);
void		complete_line(char **line, int *brea);
void		wild_cards(t_arguments **args);
int			compare_matches(char *realfile, char *myfile);
t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory);
char		*set_pwd(char *o_pwd);
void		unset(t_hold *env, char ***path, char **pwd, char **homedir);
char		**set_env(char **env);

#endif