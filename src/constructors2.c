/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:10:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:15:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*invalid_constructor(char *str)
{
	t_invalid	*invalid;

	invalid = malloc(sizeof(t_invalid));
	ft_memset(invalid, 0, sizeof(t_invalid));
	invalid->type = INVALID;
	invalid->str = str;
	return ((t_cmd *)invalid);
}

t_cmd	*builtin_constructor(char *str, unsigned short has_option, \
t_arguments *arguments)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	ft_memset(builtin, 0, sizeof(t_builtin));
	builtin->type = BUILTIN;
	builtin->builtin = str;
	builtin->arguments = arguments;
	builtin->has_option = has_option;
	return ((t_cmd *)builtin);
}
