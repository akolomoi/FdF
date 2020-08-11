/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:31:18 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/17 17:31:19 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		reset(t_fdf *fdf)
{
	fdf->info.tri = 0;
	fdf->info.ghost = 0;
	fdf->cam.ang_x = 0;
	fdf->cam.ang_y = 0;
	fdf->cam.ang_z = 0;
	fdf->cam.h_mod = 5;
	fdf->cam.zoom = 0.8;
	fdf->cam.shift_y = 0;
	fdf->cam.shift_x = 0;
}

static int	get_z(int z)
{
	while (z > 50000)
		z -= 50000;
	while (z < -50000)
		z += 50000;
	return (z);
}

static int	line_init(t_fdf *fdf, char *line_to_parse, int line, int check)
{
	char	**word;
	int		i;
	char	*coma;

	if (get_words(line_to_parse) != check)
		return (0);
	word = ft_strsplit(line_to_parse, ' ');
	i = -1;
	while (++i < check)
	{
		fdf->map[line][i].x = i;
		fdf->map[line][i].y = line;
		fdf->map[line][i].z = get_z(ft_atoi(word[i]));
		fdf->map[line][i].act_z = fdf->map[line][i].z + 100;
		if (!is_in_range(word[i], "-0123456789,xabcdefABCDEF")
		|| !can_do(word[i]))
			return (0);
		if ((coma = ft_strchr(word[i], ',')))
			get_color(coma + 1, &fdf->map[line][i].color, fdf);
		else
			fdf->map[line][i].color = 0;
		free(word[i]);
	}
	free(word);
	return (1);
}

int			parse_to_map(char **map, t_fdf *fdf)
{
	char	**row;
	int		lines;
	int		words;
	int		i;

	lines = get_quan_of_char(*map, '\n');
	row = ft_strsplit(*map, '\n');
	words = get_words(row[0]);
	fdf->info.map_width = words;
	fdf->info.map_height = lines;
	if (!map_init(fdf, lines, words))
		return (0);
	i = -1;
	while (++i < lines)
	{
		if (!(line_init(fdf, row[i], i, words)))
			return (0);
		free(row[i]);
	}
	free((void*)*map);
	free((void*)row);
	get_info(fdf);
	return (1);
}
