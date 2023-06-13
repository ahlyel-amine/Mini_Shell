/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:55:07 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/14 00:05:04 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

short	re_env_var(char *str, char *val, int opt)
{
	t_hold	*hold;
	t_list	*lst_tmp;
	size_t	len;

	hold = set__get_option_variables(0, GET | GET_ENV);
	lst_tmp = hold->lst;
	len = ft_strlen(str);
	while (lst_tmp)
	{
		if (!ft_strncmp(str, lst_tmp->content, len) \
		&& (*((char *)lst_tmp->content + len) == '=' || \
		!*((char *)lst_tmp->content + len)) && !opt)
			return (do_cmp(val, (char **)(&lst_tmp->content), opt, len), free(str), 1);
		else if (!ft_strncmp(str, lst_tmp->content, len) \
		&& (*((char *)lst_tmp->content + len) == '=' \
		|| !*((char *)lst_tmp->content + len)) && opt)	
			return (do_cmp(val, (char **)(&lst_tmp->content), opt, len), free(str), 1);
		lst_tmp = lst_tmp->next;
	}
	return (free(str), free(val), 0);
}

void	add_val(char *arg, short opt)
{
	t_hold	*env;

	env = set__get_option_variables(0, GET | GET_ENV);
	if (!opt)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(ft_strdup(arg)), env->size >> 1);
		env->size++;
	}
	else if (opt == 1)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(app_dup(arg)), env->size >> 1);
		env->size++;
	}
	else
		ft_lstadd_back(&env->lst, ft_lstnew(ft_strdup(arg)));
}


void    val(char *arg)
{
	t_hold  *env;
	char    *append;
	char    *replace;
	size_t  len;

	len = ft_strlen(arg);
	append = ft_memchr(arg, '+', len);
	replace = ft_memchr(arg, '=', len);
	env = set__get_option_variables(0, GET | GET_ENV);
	if (!append && replace)
	{
		if(!(re_env_var(ft_substr(arg, 0, (replace - arg)), ft_strdup(arg), 0)))
			add_val(arg, 0);   
	}
	else if (append)
	{
		if(!(re_env_var(ft_substr(arg, 0, ((append) - arg)), \
		ft_substr(arg, (append - arg) + 2, (len - 1) - (append - arg)), 1)))
			add_val(arg, 1);       
	}
	else
		if (is_export_var(arg))
			add_val(arg, -1);
}

int get_operator(char **arg)
{
	char    **_arg;
	int iter;
	int ret;
	iter = -1;
	ret = 0;
	_arg = arg;
	while (_arg[++iter])
	{
		if (valid_id(_arg[iter]))
		{
			printf("minishell: export: '%s': not a valid identifier\n", _arg[iter]);
			ret = 1; 
			continue;
		}
		val(_arg[iter]);
	}
	// sp_free(_arg);
	return (ret);
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
size_t	args_len_(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*d_tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->type & QUOTE || tmp->type & DQUOTE)
			len++;
		else if (!tmp->next || tmp->type & IS_SEPARTOR)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**args_to_dblstr_(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	char		*tst;
	size_t		len;

	tmp = args;
	len = args_len_(args);
	if (!len)
		return (NULL);
	str = ft_calloc(sizeof(char *), len + 1);
	len = 0;
	while (tmp)
	{
		tst = ft_strdup("");
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
		{
			puts("2");
			if ((tmp->type & IS_VARIABLE) && !*tmp->str)
			{
				free(tst);
				tmp = tmp->next;
				continue;
			}
			while (tmp && tmp->type != IS_SEPARTOR)
			{
				tst = ft_strjoin_free(tst, ft_strdup(tmp->str));
				tmp = tmp->next;
			}
			str[len++] = tst;
		}
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
		{
			puts("1");
			str[len++] = args_to_str(tmp->down);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (str);
}
void    tt_export(t_cmd *cmd)
{
	char        **args;
	t_builtin   *export;
	t_hold      *hold;
	t_list      *lst_tmp;
	int         ret;

	ret = 0;
	export = (t_builtin *)cmd;
	transform_args(&export->arguments);
	args = args_to_dblstr_(export->arguments);
	hold = set__get_option_variables(0, GET | GET_ENV);
	if (!args || !*args)
	{
		lst_tmp = lst_dup(hold->lst);
		lst_tmp = sort_list(lst_tmp, ft_strncmp);
		env_exp_print(lst_tmp, printf);
		ft_lstclear(&lst_tmp, free);
	}
	else
	{
		ret = get_operator(args);
		sp_free(args);
	}
	set__get_option_variables(hold, SET);
	glo_exit = ret;
}
