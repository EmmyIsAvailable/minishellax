#include "../minishell.h"

int	ft_bool(char *str)
{
	if (ft_strnstr(str, "export", ft_strlen(str)))
		return (0);
	if (ft_strnstr(str, "unset", ft_strlen(str)))
		return (1);
	return (-1);
}

void	moves(t_token *tmp, t_token *next_elem, t_token **shlvl)
{
	if (!tmp->prev)
	{
		if (next_elem)
			next_elem->prev = NULL;
		*shlvl = next_elem;
	}
	else if (!next_elem)
		(tmp->prev)->next = NULL;
	else
	{
		(tmp->prev)->next = next_elem;
		next_elem->prev = tmp->prev;
	}
}

void	ft_clear_shlvl(t_token **cmd, t_token **shlvl, t_token *cmp)
{
	t_token	*tmp;
	t_token	*next_elem;

	next_elem = NULL;
	tmp = *shlvl;
	while (tmp)
	{
		next_elem = tmp->next;
		if (!ft_strncmp(cmp->data, tmp->data, ft_name((*cmd)->next->data))
			&& cmp->shlvl == tmp->shlvl && ((tmp->cmd_env == 0
					&& cmp->cmd_env == 0) || (!cmp->cmd_env && tmp->cmd_env)))
		{
			moves(tmp, next_elem, shlvl);
			ft_lst_delone(tmp, free);
		}
		tmp = next_elem;
	}
}

void	create_shlvl_list(t_token **cmd, t_data *data, t_token **shlvl)
{
	t_token	*cmd_env;
	int		ex_or_unset;

	cmd_env = NULL;
	ex_or_unset = ft_bool((*cmd)->data);
	if ((ex_or_unset == 0 && ((*cmd)->next->data[ft_name((*cmd)->next->data)] == '='
			&& ft_isalpha((*cmd)->next->data[0])))
			|| (ft_search_env((*cmd)->next->data, data) && ex_or_unset == 1))
	{
		cmd_env = ft_create_token((*cmd)->next->token);
		if (!cmd)
			perror("malloc failed\n");
		cmd_env->data = ft_strdup((*cmd)->next->data);
		cmd_env->data_size = (*cmd)->next->data_size;
		cmd_env->shlvl = data->shlvl;
		cmd_env->cmd_env = ex_or_unset;
		ft_clear_shlvl(cmd, shlvl, cmd_env);
		if (*shlvl)
			(*shlvl)->prev = cmd_env;
		ft_lst_add(shlvl, cmd_env);
	}
}
