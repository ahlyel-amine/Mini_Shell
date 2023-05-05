#include "include/minishell.h"

char    *replace_str(char *var, char *lst_cnt)
{
    char    *tmp;
    char    *expand;
    size_t     var_len = ft_strlen(var);
    size_t     lst_len = ft_strlen(lst_cnt);

    tmp = var;
    expand = ft_substr(lst_cnt, var_len + 1, (lst_len - var_len));
    // free(var);
    return (expand);
}
int main()
{
    printf("%s\n", "var");
}