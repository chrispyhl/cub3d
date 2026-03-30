# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gries <gries@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 12:54:24 by craabe            #+#    #+#              #
#    Updated: 2026/03/30 20:08:03 by gries            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wextra -Wall -Werror -I $(INC_DIR)
RM = rm -f

SRC_DIR = src/
MAIN_DIR = $(SRC_DIR)/main/
PAR_DIR = $(SRC_DIR)/parser/
ENG_DIR = $(SRC_DIR)/engine/
INC_DIR = inc/
LIBFT_DIR = libft/
OBJ_DIR = obj/

MAIN_FILES = 99_freeing_tools.c

PAR_FILES = -1_tester_main.c \
			0_create_settings.c \
			1_filepath_handling.c \
			2_cub_sanitizer.c \
			3_texture_handling.c \
			4_color_handling.c

ENG_FILES =

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
ENG_SRC = $(addprefix $(ENG_DIR), $(ENG_FILES))

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
ENG_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENG_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(MAIN_OBJ) $(PAR_OBJ) $(ENG_OBJ)

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)
# $(LDFLAGS)
	@echo "Get chrispy."

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
# creates object files in new obj folder on root lvl

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "Cleaned up object files."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re
