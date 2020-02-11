/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:07:57 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/06 18:41:39 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

struct	s_flgs
{
	char	buffer[4096];
	int		index;
	int		minus;
	int		zero;
	int		dot;
	int		precision;
	int		width;
};

int		ft_putchar_minwid(struct s_flgs *flags, char c, int width);
int		ft_putchar_zerowid(struct s_flgs *flags, char c, int width);
int		ft_putchar_wid(struct s_flgs *flags, char c, int width);
int		ft_putchar(struct s_flgs *flags, char c);

int		ft_strlen(char *s);
int		ft_putstr_prewid(char *s, struct s_flgs *flags);
int		ft_putstr_wid(char *s, struct s_flgs *flags);
int		ft_putstr_pre(struct s_flgs *flags, char *s, int prec);
int		ft_putstr(struct s_flgs *flags, char *s);

int		ft_memlen(unsigned long n);
int		ft_putmem_prewid(unsigned long n, struct s_flgs *flags);
int		ft_putmem_wid(unsigned long n, struct s_flgs *flags);
int		ft_putmem_pre(unsigned long n, struct s_flgs *flags);
int		ft_putmem(struct s_flgs *flags, unsigned long n, int start);

int		ft_nbrlen(long n);
int		ft_putnbr_prewid(long n, struct s_flgs *flags);
int		ft_putnbr_pre(long n, struct s_flgs *flags);
int		ft_putnbr_wid(long n, struct s_flgs *flags);
int		ft_putnbr(struct s_flgs *flags, long n);

int		ft_hexlen(unsigned int n);
int		ft_puthex_prewid(unsigned int n, struct s_flgs *flags, int cap);
int		ft_puthex_pre(unsigned int n, struct s_flgs *flags, int cap);
int		ft_puthex_wid(unsigned int n, struct s_flgs *flags, int cap);
int		ft_puthex(struct s_flgs *flags, unsigned int n, int cap);

int		ft_octlen(unsigned int n);
int		ft_putoct_prewid(unsigned int n, struct s_flgs *flags);
int		ft_putoct_pre(unsigned int n, struct s_flgs *flags);
int		ft_putoct_wid(unsigned int n, struct s_flgs *flags);
int		ft_putoct(struct s_flgs *flags, unsigned int n);

int		ft_print_char(char c, struct s_flgs *flags);
int		ft_print_str(char *s, struct s_flgs *flags);
int		ft_print_mem(unsigned long n, struct s_flgs *flags);
int		ft_print_nbr(long n, struct s_flgs *flags);
int		ft_print_hex(unsigned int n, struct s_flgs *flags, char c);
int		ft_print_oct(unsigned int n, struct s_flgs *flags);
int		ft_print_other(char c, struct s_flgs *flags);

int		is_end_flag(const char c);
int		is_valid_flag(const char c);
int		ft_atoi_star(const char *s, int *i, va_list args);
void	flagger(const char *s, int *i, struct s_flgs *flags, va_list args);

void	buf_write(char *buffer, char c, int *printed);
int		func_branch(const char *s, int *i, va_list args, struct s_flgs *flags);
int		ft_printf(const char *string, ...);
#endif
