# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 23:38:57 by cdapurif          #+#    #+#              #
#    Updated: 2021/08/12 16:32:27 by cdapurif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server

CLIENT = client

SRCS =	srcs/server.c \
		srcs/client.c

SRCS_BONUS =	srcs_bonus/server_bonus.c \
				srcs_bonus/client_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) srcs/server.o -o $(SERVER)
		@echo "\033[32;1mCreated:\033[0m $(SERVER)"
		@$(CC) $(CFLAGS) srcs/client.o -o $(CLIENT)
		@echo "\033[32;1mCreated:\033[0m $(CLIENT)"

bonus: $(OBJS_BONUS)
		@$(CC) $(CFLAGS) srcs_bonus/server_bonus.o -o $(SERVER)
		@echo "\033[32;1mCreated:\033[0m $(SERVER)"
		@$(CC) $(CFLAGS) srcs_bonus/client_bonus.o -o $(CLIENT)
		@echo "\033[32;1mCreated:\033[0m $(CLIENT)"

clean:
		@$(RM) srcs/server.o srcs/client.o
		@$(RM) srcs_bonus/server_bonus.o srcs_bonus/client_bonus.o
		@echo "\033[31;1mremoved:\033[0m object files"

fclean: clean
		@$(RM) $(SERVER) $(CLIENT)
		@echo "\033[31;1mremoved:\033[0m $(SERVER) and $(CLIENT)"

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS) $(OBJS_BONUS)
