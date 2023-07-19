#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_data *data, int  x)
{
	int i = 0;
	int j = 0;
	while (i <=  x)
	{
		my_mlx_pixel_put(data, 0, i, 0x00FF0000);
		my_mlx_pixel_put(data, x, i, 0x00FF0000);
		my_mlx_pixel_put(data, j, 0, 0x00FF0000);
		my_mlx_pixel_put(data, j, x, 0x00FF0000);
		i++;
		j++;
	}
}



void draw_circle(t_data *data, int center_x, int center_y, int radius)
{


	int x = 0;
	int y = radius;
	int p = 1 - radius;

	while (x <= y)
	{
		my_mlx_pixel_put(data, center_x + x, center_y + y, 0x00FF0000);
		my_mlx_pixel_put(data, center_x - x, center_y + y, 0x00FF0000);
		my_mlx_pixel_put(data, center_x + x, center_y - y, 0x00FF0000);
		my_mlx_pixel_put(data, center_x - x, center_y - y, 0x00FF0000);
		my_mlx_pixel_put(data, center_x + y, center_y + x, 0x00FF0000);
		my_mlx_pixel_put(data, center_x - y, center_y + x, 0x00FF0000);
		my_mlx_pixel_put(data, center_x + y, center_y - x, 0x00FF0000);
		my_mlx_pixel_put(data, center_x - y, center_y - x, 0x00FF0000);

		if (p < 0)
		{
			x++;
			p += 2 * x + 1;
		}
		else
		{
			y--;
			x++;
			p += 2 * (x - y) + 1;
		}
	}
}



void draw_line_bresenham(t_data *data, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, get_opposite(0, 22, 194, 55));
		if (x0 == x1 && y0 == y1)
		break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}


void draw_line_dda(t_data *data, int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float xIncrement = (float)dx / (float)steps;
	float yIncrement = (float)dy / (float)steps;

	float x = x0;
	float y = y0;

	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(data, round(x), round(y), 0x00FF0000);
		x += xIncrement;
		y += yIncrement;
	}
}


void draw_triangle(t_data *data, int x0, int y0, int x1, int y1, int x2, int y2) {
	draw_line_bresenham(data, x0, y0, x1, y1);
	draw_line_bresenham(data, x1, y1, x2, y2);
	draw_line_bresenham(data, x2, y2, x0, y0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_shade(double transparent, int r, int g, int b)
{
	int shade = (int) (transparent * 255.0 / 1.0);
	return create_trgb(shade, r, g, b);
}

int get_opposite(int t, int r, int g, int b)
{
	int red = 255 - r;
	int green = 255 - g;
	int blue = 255 - b;

	return (create_trgb(t, red, green, blue));
}


