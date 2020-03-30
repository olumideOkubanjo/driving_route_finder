#include "draw_route.h"
#include "map_drawing.h"
#define BLACK 0X0000

extern shared_vars shared;

void draw_route() {
  // implement this!

  if(shared.num_waypoints > 0){
    for(int i = 0; i < shared.num_waypoints -1; i++){

      int32_t xPoint1 = longitude_to_x(shared.map_number, shared.waypoints[i].lon);
      xPoint1 = xPoint1 - shared.map_coords.x;

      int32_t yPoint1 = latitude_to_y(shared.map_number, shared.waypoints[i].lat);
      yPoint1 = yPoint1 - shared.map_coords.y;

      int32_t xPoint2 = longitude_to_x(shared.map_number, shared.waypoints[i+1].lon);
      xPoint2 = xPoint2 - shared.map_coords.x;

      int32_t yPoint2 = latitude_to_y(shared.map_number, shared.waypoints[i+1].lat);
      yPoint2 = yPoint2 - shared.map_coords.y;

      shared.tft->drawLine(xPoint1, yPoint1, xPoint2, yPoint2, BLACK);
      
    }  
  }
  
}
