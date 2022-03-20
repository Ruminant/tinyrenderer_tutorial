#pragma once
#include <vector>
#include "geometry.h"

/**
 * @brief wavefront obj model loader
 * 
 * Read in an OBJ file and allow access to the verts and faces.
 * 
 */
class Model
{
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts() const;
	int nfaces() const;
	const Vec3f &vert(int i) const;
	const std::vector<int> &face(int idx) const;
};
