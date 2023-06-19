/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:40:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:34:24 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"

void						*set__get_option_variables(void *env,
								int set__get_option);
////-/__________________________________________________________//-|
///-/                          TOOLS                           //--|
//-/__________________________________________________________//---|

void						sp_free(char **splt);
char						*app_dup(char *arg);
void						env_exp_print(t_list *sort_lst,
								int (*print)(const char *, ...));

t_list						*sort_list(t_list *lst, int (*cmp)(const char *,
									const char *, size_t));
t_list						*lst_dup(t_list *lst);
void						ft_list_remove(t_list **lst_tmp, char *data,
								int (*cmp)());
void						controll_line(char **line);
void						read_line(void);
void						complete_line(char **line, int *brea);
void						wild_cards(t_arguments **args);

#endif