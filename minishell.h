/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:38 by eruellan          #+#    #+#             */
/*   Updated: 2022/04/07 12:04:47 by eruellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*_INCLUDE_*/

# include "./libft/libft.h"

//# include "define.h"
# include "parsing/enum.h"
# include "struct.h"


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/*_RACINE_*/

/*_supp later_*/
void	ft_print(t_token *head);
void	ft_print_line(t_heads **line);

/*_list_*/
void	ft_lst_clear(t_token **lst, void (*del)(void *));
void	ft_lst_add_back(t_token **alst, t_token *new);
void	push(t_token **head, t_token **head_b);
void	push_heads(t_heads **head, t_heads **head_b);
void	ft_free(t_token **head);

/*_parsing_*/
int	ft_parse(char *str, t_token **head, t_data *data);//parse
int	check_token(t_token **head, t_token **infile, t_token **outfile, t_token **cmd);//recursive_parser
int	cmd_line_building(t_token **head, t_heads **line, t_data *data); //cmd_line

/*_recusive_parsing*/
int	check_quote(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_word(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_infile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_outfile(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
int	check_dollar(t_token **tmp, t_token **infile, t_token **outfile, t_token **cmd);
//int	check_heredoc(t_token *tmp, t_heads *list);

/*_main_*/
//int	main(int ac, char **av);
int	init_envp(t_data *data, char **envp);

/*_exit_program_*/
void	sig_int(int code);
void	event_ctrl_c(void);

/*_builtins_cmd_*/
int	displayOnTerm(char *str);
int	ft_echo(t_token *token, t_data *data);
int	ft_pwd(void);
int	ft_env(t_data *data);
int	variables_in_echo(char *params, t_data *data);

/*_builtins_dispatch_*/
int	dispatch_builtins(t_token *token, t_data *data);
int	ft_cd(t_token *token, t_data *data);

/*_env_builtins_*/
int	ft_unset(char **cmd, t_data *data);
int	add_var_envp(char *str, t_data *data);
int	ft_export(t_token *token, t_data *data);

/*_cmd_*/
void	ft_exec(t_token *token, t_data *data);
void	**ft_free_tab(char **data);
char	*get_binary(char *cmd, char **env_path);
char	**fill_token_tab(t_token *token);

/*_pipex_*/
void	ft_wait(t_data *data);
int	ft_pipex(t_heads **line, t_data *data);
int	ft_pipex_bis(t_heads **line, t_data *data);
int	multiple_pipes(t_heads **line, t_data *data);

#endif
