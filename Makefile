NAME				=	ircserv

DIRECTORY_SOURCE	=	src

FILES_SOURCE		=	src/Config/Config.cpp \
						src/Server/Server.cpp \
						src/Service/Service.cpp \
						src/Service/Commands.cpp \
						src/Service/ParseRequest.cpp \
						src/User/User.cpp \
						main.cpp

O_FILE = $(FILES_SOURCE:.cpp=.o)

COMPILE				=	c++
COMPILATION_FLAG	=	-Wall -Wextra -Werror -std=c++98

all: $(NAME)

%.o: %.cpp
	@printf "\e[33m"
	@printf "Compile\t$< -> $@\n"
	mkdir -p $(dir $@)
	$(COMPILE) $(COMPILATION_FLAG) -c $< -o $@

$(NAME): $(O_FILE)
	@printf "\e[32m"
	@printf "Build\t$@\n"
	$(COMPILE) -o $@ $(FILES_SOURCE)

clean:
	@printf "\e[31m"
	@printf "Remove\n"
	rm -rf $(O_FILE)

fclean: clean
	@printf "Remove\t$(NAME)\n"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
