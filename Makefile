READLINE_DIR = /Users/aahlyel/homebrew/opt/readline
# READLINE_DIR = /Users/aelbrahm/.brew/opt/readline
#	SRC			row 1 : src/		row 2 : src/parsing_tools/		row 3 : src/parsing/			row 4 : src/executer/			row 5 : src/tokenizer/		row 5 : src/builtin/
SRC =	\
		\
		src/minishell.c src/execute_line.c src/wild_cards.c src/read_line.c src/free_line.c src/expand_line.c \
		src/tools.c src/tools2.c src/signal.c src/getters_setters.c src/complete_line.c src/controll_line.c\
		\
		src/tree_tools/destructors2.c src/tree_tools/destructors.c src/tree_tools/constructors.c src/tree_tools/constructors2.c\
		\
		src/parsing_tools/parsing_tools.c src/parsing_tools/parsing_tools2.c \
		src/parsing_tools/redirections_parser_tools.c src/parsing_tools/redirections_parser_tools2.c src/parsing_tools/redirections_parser_tools3.c src/parsing_tools/redirections_parser_tools4.c\
		\
		\
		src/parsing/and_parser.c src/parsing/builtins_parser.c src/parsing/cmds_parser.c src/parsing/executable_parser.c src/parsing/or_parser.c \
		src/parsing/parenthisise_controll.c src/parsing/pipe_parser.c src/parsing/parse_line.c \
		src/parsing/redirections_parser.c src/parsing/check_parsing.c\
		src/parsing/redirections_parenthesis_parser.c src/parsing/redirect_before_parenthesis.c src/parsing/redirect_after_parenthesis.c\
		\
		\
		src/executer/and_executer.c src/executer/cmd_executer.c src/executer/or_executer.c src/executer/pipe_executer.c src/executer/redir_executer.c \
		src/executer/builtin_executer.c src/executer/cmd_signals.c\
		\
		\
		src/tokenizer/arguments_controll.c src/tokenizer/get_arguments.c src/tokenizer/variables_controll.c src/tokenizer/ft_split_str_to_args.c\
		src/tokenizer/translate_arguments.c src/tokenizer/translate_arguments2.c src/tokenizer/transform_arguments.c src/tokenizer/transform_arguments_tools.c\
		\
		\
		src/builtin/pwd.c src/builtin/env.c	src/builtin/cd.c src/builtin/export.c src/builtin/echo.c src/builtin/exit.c src/builtin/builtin_tools.c src/builtin/tt_unset.c\
		src/builtin/tt_cd_tools.c src/builtin/builtin_t2.c src/builtin/builtin_t3.c\

HEADERS = include/minishell.h  include/dictionary.h  include/parsing.h  include/execute.h

CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))
# OBJ =  $(addprefix obj/, $(SRC))

NC   = '\e[0m'
HBLU = '\e[1;94m'

BIN_DIR = bin/
CFLAGS		= 
#   -fsanitize=address

LIBRARIES	= -L${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include

NAME = minishell

all : ${NAME}

${NAME} : ${OBJ}
	make -C lib/libft
	cc -g ${CFLAGS} ${LIBRARIES} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

obj/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) -g $(CFLAGS) ${INCLUDES} -c $< -o $@

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all

.PHONY : all re fclean clean 
.SILENT : all re fclean clean ${OBJ} ${NAME}