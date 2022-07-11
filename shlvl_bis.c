/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdaveux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:57:46 by cdaveux           #+#    #+#             */
/*   Updated: 2022/06/09 15:58:23 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_shlvl(t_data *data, char c)
{
	char	*new;
	char	*nb_shlvl;

	if (c == '+')
		data->shlvl++;
	else if (c == '-')
		data->shlvl--;
	nb_shlvl = ft_itoa(data->shlvl);
	new = ft_strjoin("SHLVL=", nb_shlvl);
	free(nb_shlvl);
	browse_data_var(new, data);
	free(new);
	return (0);
}

int	ft_cmp_line(char *history, char *str)
{
	int	i;

	i = jump_spaces(history, 0);
	if (ft_strncmp(&history[i], str, ft_strlen(str)) != 0)
		return (1);
	return (0);
}

char	*ft_shlvl(t_data *data, char *history, t_token **shlvl)
{	
	if (!history)
		write(STDERR_FILENO, "exit\n", 5);
	if ((data->shlvl == 1 && history == NULL) || (history && data->shlvl == 1
			&& ft_message(history, "exit") == 0))
		return (NULL);
	else if (history && ft_message(history, "./minishell") == 0)
		change_shlvl(data, '+');
	else if (data->shlvl > 1 && ((history && ft_message(history,
					"exit") == 0) || history == NULL))
		ft_prev_envp(shlvl, data);
	if (!history)
		return ("history");
	return (history);
}
