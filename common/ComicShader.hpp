/*
 * ComicShader.hpp
 *
 * Shader for mtl file supporting diffuse, ambient, specular, opacity
 * by Stefanie Zollmann
 *
 *
 */
#ifndef COMICSHADER_HPP
#define COMICSHADER_HPP

#include "Shader.hpp"
#include "Texture.hpp"

class ComicShader: public Shader{
    public:
        //!Default constructor
        /*! Setup default shader. */
        ComicShader();
        //! Constructor
        /*! Version of constructor that allows for  vertex and fragment shader with differnt names */
        ComicShader(std::string vertexshaderName, std::string fragmentshaderName);
        //! Constructor
        /*! Version of constructor that assumes that vertex and fragment shader have same names */
        ComicShader(std::string shaderName);
        //! Destructor
        /*! Clean up ressources */
        ~ComicShader();
        //! setUpShaderParameters
        /*! Set up all shader parameters */
        void setUpShaderParameters();
        //! setUpSsetTexturehaderParameters
        /*! Set up all shader parameters */
        void setTexture(Texture* texture);
        //! setLightPos
        /*! Set the position of the light source. */
        void setLightPos(glm::vec3 lightPos);
        //! setDiffuse
        /*! Set the diffuse color */
        void setDiffuse(glm::vec3 diffuse);
        //! setAmbient
        /*! Set the ambient color */
        void setAmbient(glm::vec3 ambient);
        //! setSpecular
        /*! Set the specular color */
        void setSpecular(glm::vec3 specular);
        //! setOpacity
        /*! Set amount of opacity */
        void setOpacity(float opacity);
        //! setRenderMode
        /*! Set the render mode.*/
        void setRenderMode(float renderMode);
		//! setShininess
		/*! Set the shininess.*/
		void ComicShader::setShininess(float shininess);
        //! bind
        /*! Bind the shader */
        void bind();
    
    
    private:
        glm::vec4 m_diffuseColor;   //!< diffuse color of the material
        glm::vec4 m_ambientColor;   //!<  ambient color of the material
        glm::vec4 m_specularColor;  //!<  specular color of the material
        float m_renderMode;     //!< render mode
        Texture* m_texture;     //!< texture
        GLuint m_TextureID;     //!< texture id
        GLuint m_lightPosID;    //!< id of the position of the light source
        glm::vec3 m_lightPos;   //!< position of the light source
        float m_opacity;        //!< opacity of the material
		float m_shininess;		//!< shininess of the material
	
    
};


#endif
