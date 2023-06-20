/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:34:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 23:37:21 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H

# include "minishell.h"

int			ft_isname(char c);
int			ft_isvariable(char c);
int			ft_chrpos(char *line, char c);
char		*ft_strjoin_free(char *s1, char *s2);
size_t		ft_double_strlen(char **str);
int			close_parenthise(char *line);
void		check_out_of_quotes(char c, t_var *var);
int			skip_spaces_front(char *line);
void		pr_custom_err(char *error, void *ptr, char *custom);
void		panic(int type);
char		*skip_quote_heredoc_delimiter(char *line, int *j, int i, int *q);
t_arguments	*get_names(char *line, int *i);
int			check_for_syntax(char **line, int i);
char		*ft_strndup(const char *s, size_t n);

#endif