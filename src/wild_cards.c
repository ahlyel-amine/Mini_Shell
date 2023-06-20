/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:49:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 16:27:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int			compare_matches(char *realfile, char *myfile);
static int			skip_unkown(char *realfile, char *myfile);
static t_arguments	*get_files(char	*str, t_arguments *args, DIR *directory);

static t_arguments	*open_cwd(char *str)
{
	DIR				*directory;
	t_arguments		*files;

	files = NULL;
	directory = opendir(".");
	files = get_files(str, files, directory);
	closedir(directory);
	return (files);
}

void	wild_card_replace(t_arguments **args, \
t_arguments *prev, t_arguments **front)
{
	t_arguments	*files;
	t_arguments	*tmp_next;

	files = open_cwd((*front)->str);
	if (files)
	{
		tmp_next = files;
		while (tmp_next->next)
			tmp_next = tmp_next->next;
		tmp_next->next = (*front)->next;
		tmp_next = (*front)->next;
		if (prev != *args)
			prev->next = files;
		else
			*args = files;
		free((*front)->str);
		free(*front);
		*front = tmp_next;
	}
}

void	wild_cards(t_arguments **args)
{
	t_arguments	*prev;
	t_arguments	*front;

	prev = *args;
	front = *args;
	while (front)
	{
		if ((front->type & IS_STR) && ft_strchr(front->str, '*'))
			wild_card_replace(args, prev, &front);
		prev = front;
		if (front)
			front = front->next;
	}
}

static int	skip_unkown(char *myfile, char *realfile)
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
		while (myfile[i] && realfile[j] && \
		(realfile[j] != myfile[i] || \
		(realfile[j] == myfile[i] && realfile[j + 1] == myfile[i])))
			j++;
	if (myfile[i] && realfile[j] && realfile[j] == myfile[i])
		return (compare_matches(myfile + i, realfile + j));
	else if (!myfile[i] && !realfile[j])
		return (1);
	else
		return (0);
}

static int	compare_matches(char *myfile, char *realfile)
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
	{
		while (j && realfile[j - 1] == realfile[j])
			j++;
		if (!realfile[j])
			return (1);
		return (skip_unkown(myfile + i, realfile + j));
	}
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
			args = arguments_constructor(args, \
			ft_strdup(dir->d_name), IS_STR | IS_FILE, 0);
	}
	args = get_files(str, args, directory);
	return (args);
}
