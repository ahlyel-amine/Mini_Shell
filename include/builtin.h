#ifndef BUILTIN_H
#define BUILTIN_H

# include "minishell.h"

short		is_export_var(char *str);
void		do_cmp(char	*val, char **lst_cnt, short opt, size_t len);
char		**args_to_dblstr_(t_arguments *args);
void		critical_err(void);
int			err_print(char *s1, char *s2, char *s3);
int			dp_point_skip(char *path);
#endif