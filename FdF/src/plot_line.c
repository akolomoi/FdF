/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 19:21:49 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/26 19:21:50 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	plot(t_fdf *fdf, int x, int y, int c)
{
	if (x >= 0 && x < fdf->width && y >= 0 && y < fdf->height)
		if (*(int*)(fdf->img_adr + (4 * (x + y * fdf->width))) == 0)
			*(int*)(fdf->img_adr + (4 * (x + y * fdf->width))) = c;
}

static void	line(t_point a, t_point b, t_point t, t_fdf *fdf)
{
	while (!(a.act_x == b.act_x && a.act_y == b.act_y))
	{
		plot(fdf, a.act_x, a.act_y, t.color);
		if (a.act_x == b.act_x && a.act_y == b.act_y)
			break ;
		t.act_z = t.z;
		if (t.act_z > -t.x)
		{
			t.z -= t.y;
			a.act_x += t.act_x;
		}
		if (t.act_z < t.y)
		{
			t.z += t.x;
			a.act_y += t.act_y;
		}
	}
}

void		plot_line(t_point a, t_point b, int c, t_fdf *fdf)
{
	t_point	t;

	t.x = b.act_x - a.act_x;
	t.x = t.x < 0 ? -t.x : t.x;
	t.y = b.act_y - a.act_y;
	t.y = t.y < 0 ? -t.y : t.y;
	t.act_x = b.act_x > a.act_x ? 1 : -1;
	t.act_y = b.act_y > a.act_y ? 1 : -1;
	t.z = (t.x > t.y ? t.x : -t.y) / 2;
	t.color = c;
	if (a.z == 0 && b.z == 0 && fdf->info.ghost)
		c = 0;
	line(a, b, t, fdf);
}
