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

int    add_var_envp(char *str, t_data *data)
{
        int     i;
        char    **envp;

        i = 0;
        envp = data->envp;
        while (envp[i])
                i++;
	envp[i] = ft_strdup(str);
	if (!envp[i])
		return (1);
        envp[i + 1] = NULL;
	return (0);
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

int	check_assign(char *assignment)
{
	int	i;
	int	eq_sign;

	i = 0;
	eq_sign = 0;
	if (ft_isalpha(assignment[i]) == 0 && assignment[i] != '_')
		return (1);i
	while (assignment[++i])
	{
		if (assignment[i] == '=')
			eq_sign = 1;
	}
	if (eq_sign != 1)
		return (1);
	return (0);
}

int     ft_export(t_token *token, t_data *data)
{
	t_token	*tmp;

	tmp = token;
        while (tmp)
        {
                if (check_assign(tmp->data) == 0)
		{
                	/*si la variable existe deja dans l'envp remplacer ancienne valeur par nouvelle*/
			add_var_envp(tmp->data, data);
                }
		tmp = tmp->next;
        }
        return (0);
}

