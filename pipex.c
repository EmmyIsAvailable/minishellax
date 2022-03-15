#include "minishell.h"

void	**ft_free_tab(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		free(data[i]);
		data[i] = NULL;
	}
	return (NULL);
}

int	ft_error(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}
char    *get_binary(char *cmd, char **env_path)
{
        char    *tmp;
        char    *cmd_path;
        int             i;

        i = -1;
        tmp = NULL;
        cmd_path = NULL;
        while (env_path[++i])
        {
                tmp = ft_strjoin(env_path[i], "/");
                if (!tmp)
                        ft_error("Join failed");
                cmd_path = ft_strjoin(tmp, cmd);
                if (!cmd_path)
                        ft_error("Cmd_path join failed");
                free(tmp);
                if (access(cmd_path, F_OK) == 0)
                        return (cmd_path);
                free(cmd_path);
        }
        ft_error("Command not found");
        return (NULL);
}

void    ft_exec(char *av, t_data *data)
{
        char    **env_path;
        char    *binary;
        char    **cmd;

        cmd = ft_split(av, ' ');
        if (!cmd)
                ft_error("Split failed");
        env_path = ft_split(getenv("PATH"), ':');
        binary = get_binary(cmd[0], env_path);
        ft_free_tab(env_path);
        if (!binary)
                ft_error("Getting binary file failed");
        if (execve(binary, cmd, data->envp) == -1)
        {
                free (binary);
                ft_free_tab(cmd);
                ft_error("Error");
        }
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	t_data data;
	int	status;

	i = 2;
	if (ac < 3)
		return (ft_error("Wrong number of arguments"));
	data.envp = envp;
	data.pipes[0] = data.pipe0;
	data.pipes[1] = data.pipe1;
	pipe(data.pipes[0]);
	if (fork() == 0)
	{
		dup2(data.pipes[0][1], 1);
		close(data.pipes[0][0]);
		ft_exec(av[1], &data);
	}
	close(data.pipes[0][1]);
	while (av[i + 1])
	{
		pipe(data.pipes[1]);
		if (fork() == 0)
		{
			dup2(data.pipes[0][0], 0);
			dup2(data.pipes[1][1], 1);
			close(data.pipes[1][0]);
			ft_exec(av[i], &data);
		}
		close(data.pipes[0][0]);
		close(data.pipes[1][1]);
		i++;
	}
	if (fork() == 0)
	{
		dup2(data.pipes[1][0], 0);
		ft_exec(av[i], &data);
	}
	close(data.pipes[1][0]);
	while (wait(&status) != -1) {};
	return (0);
}
