/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:49:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/22 19:02:51 by aahlyel          ###   ########.fr       */
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
		return (result);
	else
		return (files);
}
t_arguments	*transform_new_files(char **str)
{
	t_arguments	*files;
	int	i;

	i = 0;
	files = NULL;
	while (str[i])
	{
		files = arguments_constructor(files, str[i], IS_STR);
		i++;
	}
	free (str);
	return (files);
}

void	*wild_cards(t_arguments *args, char *word)
{
	t_arguments	*head;
	t_arguments	*tmp;
	t_arguments	*tmp2;
	char		*files;
	int 		a;

	if (word)
	{
		if (ft_strchr(word, '*'))
			word = find_files(word);
		return (word);
	}
	head = args;
	while (args)
	{
		a = 0;
		if ((args->type & IS_STR) && ft_strchr(args->str, '*'))
		{
			files = find_files(args->str);
			if (files != args->str)
			{
				tmp = args->next;
				if (args == head)
					a = -1;
				free (args->str);
				free (args);
				args = transform_new_files(ft_split(files, ' '));
				if (a == -1)
					head = args;
				else
					tmp2->next = args;
				while (args->next)
					args = args->next;
				args->next = tmp;
			}
		}
		tmp2 = args;
		args = args->next;
	}
	args = head;
	return (args);
}
