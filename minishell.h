/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eruellan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:19:38 by eruellan          #+#    #+#             */
/*   Updated: 2022/06/21 10:56:41 by cdaveux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*_INCLUDE_*/

# include "./libft/libft.h"
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

extern int	g_global;

/*_RACINE_*/

/*parsing_utils*/
int		error_msg(int type, char *str);
char	*ft_dup(char *data, int i, int diff, char *str);
void	ft_print(t_token *head);
void	ft_print_line(t_heads **line);
t_token	*ft_create_token(t_type token);

/*_cmd_line_*/
int		check_token(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);
int		cmd_line(t_token **head, t_heads **line, t_data *data, t_token **shlvl);
int		join_data(t_token **tmp);

/*_gestion_shlvl_list_*/
void	create_shlvl(int count, t_token **cmd, t_data *data, t_token **shlvl);
void	ft_clear_shlvl(t_token **cmd, t_token **shlvl, t_token *cmp);

/*_heads_init_*/
t_heads	*tmp_init(void); //malloc
void	push_heads(t_heads **head, t_heads **head_b);
void	free_elem_heads(t_heads **lst);
int		clear_all_heads(t_heads **lst);

/*_list_*/
t_token	*ft_lst_last(t_token *lst);
void	ft_lst_add_back(t_token **alst, t_token *new);
void	ft_lst_add(t_token **alst, t_token *new);
void	push(t_token **head, t_token **head_b);
t_token	*fill_data_exit(t_type token, int len, t_data *data);

/*_list_bis_*/
void	ft_lst_delone(t_token *lst, void (*del)(void *));
void	ft_lst_clear(t_token **lst, void (*del)(void *));
int		clear_head(t_token **head);
void	ft_free(t_token **head);
char	*ft_create_data(char *str, int i);

/*_parse_*/
t_token	*scan_token(char *str, int io_here, t_data *data);
t_token	*fill_data(t_type token, int len, char *op, t_data *data);

/*_search_env_*/
int		ft_name(char *str);
char	*ft_search_env(char *params, t_data *data);
int		ft_heredoc(t_token *tmp);

/*_parse_quotes_*/
t_token	*fill_data_quotes(t_type token, char *str, char op, t_data *data);
int		find_op(char *str, char op);

/*_pre_parsing_*/
int		jump_spaces(char *str, int i);
int		ft_parse(char *str, t_token **head, t_data *data, t_token **shlvl);
void	create_tokens(char *str, t_token **head, t_data *data, int h_flag);

/*_split_bis_*/
char	**ft_split_bis(char const *s, char *c);

/*_split_env*/
t_token	*split_env(t_token *new_token, char *op, t_data *data);

/*_recusive_parsing*/
int		check_inf(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);
int		check_out(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);
int		check_out_b(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);
int		check_word(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);
int		check_here(t_token **tmp, t_token **inf, t_token **out, t_token **cmd);

/*_main_*/
int		ft_cmp_line(char *history, char *str);
char	*ft_shlvl(t_data *data, char *history, t_token **shlvl);
int		change_shlvl(t_data *data, char c);
int		minishell(t_data *data, t_token *head, t_token *shlvl);

/*_exit_program_*/
void	sig_int(int code);
void	sig_int2(int code);
int		event_ctrl_c(int i);
int		ft_message(char *history, char *str);
int		ft_message_bis(char **tab);
int		ft_exit_message(int i, t_heads **line);

/*_free_*/
int		init_envp(t_data *data, char **envp);
int		free_tab(char **tab);
char	*join_elems(char *str, char *to_add);
char	*prep_data(char *str, t_token *token);
int		check_exit_args(char *arg);

/*_builtins_cmd_*/
int		ft_pwd(void);
int		ft_env(t_data *data);
int		ft_echo(t_token **token);
int		check_option(t_token **token);

/*_pipex_*/
int		ft_pipex(t_data *data, t_heads **final_line, int i);
void	parent(t_data *data, t_heads **line);
int		child(t_data *data, t_heads **line);
int		ft_exit(t_heads **line);

/*_pipex_utils_bis_*/
int		count_token(t_token *token);
void	close_fds(t_data *data);
void	event_signal(void);
void	sig_slash(int code);

/*_builtins_dispatch_*/
int		is_builtin(t_heads **line, t_data *data);
int		dispatch_builtins(t_heads **line, t_data *data);
int		ft_cd(t_heads **line, t_data *data, int ret);
char	*ft_value(t_data *data, char *str);
void	change_pwd(int i, t_data *data, char *str);
//int		non_printable_builtins(t_heads **line, t_data *data);
//int		is_non_print_builtins(t_token *token);

/*_check_error_builtins_*/
int		error_export(t_token *token);
int		error_cd(t_token *token);
int		check_error_builtins(t_token *token);
//int		non_print(t_heads **line, t_heads **final_line, t_data *data);

/*_export_builtins_*/
int		ft_export(t_token *token, t_data *data);
int		ft_solo_export(t_data *data);

/*_export_utils_*/
int		browse_data_var(char *str, t_data *data);
int		add_var_envp(char *str, t_data *data);
int		check_assign(char *assignment);
char	**clean_envp(t_data *data);

/*_unset_builtins_*/
int		check_existence(char *str, char *env);
int		check_unset(char *str);
char	**ft_exec_unset(t_token *token, char **envp);
int		ft_unset(t_token *token, t_data *data);

/*_cmd_*/
int		ft_exec(t_token *token, t_data *data);
char	*get_binary(char *cmd, char **env_path);
char	**fill_token_tab(t_token *token);
char	*pass_path(t_token *token);
char	*check_path_cmd(char *cmd);

/*_pipex_utils_*/
int		check_infile(t_heads **line);
int		check_infile_bis(t_heads **line);
int		check_outfile(t_heads **line);
int		check_outfile_bis(t_heads **line);
//int		ft_no_fork(t_heads **line, t_data *data, t_heads **final_line);
//int		no_binary(t_heads **line, t_heads **final_line, t_data *data);

/*_heredoc_*/
int		is_heredoc(char *deli, t_data *data);
int		ft_close_heredoc(int heredoc, char *buffer);
char	*env_in_heredoc(int heredoc, char *buffer, t_data *data);
int		check_heredoc(t_heads **line, t_data *data);

/*_shlvl_*/
int		ft_prev_envp(t_token **shlvl, t_data *data);
int		ft_prev_envp_bis(t_token *tmp, t_token *tmp2, t_data *data);
int		ft_export_prev(char *str, t_token *shlvl, t_data *data);
int		ft_unset_prev(char *str, t_data *data);
void	ft_exec_unset_prev(char *to_export, char **envp);

#endif
