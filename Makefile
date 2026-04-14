# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 12:54:24 by craabe            #+#    #+#              #
#    Updated: 2026/04/14 17:46:48 by craabe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I $(INC_DIR) -I $(MLX_DIR)/include
LDFLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm
RM = rm -f

SRC_DIR		= src
MAIN_DIR	= $(SRC_DIR)/main
PAR_DIR		= $(SRC_DIR)/parser
ENG_DIR		= $(SRC_DIR)/engine
ENG_DIR_B = $(SRC_DIR)/engine_bonus
INC_DIR   = inc
LIBFT_DIR = libft
OBJ_DIR   = obj/mand
OBJ_DIR_B = obj/bonus

MLX_DIR = ./MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

MAIN_FILES = 0_cub3D.c 99_freeing_tools.c

PAR_FILES = 0_create_settings.c 1_parsing.c 2_filepath_handling.c \
			3_cub_sanitizer.c 4_texture_handling.c 5_color_handling.c \
			6_map_handling.c 7_map_handling_util.c 8_map_list_util.c \
			9_map_verification.c 10_map_verification_util.c

ENG_FILES = draw.c engine.c hooks.c player.c render_utils.c texture.c view.c

ENG_FILES_B =	draw_bonus.c engine_bonus.c hooks_bonus.c player_bonus.c \
				render_utils_bonus.c texture_bonus.c view_bonus.c minimap_bonus.c

MAIN_SRC  = $(addprefix $(MAIN_DIR)/, $(MAIN_FILES))
PAR_SRC   = $(addprefix $(PAR_DIR)/, $(PAR_FILES))
ENG_SRC   = $(addprefix $(ENG_DIR)/, $(ENG_FILES))
ENG_SRC_B = $(addprefix $(ENG_DIR_B)/, $(ENG_FILES_B))

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
ENG_OBJ  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENG_SRC))

MAIN_OBJ_B = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_B)/%.o, $(MAIN_SRC))
PAR_OBJ_B  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_B)/%.o, $(PAR_SRC))
ENG_OBJ_B  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_B)/%.o, $(ENG_SRC_B))

OBJ   = $(MAIN_OBJ) $(PAR_OBJ) $(ENG_OBJ)
OBJ_B = $(MAIN_OBJ_B) $(PAR_OBJ_B) $(ENG_OBJ_B)

LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "Get chrispy."

bonus: $(MLX_LIB) $(LIBFT_A) $(OBJ_B)
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "Get extra chrispy."

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

# Mandatory Object Pattern
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus Object Pattern
$(OBJ_DIR_B)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r obj/
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "Cleaned up object files."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re bonus
