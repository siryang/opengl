#ifndef GLES_SAMPLE_SHADER_H
#define GLES_SAMPLE_SHADER_H

#include <OpenGLES/ES2/gl.h>

namespace gles {
    struct ShaderSource {
        const char* vertex;
        const char* frame;
    };

    const ShaderSource g_sampleShader = {
        "precision mediump float;       \n"
        "attribute vec4 a_position;     \n"
        "void main() {                  \n"
        "    gl_Position = a_position;  \n"
        "}",

        "precision mediump float;       \n"
        "void main() {                  \n"
        "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}"
    };

    GLuint loadShader(GLenum type, const char *shaderSrc);
}



#endif