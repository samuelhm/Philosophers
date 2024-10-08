# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 13:53:02 by linyao            #+#    #+#              #
#    Updated: 2024/10/08 20:00:01 by shurtado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Config
CC = gcc
TARGET = philo
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

# Debug
#CFLAGS += -g -O0
# Directory
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIB_DIR = lib

# Librarys
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source + obj
SRCS_FILES = philo.c
SRCS = $(addprefix $(SRC_DIR)/,$(SRCS_FILES))

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Main entrance
all: libft $(TARGET)

# Compile Binary
$(TARGET): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(TARGET)
	@echo "\033[1;36mBinary $@ created\033[0m"


# -MMD to include header dependences to .d file and create $(OBJ_DIR) if it doesn't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@ > /dev/null
	@echo "\033[0;32mObject $@ created\033[0m"

# Create obj dir
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

#Call libft Makefile
libft:
	@git submodule update --init --recursive
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR)

# Utils
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "\033[1;31mObjects deleted\033[0m"; \
	fi
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR) clean

#remove binaries too
fclean: clean
	@if [ -f "$(TARGET)" ]; then \
		rm -f $(TARGET); \
		echo "\033[1;31m$(TARGET) deleted\033[0m"; \
	fi
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR) fclean


re: fclean all

#Add, all requiered .h Header files
-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
