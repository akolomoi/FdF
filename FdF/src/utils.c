/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:52:02 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/18 17:52:04 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_quan_of_char(char *line, char target)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == target)
			i++;
		line++;
	}
	return (i);
}

int			get_words(char *line)
{
	int	words;
	int	is_ws;

	is_ws = 1;
	words = 0;
	while (*line)
	{
		if (*line > 0 && *line <= ' ' && !is_ws)
			is_ws = 1;
		else if (!(*line > 0 && *line <= ' ') && is_ws)
		{
			is_ws = 0;
			words++;
		}
		line++;
	}
	return (words);
}

static int	hex_to_dec(char *line)
{
	int	res;
	int	t;

	res = 0;
	t = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
			t = *line - '0';
		else if (ft_isalpha(*line))
			t = *line - (*line >= 'A' && *line <= 'Z' ? 'A' - 10 : 'a' - 10);
		res *= 16;
		res += t;
		line++;
	}
	return (res);
}

void		get_color(char *line, int *c, t_fdf *fdf)
{
	int	x;

	x = 1;
	while (*line == '0' || x)
	{
		if (*line == 'x')
			x = 0;
		line++;
	}
	if (!is_in_range(line, "0123456789abcdefABCDEF"))
	{
		ft_putendl("Bad color value.");
		exit_btn(fdf);
	}
	*c = hex_to_dec(line);
}

int			can_do(char *line)
{
	while (*line != ',' && *line)
	{
		if (!ft_isdigit(*line) && *line != '-')
			return (0);
		line++;
	}
	return (1);
}
