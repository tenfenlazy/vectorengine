#include "ve_coretypes.h"

struct ve_color_s {
	uint8_t* components;
	
	bool gradient;
	bool vertical;
	ve_colorptr_t start;
	ve_colorptr_t end;
	unsigned step;
};

ve_point_t vemkpoint(const int x, const int y) {
	ve_point_t result = {x, y};
	return result;
}

ve_point_t vecombinepoints(const ve_point_t pt1, const ve_point_t pt2) {
	return vemkpoint(pt1.x + pt2.x, pt1.y + pt2.y);
}

ve_colorptr_t vemkrgba(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
	ve_colorptr_t result = malloc(sizeof(struct ve_color_s));
	
	result->components = calloc(4, sizeof(uint8_t));
	
	result->components[0] = r;
	result->components[1] = g;
	result->components[2] = b;
	result->components[3] = a;
	
	result->gradient = false;
	result->start = NULL;
	result->end = NULL;
	
	result->step = 0;
	result->vertical = false;
	
	return result;
}

ve_colorptr_t vemkgradient(const ve_colorptr_t color1, const ve_colorptr_t color2, const unsigned step, const bool vertical) {
	if (!color1 || !color2 || veisgradient(color1) || veisgradient(color2) || step < 1)
		return NULL;

	ve_colorptr_t result = malloc(sizeof(struct ve_color_s));
	
	result->components = NULL;
	
	result->gradient = true;
	result->start = vedupcolor(color1);
	result->end = vedupcolor(color2);
	
	result->step = step;
	result->vertical = vertical;
	
	return result;
}

bool veisgradient(const ve_colorptr_t color) {
	if (!color)
		return false;
		
	return color->gradient;
}

#define _setifreal(ptr, vl) if (ptr) \
				(*ptr) = vl;

bool vegetrgba(const ve_colorptr_t color, uint8_t* rptr, uint8_t* gptr, uint8_t* bptr, uint8_t* aptr) {
	if (!color)
		return false;
	
	uint8_t* components = color->components;
	
	if (color->gradient)
		components = color->start->components;
		
	_setifreal(rptr, components[0]);
	_setifreal(gptr, components[1]);
	_setifreal(bptr, components[2]);
	_setifreal(aptr, components[3]);
	
	return true;
}

ve_colorptr_t vegetbcolor(const ve_colorptr_t gradient) {
	if (!gradient)
		return NULL;
		
	if (!gradient->gradient)
		return gradient;
	
	return gradient->start;
}
	
ve_colorptr_t vegetpcolor(const ve_colorptr_t gradient) {
	if (!gradient || !gradient->gradient)
		return NULL;
		
	return gradient->end;
}

ve_colorptr_t vedupcolor(const ve_colorptr_t color) {
	if (!color)
		return NULL;
		
	ve_colorptr_t result = malloc(sizeof(struct ve_color_s));
	
	result->gradient = color->gradient;
	
	if (result->gradient) {
		result->components = NULL;
		
		result->vertical = color->vertical;
		result->step = color->step;
		
		result->start = vedupcolor(color->start);
		result->end = vedupcolor(color->end);
	} else {
		result->components = calloc(4, sizeof(uint8_t));
		
		for (unsigned i = 0; i < 4; i++)
			result->components[i] = color->components[i];
			
		result->vertical = false;
		result->step = 0;
		
		result->start = NULL;
		result->end = NULL;
	}
	
	return result;
}

void vermcolor(ve_colorptr_t color) {
	if (!color)
		return;
	
	vermcolor(color->start);
	vermcolor(color->end);
	
	free(color->components);
	free(color);
}
