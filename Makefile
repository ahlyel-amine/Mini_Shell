READLINE_DIR = /Users/aahlyel/homebrew/opt/readline
# READLINE_DIR = /Users/aelbrahm/.brew/opt/readline
#	SRC			row 1 : src/		row 2 : src/parsing_tools/		row 3 : src/parsing/			row 4 : src/executer/			row 5 : src/tokenizer/		row 5 : src/builtin/		row 6 : src/expander
SRC =	\
		\
		src/minishell.c  src/wild_cards.c src/read_line.c src/tokens_controll.c\
		src/tools.c src/tools2.c src/getters_setters.c src/complete_line.c src/controll_line.c\
		\
		\
		src/executer/builtin_executer.c  src/executer/cmd_signals.c  src/executer/priorities_call.c src/executer/priorities_call_tools.c\
		src/executer/priorities_call_helper.c\
		\
		\
		src/tokenize_tools/arguments_controll.c src/tokenize_tools/get_arguments.c src/tokenize_tools/variables_controll.c src/tokenize_tools/ft_split_str_to_args.c\
		src/tokenize_tools/translate_arguments.c src/tokenize_tools/translate_arguments2.c src/tokenize_tools/transform_arguments.c src/tokenize_tools/transform_arguments_tools.c\
		\
		\
		src/tokenize/tokenizer.c src/tokenize/tokenizer2.c src/tokenize/tokenize_checker.c\
		\
		\
		src/builtin/pwd.c src/builtin/env.c	src/builtin/cd.c src/builtin/export.c src/builtin/echo.c src/builtin/exit.c src/builtin/builtin_tools.c src/builtin/tt_unset.c\
		src/builtin/tt_cd_tools.c src/builtin/builtin_t2.c src/builtin/builtin_t3.c src/builtin/builtin_t1.c\
		src/parsing_tools/parsing_tools.c src/parsing_tools/parsing_tools2.c \
		src/parsing_tools/redirections_parser_tools.c src/parsing_tools/redirections_parser_tools2.c \
		src/expander/expand_line.c src/expander/tilde_expand.c \
		src/signal/signal.c src/signal/sig.c

HEADERS = include/builtin.h include/dictionary.h include/execute.h include/executer.h include/includes.h include/minishell.h include/parsing.h include/parsing_tools.h include/structs.h include/tokenizer.h

CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))
# OBJ =  $(addprefix obj/, $(SRC))

NC   = '\e[0m'
HBLU = '\e[1;94m'

BIN_DIR = bin/
CFLAGS		=    
#    -fsanitize=address

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