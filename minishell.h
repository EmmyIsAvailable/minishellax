#ifndef MINISHELL_H
# define MINISHELL_H

/*_INCLUDE_*/

# include "./libft/libft.h"

//# include "define.h"
# include "enum.h"
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

/*_list_*/
void	ft_lst_clear(t_token **lst, void (*del)(void *));
void	ft_lst_add_back(t_token **alst, t_token *new);

/*_parsing_*/
void	ft_print(t_token *head);
int		ft_parse(char *str, t_token **head);

/*_main_*/
//int	main(int ac, char **av);

/*_exit_program_*/
void	sig_int(int code);
void	event_ctrl_c(void);

/*_builtins_cmd_*/
int	displayOnTerm(char *str);
int	ft_echo(t_token *token, t_data *data);
int	ft_pwd(void);
int	ft_env(t_data *data);
int	variables_in_echo(char *params, t_data *data);

/*builtins_dispatch*/
int	ft_unset(char **cmd, t_data *data);
void	add_var_envp(char *cmd, t_data *data);
int	ft_export(char **cmd, t_data *data);
int	dispatch_builtins(t_token *token, t_data *data);


#endif
