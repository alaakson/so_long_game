NAME = libft.a

CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror

SRC =  ft_atoi.c \
        ft_bzero.c \
        ft_calloc.c \
        ft_isalnum.c \
        ft_isalpha.c \
        ft_isascii.c \
        ft_isdigit.c \
        ft_isprint.c \
        ft_itoa.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_memmove.c \
        ft_memset.c \
        ft_memcpy.c \
        ft_putchar_fd.c \
        ft_putendl_fd.c \
        ft_putnbr_fd.c \
        ft_putstr_fd.c \
        ft_split.c \
        ft_strrchr.c \
        ft_strchr.c \
        ft_strdup.c \
        ft_striteri.c \
        ft_strjoin.c \
        ft_strlcat.c \
        ft_strlcpy.c \
        ft_strlen.c \
        ft_strmapi.c \
        ft_strncmp.c \
        ft_strnstr.c \
        ft_strtrim.c \
        ft_substr.c \
        ft_tolower.c \
        ft_toupper.c \
        get_next_line.c \
        get_next_line_utils.c \
        ft_print_hex.c \
        ft_print_i_d.c \
        ft_print_p.c \
        ft_print_u.c \
        ft_print.c \
        ft_print_utils.c

BNS_S = ft_lstadd_back_bonus.c \
        ft_lstadd_front_bonus.c \
        ft_lstclear_bonus.c \
        ft_lstdelone_bonus.c \
        ft_lstiter_bonus.c \
        ft_lstlast_bonus.c \
        ft_lstmap_bonus.c \
        ft_lstnew_bonus.c \
        ft_lstsize_bonus.c

OFILES = $(SRC:%.c=%.o)
BOFILES = $(BNS_S:%.c=%.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(AR) -rcs $(NAME) $(OFILES)

bonus: .bonus

.bonus: $(OFILES) $(BOFILES)
	$(AR) -rcs $(NAME) $(OFILES) $(BOFILES)
	@touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
