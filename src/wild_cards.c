/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:49:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/23 22:54:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int compare_matches(char *realfile, char *myfile);
static int skip_unkown(char *realfile, char *myfile);
t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory);

t_arguments	*open_cwd(char *str)
{
	DIR				*directory;
	struct dirent	*dir;
	t_arguments		*files;

	files = NULL;
	directory = opendir(".");
	files = get_files(str, files, directory);
	closedir(directory);
	return (files);
}

void	wild_cards(t_arguments **args)
{
	t_arguments	*files;
	char		*tmp;

	if (!*args)
		return ;
	if (((*args)->type & IS_STR) && ft_strchr((*args)->str, '*'))
	{
		puts ("am here");
		tmp = (*args)->str;
		files = open_cwd((*args)->str);
		if (files)
		{
			replace_arg(args, args, files);
			free (tmp);
		}
	}
	else
		wild_cards(&(*args)->next);
}


static int skip_unkown(char *myfile, char *realfile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
    while (myfile[i] == '*')
        i++;
	if (!myfile[i])
		while (realfile[j])
			j++;
	else
		while (myfile[i] && realfile[j] && realfile[j] != myfile[i])
			j++;
    if (myfile[i] && realfile[j] && realfile[j] == myfile[i])
       return compare_matches(myfile + i, realfile + j);
    else if (!myfile[i] && !realfile[j])
        return (1);
    else
        return (0);
}

static int compare_matches(char *myfile, char *realfile)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
    while (myfile[i] && realfile[j] && myfile[i] == realfile[j])
    {
        i++;
        j++;
    }
    if (myfile[i] == '*')
        return skip_unkown(myfile + i, realfile + j);
    else if (!myfile[i] && !realfile[j])
        return (1);
    else
        return (0);
}


t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory)
{
	struct dirent	*dir;
	int				i;

	i = 0;
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
		{
		printf("<|%s|><|%s|>\n", dir->d_name, str);
			args = arguments_constructor(args, ft_strdup(dir->d_name), IS_STR);
		}
	}
	args = get_files(str, args, directory);
	return (args);
}

// t_arguments	*transform_new_files(char **str)
// {
// 	t_arguments	*files;
// 	int	i;

// 	i = 0;
// 	files = NULL;
// 	while (str[i])
// 	{
// 		files = arguments_constructor(files, str[i], IS_STR);
// 		i++;
// 	}
// 	free (str);
// 	return (files);
// }

// void	*wild_cards(t_arguments *args, char *word)
// {
// 	t_arguments	*head;
// 	t_arguments	*tmp;
// 	t_arguments	*tmp2;
// 	char		*files;
// 	int 		a;

// 	// if (word)
// 	// {
// 	// 	if (ft_strchr(word, '*'))
// 	// 		word = find_files(word);
// 	// 	return (word);
// 	// }
// 	head = args;
// 	while (args)
// 	{
// 		a = 0;
// 		if ((args->type & IS_STR) && ft_strchr(args->str, '*'))
// 		{
// 			files = find_files(args->str);
// 			if (files != args->str)
// 			{
// 				tmp = args->next;
// 				if (args == head)
// 					a = -1;
// 				free (args->str);
// 				free (args);
// 				args = transform_new_files(ft_split(files, ' '));
// 				if (a == -1)
// 					head = args;
// 				else
// 					tmp2->next = args;
// 				while (args->next)
// 					args = args->next;
// 				args->next = tmp;
// 			}
// 		}
// 		tmp2 = args;
// 		args = args->next;
// 	}
// 	args = head;
// 	return (args);
// }

// char	*find_files(char *files)
// {
// 	DIR				*directory;
// 	struct dirent	*dir;
// 	char			*result;
// 	int				i;
// 	int				j;

// 	result = NULL;
// 	directory = opendir(".");
// 	if (directory)
// 	{
// 		dir = readdir(directory);
// 		while (dir != NULL)
// 		{
// 			i = 0;
// 			j = 0;
// 			if ((*dir->d_name == '.' && !*(dir->d_name + 1)) || \
// 			(*dir->d_name == '.' && *(dir->d_name + 1) == '.' && !*(dir->d_name + 2)) || \
// 			(*files != '.' && *dir->d_name == '.'))
// 			{
// 				dir = readdir(directory);
// 				continue ;
// 			}
// 			while (dir->d_name[i])
// 			{
// 				while (files[i] && dir->d_name[j] && files[i] != '*' && files[i] == dir->d_name[j])
// 				{
// 					i++;
// 					j++;
// 				}
// 				if (files[i] == '*')
// 				{
// 					i++;
// 					if (!files[i])
// 					{
// 						if (result)
// 							result = ft_strjoin_free(result, ft_strdup(" "));
// 						result = ft_strjoin_free(result, ft_strdup(dir->d_name));
// 						break ;
// 					}
// 					while (dir->d_name[j] && files[i] != dir->d_name[j])
// 						j++;
// 				}
// 				if (!files[i] && !dir->d_name[j])
// 				{
// 					if (result)
// 						result = ft_strjoin_free(result, ft_strdup(" "));
// 					result = ft_strjoin_free(result, ft_strdup(dir->d_name));
// 					break ;
// 				}
// 				else if (files[i] != dir->d_name[j])
// 					break ;
// 			}
// 			dir = readdir(directory);
// 		}
// 		closedir(directory);
// 	}
// 	if (result)
// 		return (result);
// 	else
// 		return (files);
// }