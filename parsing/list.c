#include "../minishell.h"

void	ft_lst_delone(t_token *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->data);
		free(lst);
	}
}

void	ft_lst_clear(t_token **lst, void (*del)(void *))
{
	t_token	*temp;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lst_delone(*lst, del);
		(*lst) = temp;
	}
}

t_token	*ft_lst_last(t_token *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lst_add_back(t_token **alst, t_token *new)
{
	if (alst)
	{
		if (*alst != NULL)
			ft_lst_last(*alst)->next = new;
		else
			*alst = new;
	}
}

t_heads	*ft_last(t_heads *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst -> next;
	return (lst);
}

void	push(t_token **head, t_token **head_b)
{
	t_token	*tmp;
	t_token	*tmpb;

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
		ft_lst_last(tmpb)->next = (*head);
		(*head) = tmp;
	}
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

void	ft_free(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	(*head) = (*head)->next;
	free(tmp->data);
	free(tmp);
}

