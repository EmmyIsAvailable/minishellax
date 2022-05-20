#include "./minishell.h"

char	*join_elems(char *str, char *to_add)
{
	char	*tmp;

	tmp = NULL;
	if (str)
	{
		tmp = ft_strdup(str);
		free(str);
		str = NULL;
	}
	str = ft_strjoin(tmp, to_add);
	free(tmp);
	tmp = NULL;
	return (str);
}

char	*prep_data(char *str, t_token *token, t_data *data)
{
	char	*exit_value;
	t_token	*tmp;
	
	exit_value = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->token == ECHO)
		{
			exit_value = ft_itoa(data->exit_status);
			str = join_elems(str, exit_value);
			free(exit_value);
		}
		else	
			str = join_elems(str, tmp->data);
		if (tmp->next)
			str = join_elems(str, " ");
		tmp = tmp->next;
	}
	return (str);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (0);
}


