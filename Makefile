# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:00:43 by user42            #+#    #+#              #
#    Updated: 2021/12/20 14:48:37 by cgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		=	gcc
CFLAGS =	-Wall -Wextra -Werror
SRC		=	./srcs/others/minishell.c ./srcs/others/free.c ./srcs/others/errors.c \
			./srcs/cmd/cmd_echo.c ./srcs/cmd/cmd_unset.c ./srcs/cmd/hub.c ./srcs/cmd/cmd_export.c ./srcs/cmd/cmd_execve.c \
			./srcs/cmd/cmd_execute.c ./srcs/cmd/cmd_pwd.c ./srcs/cmd/cmd_cd.c ./srcs/cmd/cmd_export_utils.c ./srcs/cmd/cmd_exit.c\
			./srcs/cmd_struct/ft_cmdadd_back.c ./srcs/cmd_struct/ft_cmdadd_front.c ./srcs/cmd_struct/ft_cmdlast.c ./srcs/cmd_struct/ft_cmdnew.c ./srcs/cmd_struct/ft_cmdsize.c ./srcs/cmd_struct/ft_cmdfirst.c \
			./srcs/env/env.c ./srcs/env/dollars.c ./srcs/env/quotes.c ./srcs/env/dollars_utils_len.c ./srcs/env/dollars_utils_trim.c\
			./srcs/parsing/checker.c ./srcs/parsing/parser.c ./srcs/parsing/parse_redirections.c ./srcs/parsing/parse_redirections_2.c ./srcs/parsing/heredoc.c ./srcs/parsing/search_in_parsing.c \
			./srcs/tokens/concat_tokens.c ./srcs/tokens/get_token.c ./srcs/tokens/utils_concat_tokens.c ./srcs/tokens/tokens.c
OBJ 	=	$(SRC:%.c=%.o)
NAME 	=	ft_minishell
LIBFT	=	libft.a

all : $(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) ./srcs/libft/$(LIBFT) -lreadline
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

$(LIBFT):	
			@make --no-print-directory -C ./srcs/libft
			@cp ./srcs/libft/libft.a ./srcs/$(LIBFT)

clean:
			@rm -f *.o
			@rm -f ./srcs/*/*.o
			@make --no-print-directory -C ./srcs/libft clean

fclean:		clean
			@make --no-print-directory -C ./srcs/libft fclean
			@rm -f $(NAME) a.aout srcs/${LIBFT}
			
re:			fclean all
		
exec:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) executed]\n"
			@./$(NAME)
