#include "shader.h"
#include <cstdlib>
#include <OpenGLES/ES2/gl.h>
#include "basic_type.h"

namespace gles {
    GLuint loadShader(GLenum type, const char *shaderSrc) {
        GLuint shader;
        GLint compiled;

        // Create the shader object
        shader = glCreateShader(type);
        if (shader == 0) {
            YUN_LOG("load shader error, type: %d", type);
            YUN_LOG("shader source: \n %s", shaderSrc);
            return 0;
        }

        glShaderSource(shader, 1, &shaderSrc, nullptr);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled == 0) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1) {
                char *infoLog =(char*) malloc(sizeof(char) * infoLen);
                glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
                YUN_LOG("Error compiling shader:\n%s\n", infoLog);
                free(infoLog);
            }
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }
}

