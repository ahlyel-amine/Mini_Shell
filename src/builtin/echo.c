/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/18 23:02:20 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_dstr_to_str(char **clone)
{
	char	*r_str;
	int		indx;

	indx = 0;
	r_str = ft_strdup("");
	while (clone && *clone)
	{
		r_str = ft_strjoin_free(r_str, clone[indx++]);
	}
	if (indx)
		free(clone);
	return (r_str);
}

void	print_arguments(t_arguments *args, char *ref)
{
	t_arguments	*tmp;
	t_arguments	*tmp2;

	tmp = args;
	printf("--------------------arguments_START----%s--------\n", ref);
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE
			|| tmp->type & IS_SEPARTOR)
			printf("%d[%s]\n", tmp->type, tmp->str);
		else
		{
			tmp2 = tmp->down;
			printf("{%d}\n", tmp->type);
			while (tmp2)
			{
				printf("%d]%s[\n", (tmp2)->type, (tmp2)->str);
				tmp2 = (tmp2)->next;
			}
		}
		tmp = tmp->next;
	}
	printf("--------------------arguments_END------%s----------------\n", ref);
}

void	tt_echo(t_arguments *cmd_args, int echo_has_option)
{
	char		*arg;

	print_arguments(cmd_args, "alo");
	transform_args(&cmd_args);
	arg = args_to_str(cmd_args);
	if (!echo_has_option)
		ft_putendl_fd(arg, out);
	else
		ft_putstr_fd(arg, out);
	glo_exit = 0;
	free(arg);
}
