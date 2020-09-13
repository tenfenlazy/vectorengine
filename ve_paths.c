#include "ve_paths.h"

struct ve_path_s {
	ve_point_t start;

	ve_point_t* other;
	unsigned count;
};

ve_pathptr_t vemkpath(const ve_point_t start) {
	ve_pathptr_t result = malloc(sizeof(struct ve_path_s));
	
	result->start = start;
	
	result->other = calloc(VE_PATHMAX, sizeof(ve_point_t));
	result->count = 0;
	
	return result;
}

bool veappendpath(ve_pathptr_t path, const ve_point_t pt, const bool relative) {
	if (!path || (path->count + 1) >= VE_PATHMAX)
		return false;
		
	ve_point_t addp = pt;
	
	if (!relative)
		addp = vemkpoint(addp.x - path->start.x, addp.y - path->start.y);
		
	path->other[path->count] = addp;
	path->count += 1;
	
	return true;
}

bool vecatpath(ve_pathptr_t path1, const ve_pathptr_t path2) {
	if (!path1 || !path2 || (path1->count + 1 + path2->count) >= VE_PATHMAX)
		return false;
		
	veappendpath(path1, path2->start, false);
	
	for (unsigned i = 0; i < path2->count; i++)
		veappendpath(path1, path2->other[i], true);
		
	return true;
}

unsigned vepathcount(const ve_pathptr_t path) {
	if (!path)
		return 0;
		
	return path->count;
}

ve_point_t vegetpointbyid(const ve_pathptr_t path, const unsigned id) {
	if (!path || id > path->count)
		return vemkpoint(0, 0);
	else if (path->count == id)
		return path->start;
		
	return vecombinepoints(path->start, path->other[id]);
}

unsigned vegetpointid(const ve_pathptr_t path, const ve_point_t pt) {
	if (!path)
		return 0;
		
	unsigned vl = 0;
	
	for (unsigned i = 0; i < path->count; i++) {
		ve_point_t ptrq = vegetpointbyid(path, i);
		
		if (ptrq.x == pt.x && ptrq.y == pt.y)
			vl = i;
	}
	
	if (path->start.x == pt.x && path->start.y == pt.y)
		vl = path->count;
		
	return vl;
}

ve_point_t vegetclosestpoint(const ve_pathptr_t path, const ve_point_t pt, const bool relative, unsigned* idp) {
	if (!path)
		return vemkpoint(0, 0);
		
	ve_point_t cmp = pt;
	
	if (relative)
		cmp = vecombinepoints(path->start, cmp);
		
	ve_point_t closest = path->start;
	unsigned ptid = path->count;
	ve_point_t ldiff = vemkpoint(cmp.x - closest.x, cmp.y - closest.y);
	
	for (unsigned i = 0; i < path->count; i++) {
		ve_point_t ptrq = vegetpointbyid(path, i);
		ve_point_t cdiff = vemkpoint(cmp.x - ptrq.x, cmp.y - ptrq.y);
		
		if (cdiff.x <= ldiff.x && cdiff.y <= ldiff.y) {
			ldiff = cdiff;
			ptid = i;
			closest = ptrq;
		}
	}
	
	if (idp)
		(*idp) = ptid;
		
	return closest;
}

bool veremovepointbyid(const ve_pathptr_t path, const unsigned id) {
	if (!path || id >= path->count)
		return false;
	
	for (unsigned i = 0; i < path->count; i++) {
		if (i >= id && (i + 1) < path->count)
			path->other[i] = path->other[i + 1];
	}
	
	return true;
}

ve_pathptr_t veduppath(const ve_pathptr_t path) {
	if (!path)
		return NULL;
		
	ve_pathptr_t result = malloc(sizeof(struct ve_path_s));
	
	result->start = path->start;
	result->count = path->count;
	
	for (unsigned i = 0; i < result->count; i++)
		result->other[i] = path->other[i];
		
	return result;
}
	
void vermpath(ve_pathptr_t path) {
	if (!path)
		return;
		
	free(path->other);
	free(path);
}
