# Libft

A library of utilities, including a rewritten and expanded libft, an optimized ft_printf, and get_next_line. The library is usable in a 42 project, meaning it's hand-written, doesn't call any forbidden functions, and respects the 42 coding norm.

(For the libft project, refers to https://github.com/cclaude42/old_libft)

## How to use it

Using ``make`` will create the ``libft.a`` binary.

To include the library in your project, clone the repository in your working tree and compile with the following flags :

```
gcc -L. -lft file.c
```

## Available functions

This section lists the functions callable from the library. For the prototypes, refer to the headers.

#### GET_NEXT_LINE

* ``get_next_line``

#### FT_PRINTF

* ``ft_printf``

#### FT_IS

* ``ft_isalnum``
* ``ft_isalpha``
* ``ft_isascii``
* ``ft_iscount``
* ``ft_isdigit``
* ``ft_isin``
* ``ft_isprint``
* ``ft_isspace``
* ``ft_isspacenl``
* ``ft_iswhere``

#### FT_MATH

* ``ft_baselen``
* ``ft_hexlen``
* ``ft_nbrlen``
* ``ft_power``

#### FT_MEM

* ``ft_bzero``
* ``ft_calloc``
* ``ft_memccpy``
* ``ft_memchr``
* ``ft_memcmp``
* ``ft_memcpy``
* ``ft_memdel``
* ``ft_memmove``
* ``ft_memset``

#### FT_PUT

* ``ft_putchar``
* ``ft_putchar_fd``
* ``ft_putendl``
* ``ft_putendl_fd``
* ``ft_putnbr``
* ``ft_putnbr_fd``
* ``ft_putstr``
* ``ft_putstr_fd``

#### FT_SKIP

* ``ft_skip_char``
* ``ft_skip_chars``
* ``ft_skip_space``
* ``ft_skip_spacenl``

#### FT_STR

* ``ft_split``
* ``ft_strchr``
* ``ft_strcmp``
* ``ft_strdup``
* ``ft_strjoin``
* ``ft_strlcat``
* ``ft_strlcpy``
* ``ft_strlen``
* ``ft_strmapi``
* ``ft_strncmp``
* ``ft_strnstr``
* ``ft_strrchr``
* ``ft_strtrim``
* ``ft_substr``

#### FT_TO

* ``ft_atoi``
* ``ft_itoa``
* ``ft_tolower``
* ``ft_toupper``

#### FT_LST

* ``ft_lstadd_back``
* ``ft_lstadd_front``
* ``ft_lstclear``
* ``ft_lstdelone``
* ``ft_lstiter``
* ``ft_lstlast``
* ``ft_lstmap``
* ``ft_lstnew``
* ``ft_lstsize``
