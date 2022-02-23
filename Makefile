NAME	= minishell

SRCS	= main.c

OBJS	= ${SRCS:.c=.o}

RM	= rm -f

CC	= gcc 

FLAGS	= -Wall -Wextra -Werror

all:		${NAME}

.c.o:      
			@${CC} ${FLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${OBJS} 
			@echo "$(shell tput bold)$(shell tput setaf 5)Compiling...$(shell tput sgr0)"
			@${CC} ${OBJS} -o ${NAME}
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

clean:          
			@${RM} ${OBJS}
			@echo "$(shell tput bold)$(shell tput setaf 5)Deleting object files...$(shell tput sgr0)"
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

fclean:		clean
			@${RM} ${NAME}
			@echo "$(shell tput bold)$(shell tput setaf 5)Deleting binaries...$(shell tput sgr0)"
			@echo "$(shell tput bold)$(shell tput setaf 5)DONE$(shell tput sgr0)"

re:			fclean all

.PHONY:		all clean fclean re
