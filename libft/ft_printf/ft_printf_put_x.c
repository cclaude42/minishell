/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:21:24 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/06 18:13:13 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

int		ft_puthex_prewid(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		count;
	int		padding;

	printed = 0;
	count = flags->precision - ft_hexlen(n);
	count += (n < 0) ? 1 : 0;
	count = (count > 0) ? count : 0;
	padding = flags->width - ft_hexlen(n) - count;
	padding = (padding > 0) ? padding : 0;
	printed += padding + count + ft_hexlen(n);
	while (flags->minus == 0 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	if (n < 0)
	{
		buf_write(flags->buffer, '-', &flags->index);
		n = -n;
	}
	while (count-- > 0)
		buf_write(flags->buffer, '0', &flags->index);
	ft_puthex(flags, n, cap);
	while (flags->minus == 1 && padding-- > 0)
		buf_write(flags->buffer, ' ', &flags->index);
	return (printed);
}

int		ft_puthex_pre(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		count;

	printed = 0;
	count = (flags->dot == 1) ? flags->precision : flags->width;
	count -= (n >= 0) ? ft_hexlen(n) : ft_hexlen(n) - 1;
	if (n < 0)
	{
		buf_write(flags->buffer, '-', &flags->index);
		n = -n;
		printed++;
	}
	while (count-- > 0)
	{
		buf_write(flags->buffer, '0', &flags->index);
		printed++;
	}
	printed += ft_puthex(flags, n, cap);
	return (printed);
}

int		ft_puthex_wid(unsigned int n, struct s_flgs *flags, int cap)
{
	int		printed;
	int		padding;

	printed = 0;
	padding = flags->width - ft_hexlen(n);
	while (flags->minus == 0 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	printed += ft_puthex(flags, n, cap);
	while (flags->minus == 1 && padding-- > 0)
	{
		buf_write(flags->buffer, ' ', &flags->index);
		printed++;
	}
	return (printed);
}

int		ft_puthex(struct s_flgs *flags, unsigned int n, int cap)
{
	char	*set;
	int		printed;
	int		i;

	if (cap == 1)
		set = "0123456789ABCDEF";
	else
		set = "0123456789abcdef";
	printed = 0;
	if (n / 16 > 0)
		printed += ft_puthex(flags, n / 16, cap);
	i = n % 16;
	buf_write(flags->buffer, set[i], &flags->index);
	printed++;
	return (printed);
}
