/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 15:34:04 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/23 15:34:06 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rot_z(t_fdf *fdf, t_point *p)
{
	int		x;
	int		y;
	double	a;

	if (fdf->cam.ang_z == 0)
		return ;
	a = fdf->cam.ang_z;
	x = p->act_x;
	y = p->act_y;
	p->act_x = x * cos(a) - y * sin(a);
	p->act_y = x * sin(a) + y * cos(a);
}

static void	rot_y(t_fdf *fdf, t_point *p)
{
	int		x;
	int		z;
	double	a;

	if (fdf->cam.ang_y == 0)
		return ;
	a = fdf->cam.ang_y;
	x = p->act_x;
	z = p->act_z;
	p->act_x = x * cos(a) + z * sin(a);
	p->act_z = -x * sin(a) + z * cos(a);
}

static void	rot_x(t_fdf *fdf, t_point *p)
{
	int		y;
	int		z;
	double	a;

	if (fdf->cam.ang_x == 0)
		return ;
	a = fdf->cam.ang_x;
	y = p->act_y;
	z = p->act_z;
	p->act_y = y * cos(a) - z * sin(a);
	p->act_z = y * sin(a) + z * cos(a);
}

static void	scale(t_fdf *fdf, t_point *p)
{
	double	scale;

	scale = fdf->cam.zoom;
	if (scale == 0)
		return ;
	p->act_x *= scale;
	p->act_y *= scale;
	p->act_z *= scale;
}

void		transform(t_fdf *fdf, t_point *p)
{
	p->act_x = p->x * fdf->info.distance - fdf->info.point_x;
	p->act_y = p->y * fdf->info.distance - fdf->info.point_y;
	p->act_z = p->z * (p->z != 0 ? fdf->cam.h_mod : 5);
	if (fdf->info.ghost)
		iso(p);
	scale(fdf, p);
	rot_x(fdf, p);
	rot_y(fdf, p);
	rot_z(fdf, p);
	p->act_x = p->act_x + WIN_WIDTH / 2 - fdf->cam.shift_x;
	p->act_y = p->act_y + WIN_HEIGHT / 2 - fdf->cam.shift_y;
}
