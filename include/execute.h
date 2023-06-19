#ifndef EXECUTE_H
# define EXECUTE_H

// # include "minishell.h"
#include <signal.h>
char		*arguments_to_str(t_arguments *args);
char		**ft_dstrdup(char **env);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);
void		adjust_shlvl(t_hold *env);
char		*data_analyse(char *str);
void		ft_lstadd_node(t_list **lst, t_list *new, int pos);
void		env_key_cmp(char *pwd, char *to_replace, void **lst_content, short *flg);
char		*prepare_pwd(void);
int     	stat_check(char *path);
int			d_point_pwd(char *path, char *pwd);
void		reset_env(char *pwd, char *o_pwd);
int			go_to_oldpwd(char *cwd, char *path);
short       valid_var(char *var);
char		**args_to_dblstr_(t_arguments *args);
////-/__________________________________________________________//-|
///-/                         EXPANDER                         //--|
//-/__________________________________________________________//---|
char		*tilde_expansion(char *arg, unsigned short type, t_arguments *next);

////-/__________________________________________________________//-|
///-/                           EXEC                           //--|
//-/__________________________________________________________//---|
// int		tt_pwd();
// void	tt_cd(t_arguments *cd_args);
// void	tt_echo(t_arguments *cmd_args, int echo_has_option);
// void	tt_env(t_arguments *cmd_args);
// void	tt_unset(t_arguments *cmd_args);
// void	tt_export(t_arguments *cmd_args);
// void	tt_exit(t_arguments *cmd_args);

////-/__________________________________________________________//-|
///-/                        tt_cd_tools                       //--|
//-/__________________________________________________________//---|
int         stat_check(char *path);
void        reset_env(char *pwd, char *o_pwd);
char        *extend_option(char *arg, char *ex_with, int opt);
char        *get_prev_path(char *path);
int         ft_go_to(int opt, char **path, char *cwd);
int         prev_drictory_count(char *wd);
////-/__________________________________________________________//-|
///-/                           SIGNALS                        //--|
//-/__________________________________________________________//---|
void	    sig_handl();
void	    sig_exec_init(void);
void	    sig_here();

#endif