/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:08 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/23 15:22:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	args_len(t_arguments *args)
{
	t_arguments	*tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

size_t	args_strslen(t_arguments *args)
{
	t_arguments	*tmp;
	size_t		len;
	size_t		i;

	len = 0;
	tmp = args;
	while (tmp)
	{
		i = 0;
		if (!(tmp->type & QUOTE) && !(tmp->type & DQUOTE))
		{
			while (tmp->str[i])
			{
				i++;
				len++;
			}
		}
		else
			len += args_strslen(args->down);
		tmp = tmp->next;
	}
	return (len);
}

char	*args_to_str(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*f_tmp;
	char		*str;
	size_t		len;
	size_t		i;

	i = 0;
	tmp = args;
	len = args_strslen(args);
	if (!len)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		perror("");
		return (NULL);
	}
	len = 0;
	while (tmp)
	{
		i = 0;
		if (!(tmp->type & QUOTE) && !(tmp->type & DQUOTE))
			while (tmp->str[i])
				str[len++] = tmp->str[i++];
		else
		{
			f_tmp = tmp->down;
			while (f_tmp->down)
			{
				i = 0;
				while (f_tmp->down->str[i])
					str[len++] = f_tmp->down->str[i++];
				f_tmp->down = f_tmp->down->next;
			}
		}
		tmp = tmp->next;
	}
	str[len] = 0;
	return (str);
}

char	**args_to_dblstr(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	if (!len)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
	{
		perror("");
		return (NULL);
	}
	len = 0;
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
			str[len++] = ft_strdup(tmp->str);
		else
			str[len++] = args_to_str(tmp->down);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}

size_t	args_cmd_len(t_arguments *args)
{
	t_arguments	*tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		if (!(tmp->type & IS_SEPARTOR))
		len++;
		tmp = tmp->next;
	}
	return (len);
}

// char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
// {
// 	t_arguments	*tmp;
// 	char		**str;
// 	size_t		len;

// 	tmp = args;
// 	len = args_len(args);
// 	if (!len)
// 		return (NULL);
// 	str = malloc(sizeof(char *) * (len + 2));
// 	if (!str)
// 	{
// 		perror("");
// 		return (NULL);
// 	}
// 	len = 0;
// 	str[len++] = cmd;
// 	while (tmp)
// 	{
// 		if (tmp->type & IS_SEPARTOR)
// 			;
// 		else if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
// 			str[len++] = ft_strdup(tmp->str);
// 		else
// 			str[len++] = args_to_str(tmp->down);
// 		tmp = tmp->next;
// 	}
// 	str[len] = NULL;
// 	return (str);
// }
void	args_move_one_down(t_arguments *args, t_arguments *prev)
{
	t_arguments	*tmp;
	t_arguments	*down;


	tmp = args;
	if (tmp->next)
	{
		if (!(args->type & IS_SEPARTOR) && (args->next->type & DQUOTE || args->next->type & QUOTE))
		{
			if (!prev)
			{
				// args = args->next;
				tmp = args->next;
				args->next = args->next->down;
				args->next->down = args;
				args = tmp;
				print_arguments(tmp);
				return ;
			}
			else
			{
				prev->next = args->next;
				down = args->next;
			}
			tmp->next = down->down;
			down->down = tmp;
			// if (!prev)
			// 	args = down;
		}
		// else if (((*args)->type & DQUOTE || (*args)->type & QUOTE) && ((*args)->next->type & IS_SEPARTOR))
		// {
		// 	puts("in lwndjks ");
		// 	tmp = (*args)->down;
		// 	while (tmp->next)
		// 		tmp = tmp->next;
		// 	tmp->next = (*args)->next;
		// 	tmp->next->next = NULL;
		// 	(*args)->next = (*args)->next->next;
		// }
	}
}

void	args_move_down(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*prev;

	tmp = args;
	prev = NULL;
	if (!(args->type & IS_SEPARTOR) && (args->next->type & DQUOTE || args->next->type & QUOTE))
	{
		tmp = args->next;
		args->next = args->next->down;
		args->next->down = args;
		args = tmp;
	}
		print_arguments(tmp);
	// while (tmp)
	// {
	// 	args_move_one_down(tmp, prev);
	// 	prev = tmp;
	// 	tmp = tmp->next;
	// }
}
char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
{
	t_arguments	*tmp;
	char		**str;
	char		*tmp_str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	if (!len)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 2));
	if (!str)
	{
		perror("");
		return (NULL);
	}
	len = 0;
	str[len++] = cmd;
	while (tmp)
	{
		if (tmp->type & IS_SEPARTOR)
			;
		else if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
		{
			if (tmp->next && tmp->next->type & IS_SEPARTOR)
				str[len++] = ft_strdup(tmp->str);
			else if (tmp->next && !(tmp->next->type & IS_SEPARTOR))
			{
				puts("am herew");
				tmp_str = tmp->str;
				while (tmp)
				{
					if (tmp->next && !(tmp->next->type & IS_SEPARTOR))
						tmp_str = ft_strjoin(tmp_str, args_to_str(tmp->next->down));
					else
						break ;
					tmp = tmp->next;
				}
				str[len++] = tmp_str;
			}
			else
				str[len++] = ft_strdup(tmp->str);
		}
		else
			str[len++] = args_to_str(tmp->down);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}