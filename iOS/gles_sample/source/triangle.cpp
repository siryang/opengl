#include "triangle.h"
#include <stdio.h>

#include "basic_type.h"
#include "shader.h"

namespace gles {
    void DemoEntry::init(int w, int h) {
        YUN_LOG("init");
        GLuint vertexShader;
        GLuint fragmentShader;
        GLint linked;

        const ShaderSource* source = &g_sampleShader;
        vertexShader = loadShader(GL_VERTEX_SHADER, source->vertex);
        fragmentShader = loadShader(GL_FRAGMENT_SHADER, source->frame);
        m_programObject = glCreateProgram();
        glAttachShader(m_programObject, vertexShader);
        glAttachShader(m_programObject, fragmentShader);
        glLinkProgram(m_programObject);
        glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);

        glViewport(0, 0, w, h);
    }

    void DemoEntry::draw() {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(m_programObject);

        const float vertices[] = {
            -0.5, 0.2,
            0.5, 0.5,
            0.5, -0.5
        };
        // GLES2没有glMatrix的ModelView和Projection定义，默认传入Shader的顶点都是归一化定点，如果需要变换，可以将Projection当做参数传入，在Shader中变换。
        GLuint positionLocation = glGetAttribLocation(m_programObject, "a_position");
        glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(positionLocation);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
    }
}