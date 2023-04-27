/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 12:53:11 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void parse_line(char *line)
{
	t_cmd	*cmd;
	t_cmd	*left;
	t_cmd	*right;

	complete_line(&line);
	cmd = get_token_operator(ft_strdup(line));
	if (cmd->type == PIPE)
	{
		left = ((t_pipe *)cmd)->left;
		right = ((t_pipe *)cmd)->right;
		if (left->type == REDIR)
		{
			cmd = ((t_redir *)left)->cmd;
			if (cmd->type == EXEC)
			{
				while (*((t_execcmd *)cmd)->cmd)
					printf("%s\n", *((t_execcmd *)cmd)->cmd++);
			}
			printf("%s\n", ((t_redir *)left)->red.file_name);
			printf("%s\n", ((t_redir *)left)->red.efile_name);
			printf("%d\n", ((t_redir *)left)->red.fd);
			printf("%d\n", ((t_redir *)left)->red.mode);
			printf("%d\n", ((t_redir *)left)->red.type);
		}
		if (right->type == EXEC)
		{
			while (*((t_execcmd *)right)->cmd)
					printf("%s\n", *((t_execcmd *)right)->cmd++);
		}
	}
}
// int	count_arguments(char *line)
// {
// 	int	i;
// 	int	quote;
// 	int	dquote;
// 	int counter;

// 	counter = 0;
// 	dquote = 0;
// 	quote = 0;
// 	i = 0;
// 	while (line[i])
// 	{
// 		while (ft_isspace(line[i]))
// 			i++;
// 		check_out_of_quotes(line[i], &quote, &dquote);
// 		while (line[i] && !quote && !dquote && !ft_isspace(line[i]))
// 		{
// 			check_out_of_quotes(line[i], &quote, &dquote);
// 			i++;
// 		}
// 		if (ft_isspace(line[i]) || !line[i])
// 				counter++;
// 		else if (quote)
// 		{
// 			while (line[i] != '\'')
// 				i++;
// 			if (ft_isspace(line[i]) || !line[i])
// 				counter++;
// 		}
// 		else if (dquote)
// 		{
// 			while (line[i] != '\"')
// 				i++;
// 			if (line[i] == '\"')
// 				i++;
// 			if (ft_isspace(line[i]) || !line[i])
// 				counter++;
// 		}
// 	}
// 	return (counter);
// }

// char	**select_arguments(char *line, int count)
// {
// 	int		i;
// 	int		quote;
// 	int		dquote;
// 	int 	j;
// 	char	**cmd;

// 	cmd = malloc(sizeof (char *) * (count + 1));
// 	cmd[count] = NULL;
// 	count = 0;
// 	quote = 0;
// 	dquote = 0;
// 	i = 0;
// 	j = 0;

// 	while (line[i + j])
// 	{
// 		while (ft_isspace(line[i + j]))
// 			j++;
// 		check_out_of_quotes(line[i + j], &quote, &dquote);
// 		while (line[i + j] && !quote && !dquote && !ft_isspace(line[i + j]))
// 		{
// 			check_out_of_quotes(line[i + j], &quote, &dquote);
// 			j++;
// 		}
// 		if (ft_isspace(line[i + j]) || !line[i + j])
// 		{
// 			cmd[count++] = ft_substr(line, i, j);
// 			i += j;
// 		}
// 		else if (quote)
// 		{
// 			while (line[i + j] != '\'')
// 				j++;
// 			if (ft_isspace(line[i + j]) || !line[i + j])
// 			{
// 				cmd[count++] = ft_substr(line, i, j);
// 				i += j;
// 			}
// 		}
// 		else if (dquote)
// 		{
// 			while (line[i + j] != '\"')
// 				j++;
// 			if (line[i + j] == '\"')
// 				j++;
// 			if (ft_isspace(line[i + j]) || !line[i + j])
// 			{
// 				cmd[count++] = ft_substr(line, i, j - 1);
// 				i += j;
// 			}
// 		}
// 		j = 0;
// 	}
// 	j = 0;
// 	while (cmd[j])
// 		printf("|%s|\n", cmd[j++]);
// 	return (cmd);
// }


