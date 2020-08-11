/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:31:41 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/14 18:31:42 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_in_range(char *c, const char *str)
{
	while (*c)
	{
		while (*str)
		{
			if (*str == *c)
				return (1);
			str++;
		}
		c++;
	}
	return (0);
}

int		reader(t_fdf *fdf, const int fd)
{
	int		i;
	char	*line;
	char	*res;

	res = NULL;
	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1)
			return (0);
		res = ft_strjoin(res, line);
		res = ft_strjoin(res, "\n");
		free(line);
	}
	if (!res)
		return (0);
	return (parse_to_map(&res, fdf));
}
