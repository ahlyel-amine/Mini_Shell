
READLINE_DIR    = /Users/aahlyel/homebrew/opt/readline

SRC = src/minishell.c src/constructors.c  src/echo.c src/parsing/parsing_controll.c src/parsing/translater.c src/parsing/spliter.c src/parsing/tokenizer.c src/parsing/heredoc_controll.c src/parsing/spliter_handlers.c src/parsing/not_complete_line_checker.c src/parsing_tools/parsing_tools.c src/parsing_tools/parsing_tools2.c

OBJ =  ${SRC:.c=.o}


OBJ_DIR = obj/
BIN_DIR = bin/
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
LIBRARIES	= -L ${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include
NAME = minishell

all : ${NAME}

${NAME} : ${OBJ_DIR} ${OBJ}
	make -C lib/libft
	cc ${CFLAGS} ${LIBRARIES} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

${OBJ_DIR} : 
	mkdir -p ${OBJ_DIR} ${BIN_DIR}

obj/%.o : ${SRC} include/minishell.h
	cc ${CFLAGS} ${INCLUDES} -c ${SRC} -o ${OBJ}

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ} ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all