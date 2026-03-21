NAME = ft_ping
NAME_BONUS = ft_ping_bonus
CFLAGS = -Wall -Werror -Wextra 
CC = cc -g3 -O0

OBJECTS_FOLDER = ./obj/

MANDATORY_FOLDER = ./mandatory/
MANDATORY_SOURCES = $(addprefix $(MANDATORY_FOLDER), main.c build_echo_request.c read_echo_reply.c)
MANDATORY_OBJECTS = $(subst $(MANDATORY_FOLDER),$(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(MANDATORY_OBJECTS)
	 $(CC) $(CFLAGS) $(MANDATORY_OBJECTS) -o $(NAME)

$(OBJECTS_FOLDER)%.o: $(MANDATORY_FOLDER)%.c $(MANDATORY_FOLDER)ft_ping.h
	 $(CC) $(CFLAGS) -c $< -o $@

val:
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
	--trace-children=yes --trace-children-skip=*/bin/*,*/sbin/*,./a.out \
	./pipex_bonus .gitignore "nl" "tr a-z A-Z" "cat" outfile

clean:
	rm -rf $(OBJECTS_FOLDER)*

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all val
