#ifndef EXECUTE_H
# define EXECUTE_H

// # include "minishell.h"
#include <signal.h>
char		*arguments_to_str(t_arguments *args);
char		**ft_dstrdup(char **env);
char		**ft_dstrdup2(char **ds1);
void		execute_line(t_cmd *cmd);
int			pipe_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			pipe_part_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			or_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			or_part_executer(t_cmd *cmd, int infile, int outfile, int *fd);
char		*get_path(char *cmd);
int			cmd_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			and_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			and_part_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			redirect_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int			builtin_executer(t_cmd *cmd, int infile, int outfile, int *fd);
size_t		ft_double_strlen(char **str);
char		**ft_joindstrs(char **ds1, char* *ds2);
char		**get_dstr(t_cmd *cmd);
void		adjust_shlvl(t_hold *env);
char		*data_analyse(char *str);
void		ft_lstadd_node(t_list **lst, t_list *new, int pos);
void		env_key_cmp(char *pwd, char *to_replace, void **lst_content, short *flg);
char		*prepare_pwd(void);
int     	stat_check(char *path);
int			d_point_pwd(char *path, char *pwd);
void		reset_env(char *pwd, char *o_pwd);
int			go_to_oldpwd(char *cwd, char *path);
short	valid_var(char *var);
////-/__________________________________________________________//-|
///-/                           EXEC                           //--|
//-/__________________________________________________________//---|
int		tt_pwd();
void	tt_echo(t_cmd *cmd);
void	tt_cd(t_cmd *cmd);
void	tt_unset(t_cmd *cmd);
void	tt_exit(t_cmd *cmd);
void	tt_env(t_cmd *cmd);
////-/__________________________________________________________//-|
///-/                        tt_cd_tools                       //--|
//-/__________________________________________________________//---|
int     stat_check(char *path);
void    reset_env(char *pwd, char *o_pwd);
char    *extend_option(char *arg, char *ex_with, int opt);
char    *get_prev_path(char *path);
int ft_go_to(int opt, char *path, char *cwd);
int     prev_drictory_count(char *wd);
////-/__________________________________________________________//-|
///-/                           SIGNALS                        //--|
//-/__________________________________________________________//---|
void	sig_handl();
void	sig_exec_init(void);
void	sig_here();
#endif