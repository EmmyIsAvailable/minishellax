#include "minishell.h"

char	*is_heredoc(char *deli)
{
	char	*tmp;
	int	heredoc;
	char	*buffer;

	tmp = NULL;
	buffer = NULL;
	heredoc = open("./tmp", O_WRONLY | O_CREAT, 0664);
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
	return ("./tmp");
}
