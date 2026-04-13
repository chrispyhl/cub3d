# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 12:54:24 by craabe            #+#    #+#              #
#    Updated: 2026/04/13 17:03:00 by craabe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wextra -Wall -Werror -I $(INC_DIR) -I $(MLX_DIR)/include
LDFLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm
RM = rm -f

SRC_DIR = src/
MAIN_DIR = $(SRC_DIR)/main/
PAR_DIR = $(SRC_DIR)/parser/
ENG_DIR = $(SRC_DIR)/engine/
INC_DIR = inc/
LIBFT_DIR = libft/
OBJ_DIR = obj/

MLX_DIR = ./MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

MAIN_FILES =    0_cub3D.c \
                99_freeing_tools.c

PAR_FILES = 0_create_settings.c \
            1_parsing.c \
            2_filepath_handling.c \
            3_cub_sanitizer.c \
            4_texture_handling.c \
            5_color_handling.c \
            6_map_handling.c \
            7_map_handling_util.c \
            8_map_list_util.c \
            9_map_verification.c \
            10_map_verification_util.c

ENG_FILES = draw.c \
            engine.c \
            hooks.c \
            player.c \
            render_utils.c \
            texture.c \
            view.c

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
ENG_SRC = $(addprefix $(ENG_DIR), $(ENG_FILES))

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
ENG_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENG_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(MAIN_OBJ) $(PAR_OBJ) $(ENG_OBJ)

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "Get chrispy."

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)/include" ]; then \
		echo "MLX42 folder missing. Fetching it..."; \
		git submodule update --init --recursive; \
		if [ ! -d "$(MLX_DIR)/include" ]; then \
			echo "ERROR: Git failed to fetch MLX42. Exiting..."; \
			exit 1; \
		fi; \
	fi
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

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
