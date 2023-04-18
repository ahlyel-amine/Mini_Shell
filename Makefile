
READLINE_DIR    = /Users/aahlyel/homebrew/opt/readline

SRC = src/minishell.c src/parsing/parsing_controll.c src/parsing/spliter.c src/parsing/spliter_handlers.c src/parsing_tools/parsing_tools.c 

OBJ =  ${SRC:.c=.o}


OBJ_DIR = obj/
BIN_DIR = bin/
FLAGS		= -Wall -Wextra -Werror -fsanitize=address
LIBRARIES	= -L ${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include
NAME = minishell

all : ${NAME}

${NAME} : ${OBJ_DIR} ${OBJ}
	make -C lib/libft
	cc ${FLAGS} ${LIBRARIES} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

${OBJ_DIR} : 
	mkdir -p ${OBJ_DIR} ${BIN_DIR}

obj/%.o : ${SRC} include/minishell.h
	cc ${FLAGS} ${INCLUDES} -c ${SRC} -o ${OBJ}

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ} ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all