#include "../minishell.h"

int	ft_parse(char *str, t_token **head, t_data *data)
{
	int		i;
	int		io_here_flag;
	int		space;
	t_token	*tmp;
	t_heads *line;

	i = 0;
	io_here_flag = 0;
	tmp = NULL;
	line = NULL;
	while (str[i])
	{
		space = i;
		while (str[i] && (str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
				|| str[i] == '\r' || str[i] == '\f' || str[i] == 32))
			i++;
		if (str[i] == '\0')
			break;
		if (space != i && space != 0)
		{
			tmp = fill_data(SPACE, 1, " ", data);
			ft_lst_add_back(head, tmp);
		}
		tmp = scan_token(&str[i], io_here_flag, data);
		if (!tmp)
		{
			ft_lst_clear(head, free);
			return (1);
		}
		printf("data : %s_\n", tmp->data);
		if (tmp->token != 32)
		{
			if (tmp->token == 8)
				io_here_flag = 1;
			else
				io_here_flag = 0;
		}
		ft_lst_add_back(head, tmp);
		i += (int)tmp->data_size;
	}
	ft_print(*head);
	if (!(*head))
		return (0);
	else
		return (cmd_line_building(head, &line, data));
}
