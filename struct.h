#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data {
	char	**envp;
	char	**var;
	char	*oldpwd;
	char	*pwd;
	int	pipe0[2];
	int	pipe1[2];
	int	*pipes[2];
	int	shlvl;
	pid_t	last_pid;
} t_data;

typedef struct s_token
{
	token_type		token;
	char 			*data;
	size_t			data_size;
	int				fd;
	int				shlvl;
	int				cmd_env; // export = 0, unset = 1
	struct s_token	*next;
} t_token;

typedef struct s_heads
{
	t_token			*cmd;
	t_token			*infile;
	t_token			*outfile;
	struct s_heads	*next;
}t_heads;

#endif
