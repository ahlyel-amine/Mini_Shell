/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:33:29 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/06 09:51:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*pipe_constructor(t_cmd *left, t_cmd *right)
{
	t_pipe	*pipe;

	// printf("^^^^^^^^^^^^^^^pipe_constructor_caled^^^^^^^^^^^^^^^\n");
	pipe = malloc(sizeof(t_pipe));
	ft_memset(pipe, 0, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_cmd *)pipe);
}
t_cmd	*execcmd_constructor(t_arguments *cmds, t_arguments *options)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(t_execcmd));
	ft_memset(cmd, 0, sizeof(t_execcmd));
	cmd->type = EXEC;
	cmd->cmd = cmds;
	cmd->options = options;
	// printf("-------------execcmd_constructor--------------\n");
	// print_cmd((t_cmd *)cmd);
	return ((t_cmd *)cmd);
}

t_cmd	*redir_constructor(t_cmd *cmd, t_redir_content content)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	ft_memset(redir, 0, sizeof(t_redir));
	redir->type = REDIR;
	redir->cmd = cmd;
	redir->red = content;
	// printf("-------------redir_constructor----------------\n");
	// t_arguments *a;
	// a = redir->red.file_name;
	// while (a)
	// {
	// 	printf("type[%d] | filename: |%s|\n", a->type, a->str);
	// 	a = a->next;
	// }
	// printf("mode : |%d| fd : |%d| type : |%d|\n", redir->red.mode, redir->red.fd, redir->red.type);
	// if (cmd)
	// 	printf("has cmd type |%d|\n", redir->cmd->type);
	// printf("----------------------------------------------\n");
	return ((t_cmd *)redir);
}

t_cmd	*and_constructor(t_cmd *left, t_cmd *right)
{
	t_and	*and;

	// printf("^^^^^^^^^^^^^^^and_constructor_caled^^^^^^^^^^^^^^^\n");
	and = malloc(sizeof(t_and));
	ft_memset(and, 0, sizeof(t_and));
	and->type = AND;
	and->left = left;
	and->right = right;
	return ((t_cmd *)and);
}

t_cmd	*or_constructor(t_cmd *left, t_cmd *right)
{
	t_or	*or;

	// printf("^^^^^^^^^^^^^^^or_constructor_caled^^^^^^^^^^^^^^^\n");
	or = malloc(sizeof(t_or));
	ft_memset(or, 0, sizeof(t_or));
	or->type = OR;
	or->left = left;
	or->right = right;
	return ((t_cmd *)or);
}

t_cmd	*invalid_constructor(char *str)
{
	t_invalid	*invalid;

	invalid = malloc(sizeof(t_invalid));
	ft_memset(invalid, 0, sizeof(t_invalid));
	invalid->type = INVALID;
	invalid->str = str;
	// printf("-------------invalid_constructor--------------\n");
	// printf("filename: |%s|\n", invalid->str);
	// printf("----------------------------------------------\n");
	return ((t_cmd *)invalid);
}

t_cmd	*builtin_constructor(char *str, unsigned short has_option, t_arguments *arguments)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	ft_memset(builtin, 0, sizeof(t_builtin));
	builtin->type = BUILTIN;
	builtin->builtin = str;
	builtin->arguments = arguments;
	builtin->has_option = has_option;
	// printf("-------------builtin_constructor--------------\n");
	// printf("builtin: |%s|\n", builtin->builtin);
	// if (has_option)
	// printf("echo has option -n \n");
	// t_arguments *a;
	// a = arguments;
	// puts("alo");
	// while (a)
	// {
	// 	if (a->type == IS_STR || a->type == IS_VARIABLE)
	// 		printf("type : |[%d]| arguments : |%s|\n",a->type, a->str);
	// 	else
	// 	{
	// 		while (a->down)
	// 		{
	// 			printf("type : |[%d]| arguments : |%s|\n",a->down->type, a->down->str);
	// 			a->down = a->down->next;
	// 		}
	// 	}
	// 	a = a->next;
	// }
	// printf("----------------------------------------------\n");
	return ((t_cmd *)builtin);
}

t_cmd	*assignement_constructor(char *key, char *value)
{
	t_assignement	*assignement;

	assignement = malloc(sizeof(t_assignement));
	ft_memset(assignement, 0, sizeof(t_assignement));
	assignement->type = ASSIGNEMENT;
	assignement->key = key;
	assignement->value = value;
	// printf("------------assignement_constructor------------\n");
	// printf("key : |%s|\n", assignement->key);
	// printf("value : |%s|\n", assignement->value);
	// printf("----------------------------------------------\n");
	return ((t_cmd *)assignement);
}