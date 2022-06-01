#include "../minishell.h"

int	ft_echo(t_token **token, t_data *data, t_heads **line)
{
	int		option;
	char	*str;

	option = 0;
	str = NULL;
	while ((*token) && check_option(token) == 0)
	{
		option = 1;
		ft_free(token);
	}
	if (!(*token))
		return (0);
	str = prep_data(str, (*token), data);
	if (option == 0)
		str = join_elems(str, "\n");
	write_outfile(line, str);
	free(str);
	return (0);
}

int	check_option(t_token **token)
{
	int	i;

	i = 1;
	if (ft_strncmp_len((*token)->data, "-n", 2) == 0)
		return (0);
	if ((*token)->data[0] == '-')
	{
		while ((*token)->data[i] == 'n')
			i++;
		if (i != 1 && (*token)->data[i] == '\0')
			return (0);
	}
	return (1);
}
