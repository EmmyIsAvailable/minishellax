#include "libft.h"

char	**ft_sort_tab(char **tab)
{
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j])
		{
			tmp = NULL;
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) < 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}
