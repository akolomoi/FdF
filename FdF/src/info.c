/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:37:50 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/20 18:37:51 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		get_pic_pos(t_fdf *fdf, int dist)
{
	t_point	res;
	double	mid_x;
	double	mid_y;

	mid_x = fdf->info.map_width / 2;
	mid_y = fdf->info.map_height / 2;
	res.act_x = 0;
	res.act_y = 0;
	while (mid_x > 0)
	{
		res.act_x += dist;
		mid_x--;
	}
	while (mid_y > 0)
	{
		res.act_y += dist;
		mid_y--;
	}
	return (res);
}

static int	get_col_speed(t_fdf *fdf)
{
	int	i;
	int	res;
	int	j;
	int	z[2];

	i = -1;
	z[0] = fdf->map[0][0].z;
	z[1] = z[0];
	while (++i < fdf->info.map_height)
	{
		j = -1;
		while (++j < fdf->info.map_width)
		{
			if (fdf->map[i][j].z > z[0])
				z[0] = fdf->map[i][j].z;
			else if (fdf->map[i][j].z < z[1])
				z[1] = fdf->map[i][j].z;
		}
	}
	if (z[0] - z[1] == 0)
		z[0]++;
	res = 0xFFFFFF / (z[0] - z[1]);
	return (res < 0 ? -res : res);
}

static void	init_map(t_fdf *fdf)
{
	int	i;
	int	j;
	int	speed;

	i = -1;
	speed = get_col_speed(fdf);
	while (++i < fdf->info.map_height)
	{
		j = -1;
		while (++j < fdf->info.map_width)
		{
			fdf->map[i][j].act_z = fdf->map[i][j].z + fdf->info.distance * 20;
			if (!fdf->map[i][j].color)
				fdf->map[i][j].color = (fdf->map[i][j].z == 0 ? 1 :
				fdf->map[i][j].z) * (fdf->map[i][j].z < 0 ? -speed - 3000
				: speed);
		}
	}
}

void		get_info(t_fdf *fdf)
{
	int		mid_x;
	int		mid_y;
	int		dist;
	t_point	pic_pos;

	mid_x = fdf->width / 2;
	mid_y = fdf->height / 2;
	dist = (fdf->height / fdf->info.map_height +
	fdf->width / fdf->info.map_width) / 2.5;
	pic_pos = get_pic_pos(fdf, dist);
	fdf->info.distance = dist;
	fdf->info.point_x = pic_pos.act_x;
	fdf->info.point_y = pic_pos.act_y;
	if (fdf->info.init == 0)
		init_map(fdf);
	fdf->info.init = 1;
}
