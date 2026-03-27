# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 12:54:24 by craabe            #+#    #+#              #
#    Updated: 2026/03/24 12:59:53 by craabe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CC = cc
CFLAGS = -Wextra -Wall -Werror -I includes
# LDFLAGS = -lreadline
RM = rm -f

SRC_DIR = src/
MAIN_DIR = $(SRC_DIR)/main/
PAR_DIR = $(SRC_DIR)/parser/
ENG_DIR = $(SRC_DIR)/engine/
GC_DIR = $(SRC_DIR)/gc/
LIBFT_DIR = libft/
OBJ_DIR = obj/

MAIN_FILES =

PAR_FILES =

ENG_FILES =

GC_FILES = ft_malloc.c \
			gc_itoa.c \
			gc_libft.c \
			gc_split.c \
			gc_utils.c

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
ENG_SRC = $(addprefix $(ENG_DIR), $(ENG_FILES))
GC_SRC = $(addprefix $(GC_DIR), $(GC_FILES))

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
ENG_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENG_SRC))
GC_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GC_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(MAIN_OBJ) $(PAR_OBJ) $(ENG_OBJ) $(GC_OBJ)

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
