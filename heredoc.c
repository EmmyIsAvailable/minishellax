#include "minishell.h"

int	is_heredoc(char *deli, t_data *data)
{
	char	*tmp;
	int	heredoc;
	char	*buffer;

	tmp = NULL;
	buffer = NULL;
	heredoc = open(deli, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (heredoc < 0)
		perror("Heredoc failed");
	tmp = readline("> ");
	while (1)
	{
		if (buffer)
			buffer = ft_strjoin(buffer, "\n");
		if (tmp && ft_strncmp(tmp, deli, ft_strlen(deli) + 1) == 0)
			break;
		buffer = ft_strjoin(buffer, tmp);
		tmp = readline("> ");
	}
	env_in_heredoc(heredoc, buffer, data);
	close(heredoc);
	free(buffer);
	return (0);
}

char	*env_in_heredoc(int heredoc, char *buffer, t_data *data)
{
	int	i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	while (buffer[i])
	{
		tmp = NULL;
		while (buffer[i] && buffer[i] != '$')
		{
			write(heredoc, &buffer[i], 1);
			i++;
		}
		if (buffer[i] == '$')
		{
			i++;
			tmp = ft_search_env(&buffer[i], data);
			write(heredoc, tmp, ft_strlen(tmp));
		}
		i += ft_name(&buffer[i]);
	}
	return (ret);
}
