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
        "uniform float a_time;          \n"
        "void main() {                  \n"
        "    float y = sin(a_time) * a_position.y;     \n"
        "    gl_Position = vec4(a_position.x, y, a_position.z, 1.0);  \n"
        "}",

        "precision mediump float;       \n"
        "uniform float a_time;          \n"
        "void main() {                  \n"
        "    float r = abs(sin(a_time));        \n"
        "    float g = abs(cos(a_time));        \n"
        "    float b = abs(cos(a_time + 10.0)); \n"
        "    gl_FragColor = vec4(r, g, b, 1.0); \n"
        "}"
    };
    //

    GLuint loadShader(GLenum type, const char *shaderSrc);
}



#endif