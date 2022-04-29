#include "../minishell.h"

void	ft_free(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	free(tmp->data);
	free(tmp);
}

void	clear_head(t_token **head)
{
	while ((*head) && (*head)->token != 0)
		ft_free(head);
	ft_free(head);
}

int	ft_bool(char *str)
{
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (1);
	return (-1);
}

t_token	*ft_duplicate(t_token **cmd, int shell_lvl, int cmd_env)
{
	t_token	*new;

	new = ft_create_token((*cmd)->token);
	if (!new)
		return (NULL);
	new->data = ft_strdup((*cmd)->data);
	new->data_size = (*cmd)->data_size;
	new->shlvl = shell_lvl;
	new->cmd_env = cmd_env;
	return (new);
}

void	create_shlvl_list(t_token **cmd, t_data *data, t_token **shlvl)
{
	t_token	*cmd_env;

	cmd_env = NULL;
	if (ft_bool((*cmd)->data) != -1)
	{
		cmd_env = ft_duplicate(cmd, data->shell_lvl, ft_bool((*cmd)->data));
		if (!cmd_env)
			clear_head(shlvl);
		cmd_env->prev = ft_lst_last(*shlvl);
		ft_lst_add(shlvl, cmd_env);
	}
}
