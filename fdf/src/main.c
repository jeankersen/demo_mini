
#include "fdf.h"


int	close_win_press_space(int keycode, t_vars info)
{
	if (keycode ==  53)
	{
		printf("ok exit\n");
		mlx_destroy_window(info.mlx, info.win);

	}
	return (0);
}




int	main(void)
{
	 t_vars info;
	t_data	img;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(info.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	//draw_line_bresenham(&img, 50, 50, 50, 500);
	/*
	draw_circle(&img, 100, 100, 100);
	draw_line_dda(&img, 100, 100, 100, 500);
	draw_square(&img, 50);
	draw_triangle(&img, 150, 150, 150, 300, 450, 600);
	my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	*/
	mlx_hook(info.win, 2, 1L<<0, close_win_press_space, &info);
	mlx_loop(info.mlx);
}
