/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   artist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:34:21 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/18 18:34:22 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <libc.h>

static void	plot_sqr(int i, int j, t_fdf *fdf)
{
	t_point	a;
	t_point	b;
	t_point	c;
	t_point	d;

	a = fdf->map[i][j];
	b = fdf->map[i][j + 1];
	c = fdf->map[i + 1][j + 1];
	d = fdf->map[i + 1][j];
	plot_line(a, b, (a.z > b.z ? a.color : b.color), fdf);
	plot_line(b, c, (b.z > c.z ? b.color : c.color), fdf);
	plot_line(d, c, (d.z > c.z ? d.color : c.color), fdf);
	plot_line(a, d, (d.z > a.z ? d.color : a.color), fdf);
	if (fdf->info.x)
	{
		plot_line(a, c, (a.z > c.z ? a.color : c.color), fdf);
		plot_line(b, d, (b.z > d.z ? b.color : d.color), fdf);
	}
	if (fdf->info.tri)
		plot_line(a, c, (a.z > c.z ? a.color : c.color), fdf);
}

void		kostil2(t_fdf *fdf)
{
	int	t_h;

	mlx_clear_window(fdf->mlx, fdf->win);
	ft_bzero(fdf->img_adr, fdf->height * fdf->width * 4);
	t_h = -1;
	while (++t_h < fdf->info.map_height)
		transform(fdf, &fdf->map[t_h][0]);
	t_h = -1;
	if (fdf->info.map_height == 1)
	{
		if (fdf->map[0][0].act_x >= 0 && fdf->map[0][0].act_x < fdf->width
		&& fdf->map[0][0].act_y >= 0 && fdf->map[0][0].act_y < fdf->height)
			if (*(int*)(fdf->img_adr + (4 * (fdf->map[0][0].act_x +
			fdf->map[0][0].act_y * fdf->width))) == 0)
				*(int*)(fdf->img_adr + (4 * (fdf->map[0][0].act_x +
				fdf->map[0][0].act_y * fdf->width))) = fdf->map[0][0].color;
	}
	else
	{
		while (++t_h < fdf->info.map_height - 1)
			plot_line(fdf->map[t_h][0], fdf->map[t_h + 1][0],
			(fdf->map[t_h][0].z > fdf->map[t_h + 1][0].z ?
			fdf->map[t_h][0].color : fdf->map[t_h + 1][0].color), fdf);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void		kostil(t_fdf *fdf)
{
	int	t_w;

	mlx_clear_window(fdf->mlx, fdf->win);
	ft_bzero(fdf->img_adr, fdf->height * fdf->width * 4);
	t_w = -1;
	while (++t_w < fdf->info.map_width)
		transform(fdf, &fdf->map[0][t_w]);
	t_w = -1;
	if (fdf->info.map_width == 1)
	{
		if (fdf->map[0][0].act_x >= 0 && fdf->map[0][0].act_x < fdf->width
		&& fdf->map[0][0].act_y >= 0 && fdf->map[0][0].act_y < fdf->height)
			if (*(int*)(fdf->img_adr + (4 * (fdf->map[0][0].act_x +
			fdf->map[0][0].act_y * fdf->width))) == 0)
				*(int*)(fdf->img_adr + (4 * (fdf->map[0][0].act_x +
				fdf->map[0][0].act_y * fdf->width))) = fdf->map[0][0].color;
	}
	else
	{
		while (++t_w < fdf->info.map_width - 1)
			plot_line(fdf->map[0][t_w], fdf->map[0][t_w + 1],
			(fdf->map[0][t_w].z > fdf->map[0][t_w + 1].z ?
			fdf->map[0][t_w].color : fdf->map[0][t_w + 1].color), fdf);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void		draw(t_fdf *fdf)
{
	int	t_w;
	int	t_h;

	t_h = -1;
	mlx_clear_window(fdf->mlx, fdf->win);
	ft_bzero(fdf->img_adr, fdf->height * fdf->width * 4);
	while (++t_h < fdf->info.map_height)
	{
		t_w = -1;
		while (++t_w < fdf->info.map_width)
			transform(fdf, &fdf->map[t_h][t_w]);
	}
	t_h = -1;
	while (++t_h < fdf->info.map_height - 1)
	{
		t_w = -1;
		while (++t_w < fdf->info.map_width - 1)
			plot_sqr(t_h, t_w, fdf);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
