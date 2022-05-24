#include "libft.h"

static int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrimone(char *str, char c)
{
	char	*ret;
	int		i;

	i = 0;
	if (ft_check(str, c) == 0)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		ret[i] = str[i];
		i++;
	}
	if (str[i] == c)
		i++;
	while (str[i])
	{
		ret[i - 1] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
