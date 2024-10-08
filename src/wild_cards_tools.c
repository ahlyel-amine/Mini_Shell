/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabato <sabato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:58:45 by aahlyel           #+#    #+#             */
/*   Updated: 2024/08/05 21:15:55 by sabato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory)
{
	struct dirent	*dir;

	dir = readdir(directory);
	if (!dir)
		return (args);
	if (*str != '.' && *dir->d_name == '.')
	{
		args = get_files(str, args, directory);
		return (args);
	}
	if (ft_strncmp(dir->d_name, ".", 2) && ft_strncmp(dir->d_name, "..", 3))
	{
		if (compare_matches(str, dir->d_name))
			args = arguments_constructor(args, \
			ft_strdup(dir->d_name), IS_STR | IS_FILE, 0);
	}
	args = get_files(str, args, directory);
	return (args);
}
