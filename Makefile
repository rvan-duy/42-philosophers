# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rvan-duy <rvan-duy@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/25 13:42:50 by rvan-duy      #+#    #+#                  #
#    Updated: 2022/04/15 14:53:15 by rvan-duy      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			:= philo
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror -g

################################################################################

ifdef THREAD
CFLAGS			+= -fsanitize=thread
endif
ifdef ADDRESS
CFLAGS			+= -fsanitize=address -g3
endif
ifdef NO_FLAGS
CFLAGS			:= 
endif
ifneq ($(shell uname), Darwin)
CFLAGS			+= -pthread
endif

################################################################################

HEADERS 		:= include/philo.h
INCLUDE_FLAGS 	:= $(addprefix -I, $(sort $(dir $(HEADERS))))

SOURCES 		:= 	src/main.c \
					src/start_threads.c \
					src/routine.c \
					src/utils.c \
					src/init/init_data.c \
					src/init/init_philos.c \
					src/actions/eat.c \
					src/actions/sleep.c \
					src/actions/think.c \
					src/time.c

BOLD 			:= \e[1m
RESET 			:= \e[0m
LIGHT_GREEN 	:= \e[92m
LIGHT_CYAN 		:= \e[96m

OBJECTS_DIR		:= obj
OBJECTS			:= $(SOURCES:src/%.c=$(OBJECTS_DIR)/%.o)

################################################################################

all: $(NAME)

obj/%.o: src/%.c $(HEADERS)
	@mkdir -p $(@D)
	@printf "$(LIGHT_CYAN)$(BOLD)make$(RESET)   [$(LIGHT_GREEN)$(NAME)$(RESET)] : "
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(LIGHT_CYAN)$(BOLD)make$(RESET)   [$(LIGHT_GREEN)$(NAME)$(RESET)] : "
	@printf "$(NAME) created\n"

clean:
	@printf "$(LIGHT_CYAN)$(BOLD)clean$(RESET)  [$(LIGHT_GREEN)$(NAME)$(RESET)] : "
	/bin/rm -rf obj

fclean: clean
	@printf "$(LIGHT_CYAN)$(BOLD)fclean$(RESET) [$(LIGHT_GREEN)$(NAME)$(RESET)] : "
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

################################################################################
