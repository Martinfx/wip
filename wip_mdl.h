//
// WIP
// Copyright (c) 2020 Jovan Lanik
//

// Model Functions

#pragma once

#include "wip_types.h"

typedef struct {
	float *vertex;
	float *normal;
	uint8_t *color;
	uint32_t *index;
	int vertex_c;
	int index_c;
} wip_ply_t;

typedef struct {
	struct {
		struct WIP_NAMED_VEC(3, float, WIP_XYZ, vertex, v);
		struct WIP_NAMED_VEC(3, float, WIP_XYZ, normal, n);
		struct WIP_NAMED_VEC(4, uint8_t, WIP_RGBA, color, c);
	} *model;
	uint32_t *index;
	int *vertex_c;
	int *index_c;
} wip_mdl_t;

wip_ply_t *wip_readModel(wip_ply_t *p, const char *file);
wip_mdl_t *wip_prepModel(wip_mdl_t *m, wip_ply_t *p);

#ifdef GL_TRUE
typedef struct {
	#define BUFF2(type) { type data_b; type element_b; }
	union WIP_NAMED_VEC(2, GLuint, BUFF2, buffers, );
	#undef BUFF2
	size_t element_c;
	GLuint vertex_a;
} wip_glmdl_t;

wip_glmdl_t *wip_loadModel(wip_glmdl_t *gm, wip_mdl_t *m);
#endif

