/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:17:12 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/05 18:17:13 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char *av[])
{
	t_fdf	fdf;

	if (ac != 2)
	{
		ft_putendl("usage: ./fdf [map]");
		return (0);
	}
	new_window(&fdf);
	if (!reader(&fdf, open(av[1], O_RDONLY)))
	{
		ft_putendl("Bad input file.");
		exit(0);
	}
	draw(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, keyboard_events, &fdf);
	mlx_hook(fdf.win, 17, 1L << 17, exit_btn, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
