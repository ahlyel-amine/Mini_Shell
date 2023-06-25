READLINE_DIR = /Users/aahlyel/homebrew/opt/readline

SRC =	\
		\
		src/minishell.c  src/wild_cards.c src/wild_cards_tools.c src/read_line.c src/tokens_controll.c\
		src/tools.c src/tools2.c src/getters_setters.c src/getters_setters_tools.c src/complete_line.c src/controll_line.c\
		\
		\
		src/executer/builtin_executer.c src/executer/cmd_executer_tools.c src/executer/priorities_call.c src/executer/red_call_tools.c\
		src/executer/builtin_executer_tools.c src/executer/cmd_signals.c src/executer/priorities_call_helper.c\
		src/executer/cmd_executer.c src/executer/parse_cmd.c src/executer/priorities_call_tools.c\
		\
		\
		src/tokenizer/arguments_controll.c src/tokenizer/get_arguments.c src/tokenizer/variables_controll.c src/tokenizer/ft_split_str_to_args.c\
		src/tokenizer/translate_arguments.c src/tokenizer/translate_arguments2.c src/tokenizer/transform_arguments.c src/tokenizer/transform_arguments_tools.c\
		\
		\
		src/tokenize/tokenizer.c src/tokenize/tokenizer2.c src/tokenize/tokenize_checker.c\
		\
		\
		src/builtin/pwd.c src/builtin/env.c	src/builtin/cd.c src/builtin/export.c src/builtin/echo.c src/builtin/exit.c src/builtin/builtin_tools.c src/builtin/tt_unset.c\
		src/builtin/tt_cd_tools.c src/builtin/builtin_t2.c src/builtin/builtin_t3.c src/builtin/builtin_t1.c\
		\
		\
		src/parsing_tools/parsing_tools.c src/parsing_tools/parsing_tools2.c \
		src/parsing_tools/redirections_parser_tools.c src/parsing_tools/herdoc_parser_tools.c src/parsing_tools/herdoc_parser_tools2.c\
		\
		\
		src/expander/expand_line.c src/expander/tilde_expand.c \
		\
		\
		src/signal/signal.c src/signal/sig.c

HEADERS = include/minishell.h  include/dictionary.h  include/parsing.h include/executer.h   include/includes.h include/builtin.h   include/parsing_tools.h include/structs.h  include/tokenizer.h lib/libft/include/libft.h

CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))

NC			= '\e[0m'
HBLU		= '\e[1;94m'
BIN_DIR		= bin/
CFLAGS		= -Wall -Wextra -Werror 
# -fsanitize=address
LIBRARIES	= -L${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include
NAME		= minishell

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