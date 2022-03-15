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
} t_data;

typedef struct s_token {
    token_type token; 
    char *data;
    size_t data_size;
	struct s_token *next;
} t_token;

#endif
