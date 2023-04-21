/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/21 03:29:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_tree	*new_node(char *data)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->prev = NULL;
	return (new);
}
void fun()
{
	system("leaks minishell");
}
// char	**get_env(char **envp)
// {
// 	char	**program_env;

	
// }

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;

	tree = NULL;

	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	while (1)
	{
		line = readline("minishell#  ");
		if (!line || !ft_strncmp(line, "exit", 5))
			exit(0);
		if (!*line)
			continue ;
		else
			add_history(line);
		parsing_controll(&tree, line);
	}
	return (0);
}