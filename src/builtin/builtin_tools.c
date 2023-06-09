/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:42:38 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/09 19:33:44 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	adjust_shlvl(t_hold *env)
{
	t_list	*lst;
	int		num;
	short	flg;

	flg = 0;
	lst = env->lst;
	while (lst)
	{
		if (!ft_memcmp(lst->content, "SHLVL=", 6))
		{
			num = ft_atoi((lst->content + 6));
			free(lst->content);
			lst->content = ft_strjoin_free(ft_strdup("SHLVL="), ft_itoa(++num));
			flg = 1;
		}
		lst = lst->next;
	}
	if (!flg)
	{
		ft_lstadd_back(&(env->lst), ft_lstnew(ft_strdup("SHLVL=1")));
		env->size++;
	}	
}
// void	pre_
char	**ft_dstrdup2(char **ds1)
{
	char	**words;
	int		ds1_len;	
	int		j;
	
	ds1_len = ft_double_strlen(ds1);
	j = -1;
	words = malloc(sizeof(char *) * (ds1_len + 1));
	if (!words)
		return (NULL);
	while (ds1[++j])
		words[j] = ft_strdup(ds1[j]);
	words[j] = NULL;
	return (words);
}
void	ft_lstadd_node(t_list **lst, t_list *new, int pos)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = NULL;
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next && count < pos)
		{
			tmp = tmp->next;
			count++;
		}	
		new->next = tmp->next;
		tmp->next = new;
	}	
}

void	env_key_cmp(char *pwd, char *to_replace, void **lst_content, short *flg)
{
	char	*tmp;

	tmp = *((char **)lst_content);
		*flg = 1;
		*lst_content = ft_strjoin_free(ft_strdup(to_replace), ft_strdup(pwd));
		free(tmp);
}
char	*prepare_pwd(void)
{
	char	*pwd;

	pwd = get_owd("PWD=");
	if (!pwd)
	{
		set__get_option_variables(0, SET_PWD);
        pwd = ft_strdup(set__get_option_variables(0, GET | GET_PWD));
	}
	else
		pwd = ft_strdup(pwd);
	return (pwd);
}

int	d_point_pwd(char *path, char *pwd)
{
	int	ret;
	char	cwd2[PATH_MAX];
	if (!stat_check(path))
		return (1);
	ret = chdir(path);
	if (ret == -1)
		return (printf("cd: %s: %s\n", path, strerror(errno)), (1));
	getcwd(cwd2, sizeof(cwd2));
	reset_env(cwd2, pwd);
	return (ret);
}
int	go_to_oldpwd(char *cwd, char *path)
{
	char	*env_path;
	int		ret;

	env_path = get_owd("OLDPWD=");
	if (!stat_check(env_path))
		return (1);
	if (!env_path)
		return (ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR_FILENO), (1));
	if (access(env_path, R_OK) != 0)
		return (printf("cd: %s: %s\n", path, "No such file or directory"), (1));
	if (get_owd("PWD=") && !*cwd)
		reset_env(env_path, get_owd("PWD="));
	else    
		reset_env(env_path, cwd);
	ft_putendl_fd(get_owd("PWD="), out);
	ret = chdir(get_owd("PWD="));
	return (ret);
}
// env | awk -F= '{print $1}' | while read -r line; do unset "$line"; done