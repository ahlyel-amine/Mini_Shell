/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/23 15:03:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_parsing(t_cmd *cmd);

int	check_and_parsing(t_cmd *cmd)
{
	if (!((t_and *)cmd)->left || !((t_and *)cmd)->right)
		return (0);
	else
		return (check_parsing(((t_and *)cmd)->left) & check_parsing(((t_and *)cmd)->right));
	return (1);
}

int	check_or_parsing(t_cmd *cmd)
{
	if (!((t_or *)cmd)->left || !(((t_or *)cmd)->right))
		return (0);
	else
		return (check_parsing(((t_or *)cmd)->left) & check_parsing(((t_or *)cmd)->right));
	return (1);
}

int	check_pipe_parsing(t_cmd *cmd)
{
	if (!((t_pipe *)cmd)->left || !(((t_pipe *)cmd)->right))
		return (0);
	else
		return (check_parsing(((t_pipe *)cmd)->left) & check_parsing(((t_pipe *)cmd)->right));
	return (1);
}

int	check_redir_parsing(t_cmd * cmd)
{
	char	*file_name;
	char	*line;
	if (((t_redir *)cmd)->cmd && ((t_redir *)cmd)->cmd->type == INVALID)
	{
		file_name = arguments_to_str(((t_redir *)cmd)->red.file_name);
		while (1337)
		{
			line = readline("heredoc> ");
			if (!line)
				break ;
			if (!strncmp(line, file_name, ft_strlen(file_name)))
			{
				free(line);
				break;
			}
			free(line);
		}
		pr_custom_err(ERR_SNTX, NULL, ((t_invalid *)((t_redir *)cmd)->cmd)->str);
		free (file_name);
		return (0);
	}
	return (1);
}

int	check_parsing(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->type == AND)
		return (check_and_parsing(cmd));
	else if (cmd->type == OR)
		return (check_or_parsing(cmd));
	else if (cmd->type == PIPE)
	return (check_pipe_parsing(cmd));
	else if (cmd->type == REDIR)
		return (check_redir_parsing(cmd));
	return (1);
}

void	print_arguments(t_arguments *args)
{
	t_arguments	*tmp;

	tmp = args;
	printf("--------------------arguments_START-------------------------\n");
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE || tmp->type & IS_SEPARTOR)
			printf("%d[%s]\n",tmp->type , tmp->str);
		else
		{
			t_arguments	*tmp2 = tmp->down;
			while (tmp2)
			{
				printf("%d]%s[\n",(tmp2)->type ,(tmp2)->str);
				tmp2 = (tmp2)->next;
			}
		}
		tmp = tmp->next;
	}
	printf("--------------------arguments_END----------------------------\n");
}

void	print_cmd(t_cmd *cmd)
{
	t_execcmd *cmds = (t_execcmd *)cmd;
		printf("---------cmd----------\n");
		if (!cmds)
			return ;
		if (cmds->cmd)
		print_arguments(cmds->cmd);
		printf("--------------------------\n");
		printf("---------options----------\n");
		if (cmds->options)
		print_arguments(cmds->options);
		printf("--------------------------\n");
}

void	controll_line(char **line)
{
	t_cmd	*cmd;

	cmd = NULL;
	complete_line(line);
	
	if (line && *line)
		cmd = parse_line(*line);
	
	// print_arguments(((t_execcmd *)cmd)->cmd);
	// print_arguments(((t_execcmd *)cmd)->options);
	// echo(cmd);
	t_execcmd *exec;
	exec = (t_execcmd *)cmd;
	args_move_down(exec->options);
	print_arguments(exec->options);
		
	// if (!check_parsing(cmd))
	// {
	// 	if (cmd)
	// 		free_line(cmd);
	// 	return ;
	// }
	if (cmd)
		free_line(cmd);


	// if (cmd->type == BUILTIN)
	// 	echo(cmd);
	// printf("\n\n\n\n");
	// execute_line(cmd);
	// printf("\n\n\n\n");
}
