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

int	size_shlvl(t_token *shlvl)
{
	int len = 0;
	t_token *tmp;
	tmp= shlvl;
	if (tmp)
	{
		while (tmp)
		{
			tmp = tmp->next;
			len ++;
		}
	}
	return (len);
}
void	ft_clear_shlvl(t_token **cmd, t_token **shlvl, t_token *cmd_env)
{
	t_token *tmp;
	t_token	*to_erase;
	t_token	*previous;
	t_token	*next_elem;
	int		i = 0;

	to_erase = NULL;
	previous = NULL;
	next_elem = NULL;
	tmp = *shlvl;
	while (tmp != NULL)
	{
		to_erase = tmp->next;
		previous = tmp->prev;
		next_elem = tmp->next;
		if (!ft_strncmp(cmd_env->data, tmp->data, ft_name((*cmd)->next->data))
						&& cmd_env->shlvl == tmp->shlvl && (tmp->cmd_env == 0 && (*cmd)->cmd_env == 0)) // derniere condition peut varier en fonction de ce qu'on veut
		{
				if (!previous)
					(*shlvl) = next_elem;
				else if (!next_elem)
					previous->next= NULL;
				else
				{
					previous->next = next_elem;
					next_elem->prev = previous;
				}
				ft_lst_delone(tmp, free);
		}
		tmp = to_erase;
		i++;
	}
}

void	create_shlvl_list(t_token **cmd, t_data *data, t_token **shlvl)
{
	t_token	*cmd_env;
	int		ex_or_unset;

	cmd_env = NULL;
	ex_or_unset = ft_bool((*cmd)->data);
	if (ex_or_unset == 0 || (ft_search_env((*cmd)->next->data, data) && ex_or_unset))
	{
		cmd_env = ft_duplicate(&(*cmd)->next, data->shlvl, ex_or_unset);
		if (!cmd_env)
			clear_head(shlvl);
		ft_clear_shlvl(cmd, shlvl, cmd_env);
		if (*shlvl)
			(*shlvl)->prev = cmd_env;;
		ft_lst_add(shlvl, cmd_env);
	}
}
