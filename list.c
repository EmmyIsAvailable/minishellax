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
