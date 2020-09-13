#ifndef VectorEngine_Header_Paths
#define VectorEngine_Header_Paths

#include "ve_coretypes.h"

#define VE_PATHMAX 7078

struct ve_path_s;
typedef struct ve_path_s* ve_pathptr_t;

ve_pathptr_t vemkpath(const ve_point_t start);

bool veappendpath(ve_pathptr_t path, const ve_point_t pt, const bool relative);
bool vecatpath(ve_pathptr_t path1, const ve_pathptr_t path2);

unsigned vepathcount(const ve_pathptr_t path);

ve_point_t vegetpointbyid(const ve_pathptr_t path, const unsigned id);
unsigned vegetpointid(const ve_pathptr_t path, const ve_point_t pt);
ve_point_t vegetclosestpoint(const ve_pathptr_t path, const ve_point_t pt, const bool relative, unsigned* idp);
bool veremovepointbyid(const ve_pathptr_t path, const unsigned id);

ve_pathptr_t veduppath(const ve_pathptr_t path);
void vermpath(ve_pathptr_t path);

#endif
