#include <mesh_generate.hpp>

#define OFF (0.5/resolutionX)

// MAGIC
#define ENUMERATE(x, y) \
	( (y) * (resolutionX + 1) \
			+ ((x) % (resolutionX + 1)) )

static inline float map(int i, float a, float b, float A, float B) {
	return (((float)i) - a)
		/ (b - a)
		* (B - A)
		+ A;
}

void createSphereMesh(
    std::vector<VertexNormUV> &vDef,
    std::vector<uint32_t> &vIdx,
    float radius,
    int resolutionX,
    int resolutionY) {

	// TOP
	for(int j=0; j<=resolutionX; j++) {
		vDef.push_back({
			{0, radius, 0},
			{0, 1, 0},
			{map(j, 0, resolutionX, 0, 1) + OFF, 0}});
	}

	// BODY
	// use nonlinear mapping for the V and radY coordinates to lower the
	// polygon density at the equator and increase it at the poles
	for(int j=1; j<=resolutionY-1; j++) {
		for(int i=0; i<=resolutionX; i++) {
			float
				radX = map(i, 0, resolutionX, 0, 2 * M_PI),
				radY = map(j, 0, resolutionY, M_PI/2, -M_PI/2);
			glm::vec3
				nP(
					cos(radX) * abs(cos(radY)),
					sin(radY),
					sin(radX) * abs(cos(radY))),
                P = nP * radius;
			vDef.push_back({
				{P.x, P.y, P.z},
				{nP.x, nP.y, nP.z},
				{   map(i,0,resolutionX,0,1),
					map(j,0,resolutionY,0,1)}});
		}
	}

	// TOP
	for(int j=0; j<=resolutionX; j++) {
		vDef.push_back({
			{0, -radius, 0},
			{0, -1, 0},
			{map(j, 0, resolutionX, 0, 1) + OFF, 1}});
	}

	for(int j=0; j<resolutionY; j++) {
		for(int i=0; i<resolutionX; i++) {
			vIdx.push_back(
				ENUMERATE(i,j));
			vIdx.push_back(
				ENUMERATE(i,j+1));
			vIdx.push_back(
				ENUMERATE(i+1,j));
			vIdx.push_back(
				ENUMERATE(i,j+1));
			vIdx.push_back(
				ENUMERATE(i+1,j));
			vIdx.push_back(
				ENUMERATE(i+1,j+1));
		}
	}
}