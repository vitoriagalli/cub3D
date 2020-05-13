  #include "cub3d.h"

  void bresenhamAlg (t_data *img, int x0, int y0, int x1, int y1)
 {
  int dx = abs (x1 - x0);
  int dy = abs (y1 - y0);
  int x, y;
  if (dx >= dy)
  {
   int d = dy-dx;
   int ds = dy;
   int dt = (dy-dx);
       if (x0 < x1)
       {
            x = x0;
            y = y0;
       }
        else
        {
             x = x1;
             y = y1;
             x1 = x0;
             y1 = y0;
        }
       my_mlx_pixel_put(img, x, y, 0xff0000ff);
   while (x < x1)
   {
        if (d < 0)
        d += ds;
        else {
             if (y < y1) {
              y++;
              d += dt;
             }
             else {
              y--;
              d += dt;
             }
            }
   x++;
        my_mlx_pixel_put(img, x, y, 0xff0000ff);
       }
       }
       else {
             int d = dx-dy;
             int ds = dx;
             int dt = (dx-dy);
             if (y0 < y1) {
             x = x0;
             y = y0;
             }
             else {
             x = x1;
             y = y1;
             y1 = y0;
             x1 = x0;
             }
            my_mlx_pixel_put(img, x, y, 0xff0000ff);
        while (y < y1)
        {
              if (d < 0)
                 d += ds;
              else {
                      if (x > x1){
                      x--;
                      d += dt;
                   } else {
                      x++;
                      d += dt;
                   }
              }
              y++;
              my_mlx_pixel_put(img, x, y, 0xff0000ff);
        }
       }
  }

void	draw_triangle_bresenham(t_data *img)
{
	bresenhamAlg(img, 0, 200, 100, 0);
}
