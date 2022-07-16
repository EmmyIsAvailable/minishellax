/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:24:43 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/09 15:49:45 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*builtins : env, pwd, echo*/

int	ft_env(t_data *data)
{
	int		i;
	char	*env;

	i = 0;
	env = NULL;
	while (data->envp[i])
	{
		env = join_elems(env, data->envp[i]);
		env = join_elems(env, "\n");
		i++;
	}
	write(1, env, ft_strlen(env));
	free(env);
	return (0);
}

void	change_pwd(int i, t_data *data, char *str)
{
	char	*new;
	char	*cwd;

	new = NULL;
	if (!str)
		cwd = getcwd(NULL, 0);
	else
		cwd = str;
	if (i == 1)
		new = ft_strjoin("OLDPWD=", cwd);
	else if (i == 2)
		new = ft_strjoin("PWD=", cwd);
	browse_data_var(new, data);
	free(new);
	free(cwd);
}

int	ft_pwd(void)
{
	char	*pwd;
	char	*cwd;

	pwd = NULL;
	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin(cwd, "\n");
	free(cwd);
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	return (0);
}

int	ft_echo(t_token **token)
{
	int		option;
	char	*str;

	option = 0;
	str = NULL;
	while ((*token) && check_option(token) == 0)
	{
		option = 1;
		ft_free(token);
	}
	if (!(*token))
		return (0);
	str = prep_data(str, (*token));
	if (option == 0)
		str = join_elems(str, "\n");
	write(1, str, ft_strlen(str));
	free(str);
	return (0);
}

int	check_option(t_token **token)
{
	int	i;

	i = 1;
	if (ft_strncmp_len((*token)->data, "-n", 2) == 0)
		return (0);
	if ((*token)->data[0] == '-')
	{
		while ((*token)->data[i] == 'n')
			i++;
		if (i != 1 && (*token)->data[i] == '\0')
			return (0);
	}
	return (1);
}
