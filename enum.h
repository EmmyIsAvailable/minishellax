#ifndef ENUM_H
# define ENUM_H

typedef enum {
	SPACE,
	PIPE,
	DOLLAR_SIGN,
	DOUBLE_QUOTE,
	SIMPLE_QUOTE,
	REDIR_IN,
	REDIR_OUT,
	PLUS,
	MINUS, 
	DIV,
	MULTI,
	MODULO,
	EQ,
	DOUBLE_GREATER,
	HEREDOC,
	WORD,
//	WORD_ASSIGNMENT : ou juste mettre WORD=WORD || WORD= 
} token_type;

#endif
