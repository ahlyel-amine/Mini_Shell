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
char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		count;

	count = -1;
	while (ft_isspace(*(char *)(s1)))
		s1++;
	dst = (char *)ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (*(char *)(s1 + ++count))
		*(dst + count) = *(char *)(s1 + count);
	return (dst);
}

int main()
{
    printf("%s\n", "var");
}