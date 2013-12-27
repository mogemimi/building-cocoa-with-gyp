//
//  Copyright (C) <year> <copyright holders>.
//

#ifndef BUILDINGCOCOAWITHGYP_SRC_QUADRENDERER_H
#define BUILDINGCOCOAWITHGYP_SRC_QUADRENDERER_H

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

namespace BuildingCocoaWithGyp {

class QuadRenderer
{
public:
	QuadRenderer();
	~QuadRenderer();

	void Draw();
	
private:
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint shaderProgram;
	GLuint inputLayout;
};

}// namespace BuildingCocoaWithGyp

#endif
