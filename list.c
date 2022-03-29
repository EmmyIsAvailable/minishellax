#include "minishell.h"

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

t_heads	*ft_last(t_heads *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_heads **alst, t_heads *new)
{
	if (*alst)
	{
		if (alst)
			ft_last(*alst)->next = new;
		else
			*alst = new;
	}
}

void	ft_lst_add_back(t_token **alst, t_token *new)
{
	if (alst)
	{
		if (*alst)
			ft_lst_last(*alst)->next = new;
		else
			*alst = new;
	}
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
	else //on veut push in the back : essai ne marche pas
	{
		/*tmpb = (*head_b);
		while (tmpb->next != NULL)
			tmpb = tmpb->next;
		tmpb->next = (*head);
		(*head) = tmp;*/
		tmpb = (*head_b);
		(*head_b) = (*head);
		(*head_b)->next = tmpb;
		(*head) = tmp;
	}
}
