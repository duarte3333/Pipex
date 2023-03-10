NAME = pipex
CC = cc
CFLAGS = -O3 -Wall -Wextra #-fsanitize=address -g

# ANSI color codes
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
BOLD=\033[1m
UNDERLINE=\033[4m
RESET=\033[0m
bold_green=\033[1;32m
yellow_bg=\033[43m

SRCS = main.c \
	   Aux/ft_atoi.c \
	   Aux/ft_split.c \
	   Aux/ft_strlen.c \
	   Aux/ft_strjoin.c \
	   Aux/lists_aux.c \
	   Aux/lists_aux2.c \
	   path.c

OBJS	= ${SRCS:.c=.o}



#-c: This is a flag that tells the compiler to compile 
#	 the source file into an object file, without linking 
#	 it to other object files or libraries.
#$@: Is the name of the output file that this rule will create. 
#	 In this case, it's the name of the object file being created.
#$<: Contains the name of the first dependency of the rule, which is the name of the source file being compiled. 
%.o: %.c pipex.h
	@$(CC) -c $(CFLAGS) -o $@ $< 
	@echo "$(YELLOW)[COMPILED]	"$<"$(RESET)"

all: fingers $(NAME) done

#@echo "$(GREEN)Another day, another successful compile.$(RESET)"
#@echo "$(GREEN)Ready to use "$@"!$(RESET)"
#@echo "$(GREEN)The "$@" was successfully graduated from compile school!$(RESET)"
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

fingers:
	@echo "$(YELLOW)Fingers crossed for no errors...$(RESET)"
	@echo "$(YELLOW)Code getting the VIP treatment in the compiler...$(RESET)"

done:
	@echo "$(GREEN)The $(NAME) was successfully graduated from compile school!$(RESET)\n"


clean:
	@rm -f ${OBJS}
	@echo "\033[31mTemporary object files deleted\033[0m"

fclean: clean
	@rm -f ${NAME}
	@echo "\033[31mExecutable deleted\033[0m"

fclean_all: clean fclean_checker

re: fclean all

.PHONY: all clean fclean re