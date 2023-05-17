READLINE_DIR = /Users/aelbrahm/.brew/opt/readline

SRC = src/minishell.c src/execute_line.c src/wild_cards.c src/read_line.c src/free_line.c src/destructors.c src/cd.c src/expand_line.c src/pwd.c src/export.c src/tt_unset.c src/tools.c src/tools2.c src/getters_setters.c src/expender.c src/complete_line.c src/constructors.c src/echo.c src/controll_line.c src/parsing_tools/parsing_tools.c src/parsing_tools/ft_split_char.c src/tokenizer/builtins_token.c src/tokenizer/cmds_token.c src/tokenizer/operators_token.c src/tokenizer/orders_token.c src/tokenizer/pipes_token.c src/tokenizer/redirections_token.c src/tokenizer/variables_token.c src/tokenizer/tokenizer_tools.c src/tokenizer/tokenize_line.c src/tokenizer/parenthesis_operators_token.c\
		src/executer/and_executer.c src/executer/cmd_executer.c src/executer/or_executer.c src/executer/pipe_executer.c src/executer/redir_executer.c src/executer/builtin_executer.c

HEADERS = include/minishell.h  include/dictionary.h  include/parsing.h  include/execute.h

CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))
# OBJ =  $(addprefix obj/, $(SRC))

NC   = '\e[0m'
HBLU = '\e[1;94m'

BIN_DIR = bin/
CFLAGS		=    -fsanitize=address

LIBRARIES	= -L${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include

NAME = minishell

all : ${NAME}

${NAME} : ${OBJ}
	make -C lib/libft
	cc ${CFLAGS} ${LIBRARIES} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

obj/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) ${INCLUDES} -c $< -o $@

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all

.PHONY : all re fclean clean 
.SILENT : all re fclean clean ${OBJ} ${NAME}