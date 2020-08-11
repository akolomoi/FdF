/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:41:08 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/16 18:41:09 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set1(int k, t_fdf *fdf)
{
	if (k == 91)
		fdf->cam.ang_x += 0.15;
	else if (k == 84)
		fdf->cam.ang_x -= 0.15;
	else if (k == 86)
		fdf->cam.ang_y -= 0.15;
	else if (k == 88)
		fdf->cam.ang_y += 0.15;
	else if (k == 69)
		fdf->cam.zoom += fdf->cam.zoom > 4 ? 0 : 0.07;
	else if (k == 78)
		fdf->cam.zoom -= fdf->cam.zoom - 0.07 > 0 ? 0.07 : 0;
	else if (k == 123)
		fdf->cam.shift_x += 10;
	else if (k == 124)
		fdf->cam.shift_x -= 10;
	else if (k == 126)
		fdf->cam.shift_y += 10;
	else if (k == 125)
		fdf->cam.shift_y -= 10;
	else if (k == 92)
		fdf->cam.h_mod += fdf->cam.h_mod > 32 ? 0 : 1;
	else if (k == 89)
		fdf->cam.h_mod -= fdf->cam.h_mod < -32 ? 0 : 1;
}

static void	spin(t_fdf *fdf, int i)
{
	fdf->cam.ang_x += i * 0.05;
	fdf->cam.ang_y += i * 0.05;
	fdf->cam.ang_z += i * 0.05;
}

static void	set2(int k, t_fdf *fdf)
{
	if (k == 53)
		exit_btn((void*)fdf);
	else if (k == 83)
		fdf->cam.ang_z -= 0.15;
	else if (k == 85)
		fdf->cam.ang_z += 0.15;
	else if (k == 1)
		spin(fdf, 1);
	else if (k == 0)
		spin(fdf, -1);
	else if (k == 2)
		fdf->info.x = fdf->info.x == 1 ? 0 : 1;
	else if (k == 13)
		fdf->info.tri = fdf->info.tri == 1 ? 0 : 1;
	else if (k == 87)
		fdf->info.ghost = fdf->info.ghost == 1 ? 0 : 1;
	else if (k == 50)
		reset(fdf);
}

int			keyboard_events(int k, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	set1(k, fdf);
	set2(k, fdf);
	if (fdf->info.map_height == 1)
		kostil(fdf);
	else if (fdf->info.map_width == 1)
		kostil2(fdf);
	else
		draw(fdf);
	return (0);
}

int			exit_btn(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	exit(1);
}

/*
** system("leaks fdf");
*/
