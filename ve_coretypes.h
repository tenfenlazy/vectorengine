#ifndef VectorEngine_Header_CoreTypes
#define VectorEngine_Header_CoreTypes

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct ve_point_s {
	int x;
	int y;
};
typedef struct ve_point_s ve_point_t;

ve_point_t vemkpoint(const int x, const int y);
ve_point_t vecombinepoints(const ve_point_t pt1, const ve_point_t pt2);

struct ve_color_s;
typedef struct ve_color_s* ve_colorptr_t;

ve_colorptr_t vemkrgba(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
ve_colorptr_t vemkgradient(const ve_colorptr_t color1, const ve_colorptr_t color2, const unsigned step, const bool vertical);

bool veisgradient(const ve_colorptr_t color);

bool vegetrgba(const ve_colorptr_t color, uint8_t* rptr, uint8_t* gptr, uint8_t* bptr, uint8_t* aptr);
ve_colorptr_t vegetbcolor(const ve_colorptr_t gradient);
ve_colorptr_t vegetpcolor(const ve_colorptr_t gradient);

ve_colorptr_t vedupcolor(const ve_colorptr_t color);
void vermcolor(ve_colorptr_t color);

#endif
