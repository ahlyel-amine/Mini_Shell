#ifndef BUILTIN_H
#define BUILTIN_H

# include "minishell.h"

void	do_cmp(char	*val, char **lst_cnt, short opt, size_t len);
short	is_export_var(char *str);
int	dp_point_skip(char *path);
int	err_print(char *s1, char *s2, char *s3);
void	critical_err(void);
#endif