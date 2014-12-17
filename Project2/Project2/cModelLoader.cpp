#include "cModelLoader.h"

cModelLoader::cModelLoader()
{
	m_model = NULL;
}


void cModelLoader::loadModel(const char* mdlFilename)
{
	m_model = glmReadOBJ(mdlFilename);
	glmVertexNormals(m_model, 180.0, false);
}

void cModelLoader::renderMdl(glm::vec3 mdlPosition, glm::vec3 mdlRotationAngle, glm::vec3 mdlScale)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	//transformations here...
	glTranslatef(mdlPosition.x, mdlPosition.y, -mdlPosition.z);
	glRotatef(mdlRotationAngle.x, 1, 0, 0);
	glRotatef(mdlRotationAngle.y, 0, 1, 0);
	glRotatef(mdlRotationAngle.z, 0, 0, 1);
	glScalef(mdlScale.x, mdlScale.y, mdlScale.z);
	glmDraw(m_model, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
	//glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

mdlDimensions cModelLoader::getModelDimensions()
{
	mdlDimensions mdl_Dims;
	GLfloat mdlDims[3];
	glmDimensions(m_model, mdlDims);
	mdl_Dims.s_mdlWidth = mdlDims[0];
	mdl_Dims.s_mdlheight = mdlDims[1];
	mdl_Dims.s_mdldepth = mdlDims[2];
	return mdl_Dims;
}

cModelLoader::~cModelLoader()
{

}
