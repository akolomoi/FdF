/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:17:45 by akolomoi          #+#    #+#             */
/*   Updated: 2018/12/05 18:17:46 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "mlx.h"

# define WIN_WIDTH 1400
# define WIN_HEIGHT 1400

typedef	struct		s_cam
{
	double			zoom;
	double			ang_x;
	double			ang_y;
	double			ang_z;
	int				shift_x;
	int				shift_y;
	int				h_mod;
}					t_cam;

typedef struct		s_point
{
	int				x;
	int				act_x;
	int				y;
	int				act_y;
	int				z;
	int				act_z;
	int				color;
}					t_point;

typedef struct		s_info
{
	int				point_x;
	int				point_y;
	int				map_width;
	int				map_height;
	int				distance;
	int				init;
	int				ghost;
	int				tri;
	int				x;
	t_point			rot_point;
}					t_info;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_adr;
	t_point			**map;
	int				width;
	int				height;
	t_info			info;
	t_cam			cam;
}					t_fdf;

void				new_window(t_fdf *fdf);
int					keyboard_events(int k, void *param);
int					exit_btn(void *param);
int					parse_to_map(char **map, t_fdf *fdf);
int					is_in_range(char *c, const char *str);
int					map_init(t_fdf *fdf, int lines, int words);
int					reader(t_fdf *fdf, const int fd);
int					get_quan_of_char(char *line, char target);
int					get_words(char *line);
void				get_color(char *line, int *c, t_fdf *fdf);
int					can_do(char *line);
void				draw(t_fdf *fdf);
void				kostil(t_fdf *fdf);
void				kostil2(t_fdf *fdf);
void				get_info(t_fdf *fdf);
void				iso(t_point *p);
void				transform(t_fdf *fdf, t_point *p);
t_point				get_pic_pos(t_fdf *fdf, int dist);
void				plot_line(t_point a, t_point b, int c, t_fdf *fdf);
void				reset(t_fdf *fdf);

#endif
