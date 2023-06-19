/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:34:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 13:00:48 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

char	*skip_q_hrdc_delim(char *line, char *end_line, int *q);
int		read_heredocs(char *delimiter, int q);
char	*get_filename(char *line, char *endline);

#endif