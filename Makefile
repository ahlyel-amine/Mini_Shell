READLINE_DIR = /Users/aahlyel/homebrew/opt/readline

#	SRC			row 1 : src/		row 2 : src/parsing_tools/		row 3 : src/parsing/			row 4 : src/executer/			row 5 : src/tokenizer/		row 5 : src/builtin/
SRC =	\
		\
		src/minishell.c src/execute_line.c src/wild_cards.c src/read_line.c src/free_line.c src/destructors.c src/expand_line.c \
		src/tools.c src/tools2.c src/getters_setters.c src/expender.c src/complete_line.c src/constructors.c src/controll_line.c\
		\
		\
		src/parsing_tools/parsing_tools.c src/parsing_tools/ft_split_char.c  \
		\
		\
		src/parsing/and_parser.c src/parsing/builtins_parser.c src/parsing/cmds_parser.c src/parsing/executable_parser.c src/parsing/or_parser.c \
		src/parsing/parenthisise_controll.c src/parsing/parsing_tools.c src/parsing/pipe_parser.c src/parsing/parse_line.c \
		src/parsing/redirections_parser_tools.c src/parsing/redirections_parser.c\
		\
		\
		src/executer/and_executer.c src/executer/cmd_executer.c src/executer/or_executer.c src/executer/pipe_executer.c src/executer/redir_executer.c \
		src/executer/builtin_executer.c\
		\
		\
		src/tokenizer/arguments_controll.c src/tokenizer/get_arguments.c src/tokenizer/variables_controll.c src/tokenizer/ft_split_str_to_args.c \
		\
		\
		src/builtin/pwd.c src/builtin/cd.c src/builtin/export.c src/builtin/echo.c src/builtin/exit.c src/builtin/tt_unset.c\

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