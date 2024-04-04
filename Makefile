# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmorot <mmorot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 07:30:46 by mmorot            #+#    #+#              #
#    Updated: 2024/03/06 07:45:11 by mmorot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror
BUILD_DIR = .build
BUILD_CLIENT = .build/$(CLIENT)
BUILD_SERVER = .build/$(SERVER)
PATH_SRCS = ./srcs/
SRCS_CLIENT = client.c utils.c ft_atoi.c
SRCS_SERVER = server.c utils.c ft_atoi.c
INCLUDES_DIR = includes
INCLUDES = $(INCLUDES_DIR)/minitalk.h
OBJ_CLIENT = $(addprefix $(BUILD_CLIENT)/,$(SRCS_CLIENT:.c=.o))
OBJ_SERVER = $(addprefix $(BUILD_SERVER)/,$(SRCS_SERVER:.c=.o))

all: $(SERVER) $(CLIENT)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $@

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $@

$(BUILD_CLIENT)/%.o: $(PATH_SRCS)%.c $(INCLUDES)
	@mkdir -p $(BUILD_CLIENT)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

$(BUILD_SERVER)/%.o: $(PATH_SRCS)%.c $(INCLUDES)
	@mkdir -p $(BUILD_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(SERVER)
	@rm -rf $(CLIENT)

bonus: all

re: fclean all

.PHONY: all clean fclean re bonus