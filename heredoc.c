#include "minishell.h"

int	is_heredoc(char *deli)
{
	char	*tmp;
	int	heredoc;
	char	*buffer;

	tmp = NULL;
	buffer = NULL;
	heredoc = open(deli, O_WRONLY | O_RDONLY | O_CREAT, 0777);
	if (heredoc < 0)
		perror("Heredoc failed");
	tmp = readline("> ");
	while (1)
	{
		if (tmp && ft_strncmp(tmp, deli, ft_strlen(deli) + 1) == 0)
			break;
		buffer = ft_strjoin(buffer, tmp);
		buffer = ft_strjoin(buffer, "\n");
		tmp = readline("> ");
	}
	write(heredoc, buffer, ft_strlen(buffer));
	close(heredoc);
	return (0);
}
