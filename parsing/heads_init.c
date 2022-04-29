#include "../minishell.h"

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
