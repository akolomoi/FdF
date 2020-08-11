/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:25:32 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/16 18:26:43 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_cntrl(void)
{
	ft_putendl("\nControls\n");
	ft_putendl(" [NumPad] 8, 2 -> rotate around x axis");
	ft_putendl(" [NumPad] 4, 6 -> rotate around y axis");
	ft_putendl(" [NumPad] 1, 3 -> rotate around z axis");
	ft_putendl(" [NumPad] 7, 9 -> increase/decrease height");
	ft_putendl(" [NumPad] +, - -> zoom in/out");
	ft_putendl(" [NumPad] 5    -> change projection");
	ft_putendl(" [Arrows]      -> move image");
	ft_putendl("          A, S -> rotate around xyz axis (Ccw/cw)");
	ft_putendl("          W, D -> do not press!");
	ft_putendl("          `    -> reset map (completely)\n");
}

void		new_window(t_fdf *fdf)
{
	int	temp;

	temp = 32;
	fdf->height = WIN_HEIGHT;
	fdf->width = WIN_WIDTH;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height,
	"FdF by akolomoi.");
	fdf->img = mlx_new_image(fdf->mlx, fdf->width, fdf->height);
	fdf->img_adr = mlx_get_data_addr(fdf->img, &temp, &temp, &temp);
	fdf->cam.zoom = 0.8;
	fdf->cam.ang_x = 0.0;
	fdf->cam.ang_z = 0.0;
	fdf->cam.ang_y = 0.0;
	fdf->cam.shift_x = 0;
	fdf->cam.shift_y = 0;
	fdf->cam.h_mod = 5;
	fdf->info.init = 0;
	fdf->info.ghost = 0;
	fdf->info.x = 0;
	fdf->info.tri = 0;
	fdf->info.rot_point.color = 0;
	print_cntrl();
}

void		iso(t_point *p)
{
	int	p_x;
	int	p_y;

	p_x = p->act_x;
	p_y = p->act_y;
	p->act_x = (p_x - p_y) * cos(0.523599);
	p->act_y = (p_x + p_y) * sin(0.523599) - p->act_z;
}

int			map_init(t_fdf *fdf, int lines, int words)
{
	int	i;

	i = -1;
	if (!(fdf->map = (t_point**)malloc(sizeof(t_point*) * lines)))
		return (0);
	while (++i < lines)
		if (!(fdf->map[i] = (t_point*)malloc(sizeof(t_point) * words)))
			return (0);
	return (1);
}
