
#include "Group.hpp"

const char* shaderName = "mtlShader";

    // default triangle
Group::Group(){
        init();
    
    };
Group::~Group(){
        
        
    };
    
void Group::addMesh(Mesh* mesh){
        meshes.push_back(mesh);
    
    }
void Group::addMaterial(Material* mat){
        materials.push_back(mat);
        
    }
    
Mesh* Group::getMesh(int index){
        return meshes[index];
    
    }
Material* Group::getMaterial(int index){
        return materials[index];
    }
    
int Group::getNumMeshes(){
    return meshes.size();

}

//! change the name so vertfrag shaders are switchable
void Group::setRenderMode(float rendermode) {
	if (materials.size() > 0) {
		if (rendermode == 1) {
			shaderName = "comicShader";
			setupShaders();
			for (unsigned int i = 0; i < materials.size(); i++)
			{
				MTLShader* shader = static_cast<MTLShader*>(materials[i]->getShader());
				if (shader != NULL)
					shader->setRenderMode(rendermode);
			}
		}
		else {
			shaderName = "mtlShader";
			setupShaders();
			for (unsigned int i = 0; i < materials.size(); i++)
			{
				MTLShader* shader = static_cast<MTLShader*>(materials[i]->getShader());
				if (shader != NULL)
					shader->setRenderMode(rendermode);
			}
		}
	}
}

void Group::init(){
    setupShaders();
    
}
//!render all the meshes
void Group::render(Camera* camera){
   //TODO: Make sure all meshes are rendered - at the moment only the first one is rendered
    if(meshes.size()>0){
		for (unsigned int i = 0; i < meshes.size(); i++) {
			meshes[i]->bindShaders();
			meshes[i]->render(camera);
		}
    }
    
}
//! pass all the mat info into mtlshader
void Group::setupShaders(){
	//TODO: Do this for all meshes
	if(meshes.size()>0){
		for (unsigned int i = 0; i < meshes.size(); i++) {
			int matIndex = meshes[i]->getMatIndex(); // TODO: get the correct material index from obj file
			Material* mat = getMaterial(matIndex);
			Shader* shader = NULL;
			//if (!mat->shaderIsInitialized()) {
				MTLShader* mtlshader = new MTLShader(shaderName);
				mtlshader->setDiffuse(mat->getDiffuseColour());
				mtlshader->setAmbient(mat->getAmientColour());
				mtlshader->setSpecular(mat->getSpecularColour());
				mtlshader->setShininess(mat->getShininess());
				mtlshader->setOpacity(mat->getOpacity());
				mtlshader->setLightPos(glm::vec3(4,4,4));
				mat->setShader(mtlshader);
				if (mat->getTextureName() != "") {
					Texture* texture = new Texture(mat->getTextureName());
					mtlshader->setTexture(texture);
				}

				shader = mtlshader;
			//}
			//else {
			//	shader = mat->getShader();
			//}
			meshes[i]->setShader(shader);
		}
        
    }
}
