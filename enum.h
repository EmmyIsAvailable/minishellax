#ifndef ENUM_H
# define ENUM_H

typedef enum {
	PIPE,
	DOLLAR_SIGN,
	DOUBLE_QUOTE,
	SIMPLE_QUOTE,
	REDIR_IN,
	REDIR_OUT,
	ASSIGN,
	DOUBLE_GREATER,
	HEREDOC,
	WORD
} token_type;

#endif
