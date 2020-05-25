#include "cub3d.h"

int main(void)
{
	t_vars	vars;

	setup_vars(&vars);
	mlx_hook(vars.win, 2, (1l<<0), move_player, &vars);
	mlx_loop(vars.mlx);
}


/*

#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease	5
#define MotionNotify	6
#define EnterNotify		7

#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)
#define EnterWindowMask			(1L<<4)
*/
