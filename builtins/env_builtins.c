#include "../minishell.h"

int     ft_unset(char **cmd, t_data *data)
{
        char    **envp;
        int     i;
        int     j;

        j = 0;
        envp = data->envp;
        while (cmd[++j])
        {
                i = -1;
                while (envp[++i])
                {
                        if (ft_strncmp(&envp[i][ft_strlen(cmd[j])], "=", 1) == 0)
                        {
                                if (ft_strncmp(envp[i], cmd[j], ft_strlen(cmd[j])) == 0)
                                {
                                        while (envp[i])
                                        {
                                                envp[i] = envp[i + 1];
                                                i++;
                                        }
                                }
                        }
                }
        }
        return (0);
}

void    add_var_envp(char *cmd, t_data *data)
{
        int     i;
        char    **envp;

        i = 0;
        envp = data->envp;
        while (envp[i])
                i++;
        envp[i] = cmd;
        envp[i + 1] = NULL;
}

int     browse_data_var(char *cmd, t_data *data)
{
        int     i;

        i = 0;
        while (data->var[i])
        {
                if (ft_strncmp(data->var[i], cmd, ft_strlen(cmd)) == 0)
                {
                        add_var_envp(data->var[i], data);
                        return (0);
                }
                i++;
        }
        return (0);
}

int     ft_export(char **cmd, t_data *data)
{
        int     i;
        int     j;
        int     is_var;

        i = 1;
        while (cmd[i])
        {
                j = 1;
                is_var = 0;
                while (cmd[i][j])
                {
                        if (cmd[i][j] == '=' && cmd[i][j + 1] != '\0')
                                is_var = 1;
                        j++;
                }
                if (is_var == 0)
                        browse_data_var(cmd[i], data);
                if (is_var == 1)
                        add_var_envp(cmd[i], data);
                i++;
        }
        return (0);
}

