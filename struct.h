#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data {
	char	**envp;
	char	**var;
} t_data;

typedef struct s_token {
    token_type token; 
    char *data;
    size_t data_size;
	struct s_token *next;
} t_token;

#endif
