/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:52:47 by eruellan          #+#    #+#             */
/*   Updated: 2022/05/27 15:54:06 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data {
	char	**envp;
	char	**var;
	char	*oldpwd;
	char	*pwd;
	int		tmp_fd;
	int		pipes[2];
	int		shlvl;
	int		exit_status;
	pid_t	last_pid;
	pid_t	pid1;
}	t_data;

typedef struct s_token
{
	token_type		token;
	char			*data;
	size_t			data_size;
	int				fd;
	int				shlvl;
	int				cmd_env;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_heads
{
	t_token			*cmd;
	t_token			*infile;
	t_token			*outfile;
	struct s_heads	*next;
}	t_heads;

#endif
