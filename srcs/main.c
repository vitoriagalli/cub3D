#include "cub3d.h"

int main(void)
{
	t_vars	vars;

	init_game(&vars);
	mlx_hook(vars.win, 2, (1l<<0), move_player_press, &vars);

	// a função release deixa mais devagar pois processa todos os keycodes antes de update the position
	// a nao ser que mude para new_position player --> verificar diferenças
	//mlx_hook(vars.win, 3, (1l<<1), move_player_release, &vars); //verificar se faz diferença

	//mlx_expose_hook(vars.win, update_new_position, &vars);

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
