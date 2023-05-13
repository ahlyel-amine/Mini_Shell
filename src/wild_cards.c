/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:49:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/13 14:29:54 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*find_files(char *files)
{
	DIR				*directory;
	struct dirent	*dir;
	char			*result;
	int				i;
	int				j;

	result = NULL;
	directory = opendir(".");
	if (directory)
	{
		dir = readdir(directory);
		while (dir != NULL)
		{
			i = 0;
			j = 0;
			if ((*dir->d_name == '.' && !*(dir->d_name + 1)) || \
			(*dir->d_name == '.' && *(dir->d_name + 1) == '.' && !*(dir->d_name + 2)) || \
			(*files != '.' && *dir->d_name == '.'))
			{
				dir = readdir(directory);
				continue ;
			}
			while (dir->d_name[i])
			{
				while (files[i] && dir->d_name[j] && files[i] != '*' && files[i] == dir->d_name[j])
				{
					i++;
					j++;
				}
				if (files[i] == '*')
				{
					i++;
					if (!files[i])
					{
						if (result)
							result = ft_strjoin_free(result, ft_strdup(" "));
						result = ft_strjoin_free(result, ft_strdup(dir->d_name));
						break ;
					}
					while (dir->d_name[j] && files[i] != dir->d_name[j])
						j++;
				}
				if (!files[i] && !dir->d_name[j])
				{
					if (result)
						result = ft_strjoin_free(result, ft_strdup(" "));
					result = ft_strjoin_free(result, ft_strdup(dir->d_name));
					break ;
				}
				else if (files[i] != dir->d_name[j])
					break ;
			}
			dir = readdir(directory);
		}
		closedir(directory);
	}
	if (result)
		return (free(files), result);
	else
		return (files);
}

void	*wild_cards(t_arguments *args, char *word)
{
	t_arguments	*head;

	if (word)
	{
		if (ft_strchr(word, '*'))
			word = find_files(word);
		return (word);
	}
	head = args;
	while (args)
	{
		if (!(args->type & DONT_EXPAND_WILD_CARDS) && ft_strchr(args->str, '*'))
			args->str = find_files(args->str);
		args = args->next;
	}
	return (head);
}
