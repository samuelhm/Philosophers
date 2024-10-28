# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 13:53:02 by linyao            #+#    #+#              #
#    Updated: 2024/10/28 02:31:30 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Config
CC = gcc
TARGET = philo
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Debug
CFLAGS += -g -O1 #-fsanitize=thread
# Directory
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Source + obj
SRCS_FILES = philo.c checks.c actions.c philo_utils.c time_utils.c
SRCS = $(addprefix $(SRC_DIR)/,$(SRCS_FILES))

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Main entrance
all: $(TARGET)

# Compile Binary
$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(TARGET)
	@echo "\033[1;36mBinary $@ created\033[0m"


# -MMD to include header dependences to .d file and create $(OBJ_DIR) if it doesn't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@ > /dev/null
	@echo "\033[0;32mObject $@ created\033[0m"

# Create obj dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Utils
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "\033[1;31mObjects deleted\033[0m"; \
	fi

#remove binaries too
fclean: clean
	@if [ -f "$(TARGET)" ]; then \
		rm -f $(TARGET); \
		echo "\033[1;31m$(TARGET) deleted\033[0m"; \
	fi

re: fclean all

#Add, all requiered .h Header files
-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
