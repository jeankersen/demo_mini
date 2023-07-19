
#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


int	create_trgb(int t, int r, int g, int b);
void draw_triangle(t_data *data, int x0, int y0, int x1, int y1, int x2, int y2);
void draw_line_dda(t_data *data, int x0, int y0, int x1, int y1);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_circle(t_data *data, int center_x, int center_y, int radius);
void draw_line_bresenham(t_data *data, int x0, int y0, int x1, int y1);
void draw_square(t_data *data, int  x);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

int get_opposite(int t, int r, int g, int b);
int	put_to_range(double value);

int add_shade(double transparent, int r, int g, int b);

#endif
