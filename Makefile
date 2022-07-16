NAME	= minishell

SRCS	= main.c exit_program.c shlvl.c shlvl_bis.c free.c\
		./builtins/builtins_cmd.c ./builtins/builtins_dispatch.c ./builtins/export_builtins.c \
		./builtins/unset_builtins.c ./builtins/check_error_builtins.c ./builtins/export_utils.c \
		./cmd.c pipex_chloe.c heredoc.c pipex_utils.c pipex_utils_bis.c\
		./parsing/parse.c ./parsing/cmd_line.c\
		./parsing/list.c ./parsing/recursive_parser.c \
		./parsing/parse_quotes.c ./parsing/pre_parsing.c \
		./parsing/split_bis.c ./parsing/split_env.c \
		./parsing/gestion_list_shlvl.c ./parsing/heads_init.c \
		./parsing/list_bis.c ./parsing/search_env.c \
		./parsing/parsing_utils.c

OBJS	= ${SRCS:.c=.o}

RM	= rm -f

CC	= gcc #-fsanitize=address

FLAGS	= -Wall -Wextra -Werror

LIBFT		= ./libft/libft.a

all:		${NAME}

.c.o:      
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${LIBFT} 
			@echo "$(shell tput bold)$(shell tput setaf 5)Compiling...$(shell tput sgr0)"
			@${CC} ${OBJS} -lreadline -o ${NAME} ${LIBFT} 
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

${LIBFT}:	
			@echo "$(shell tput bold)$(shell tput setaf 5)Building libft...$(shell tput sgr0)"
			@make -sC libft
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

clean:          
			@${RM} ${OBJS}
			@echo "$(shell tput bold)$(shell tput setaf 5)Deleting object files...$(shell tput sgr0)"
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

fclean:		clean
			@${RM} ${NAME}
			@echo "$(shell tput bold)$(shell tput setaf 5)Deleting binaries...$(shell tput sgr0)"
			@make fclean -sC ./libft 
			@echo "$(shell tput bold)$(shell tput setaf 5)Cleaning libft...$(shell tput sgr0)"
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

re:			fclean all

.PHONY:		all clean fclean re
