
#include "ComicShader.hpp"
// complete the setters with the appropriate method for passing information to the shaders


ComicShader::ComicShader(){
        
}

// version of constructor that allows for  vertex and fragment shader with differnt names
    
ComicShader::ComicShader(std::string vertexshaderName, std::string fragmentshaderName): Shader(vertexshaderName, fragmentshaderName){
    
    setUpShaderParameters();
    
}

// version of constructor that assumes that vertex and fragment shader have same name
ComicShader::ComicShader(std::string shaderName): Shader(shaderName){
    
    setUpShaderParameters();
    
}

ComicShader::~ComicShader(){
    glDeleteTextures(1, &m_TextureID);

}

void ComicShader::setUpShaderParameters(){
	m_diffuseColor = glm::vec4(1.0);
    GLint diffusecolorID = glGetUniformLocation(programID, "diffuseColor");
    glProgramUniform4fv(programID,diffusecolorID,1, &m_diffuseColor[0]);

    m_texture =NULL;
}

void ComicShader::setTexture(Texture* texture){
    m_texture = texture;
	GLuint m_TextureID = glGetUniformLocation(programID, "myTextureSampler");
	glGenTextures(1, &m_TextureID);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, m_TextureID);

	//Give the image to OpenGL
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, )
    // Get a handle for our "myTextureSampler" uniform
	
}


void ComicShader::setLightPos(glm::vec3 lightPos) {
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(gl_light) */
	m_lightPos = lightPos;
	GLint m_lightPosID = glGetUniformLocation(programID, "lightPosWorldspace");
	glProgramUniform3f(programID, m_lightPosID, m_lightPos.x, m_lightPos.y, m_lightPos.z);

}
void ComicShader::setDiffuse(glm::vec3 diffuse){
    
    m_diffuseColor= glm::vec4(diffuse[0],diffuse[1],diffuse[2],1.0);;
    GLint diffusecolorID = glGetUniformLocation(programID, "diffuseColor");
    glProgramUniform4fv(programID,diffusecolorID,1, &m_diffuseColor[0]);
}
void ComicShader::setAmbient(glm::vec3 ambient){
    
    m_ambientColor= glm::vec4(ambient[0],ambient[1],ambient[2],1.0);
	GLint ambientID = glGetUniformLocation(programID, "ambientColor");
	glProgramUniform4fv(programID, ambientID, 1, &m_ambientColor[0]);
	
}
void ComicShader::setSpecular(glm::vec3 specular){
    
    m_specularColor= glm::vec4(specular[0],specular[1],specular[2],1.0);
	GLint specularID = glGetUniformLocation(programID, "specularColor");
	glProgramUniform4fv(programID, specularID, 1, &m_specularColor[0]);
	
}

void ComicShader::setOpacity(float opacity){
    
    m_opacity= opacity;
	GLint opacityID = glGetUniformLocation(programID, "opacityV");
	glProgramUniform1f(programID, opacityID, m_opacity);
	
}

void ComicShader::setShininess(float shininess) {
	m_shininess = shininess;
	GLint shininessID = glGetUniformLocation(programID, "Ns");
	glProgramUniform1f(programID, shininessID, m_shininess);
}

void ComicShader::setRenderMode(float renderMode){
    
    m_renderMode= renderMode;
 
}


void ComicShader::bind(){
    // Use our shader
    glUseProgram(programID);
    // Bind our texture in Texture Unit 0
    if(m_texture!=NULL){
        m_texture->bindTexture();
        // Set our "myTextureSampler" sampler to user Texture Unit 0 using glUniform1i

		
		
    }
    
}
