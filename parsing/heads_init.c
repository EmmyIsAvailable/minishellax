#include "../minishell.h"

void	free_elem_heads(t_heads **lst)
{
	t_heads *tmp;

	tmp  = *lst;
	if ((*lst))
	{
		if ((*lst)->next)
			*lst = (*lst)->next;
		else 
			*lst = NULL;
		if (tmp->cmd)
			ft_lst_clear(&tmp->cmd, free);
		if (tmp->infile)
			ft_lst_clear(&tmp->infile, free);
		if (tmp->outfile)
			ft_lst_clear(&tmp->outfile, free);
	}
	free(tmp);
}

void	clear_all_heads(t_heads **lst)
{
	t_heads	*tmp;

	tmp = *lst;
	while (tmp)
	{
		(*lst) = (*lst)->next;
		free_elem_heads(&tmp);
		tmp = *lst;
	}
}

t_heads	*ft_last(t_heads *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	push_heads(t_heads **head, t_heads **head_b)
{
	t_heads	*tmp;
	t_heads	*tmpb;

	if (*head == NULL)
		return ;
	tmpb = NULL;
	tmp = (*head)->next;
	if (*head_b == NULL)
	{
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
	else
	{
		tmpb = (*head_b);
		(*head)->next = NULL;
		ft_last(tmpb)->next = (*head);
		(*head) = tmp;
	}
}

t_heads	*tmp_init(void)
{
	t_heads	*tmp;

	tmp = malloc(sizeof(t_heads));
	if (!tmp)
		return (NULL);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->cmd = NULL;
	return (tmp);
}
