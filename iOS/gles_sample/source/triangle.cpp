#include "triangle.h"
#include <stdio.h>

#include "basic_type.h"
#include "shader.h"
#include "cmath"

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

        m_positionVar = glGetAttribLocation(m_programObject, "a_position");
        m_timeVar = glGetUniformLocation(m_programObject, "a_time");
        glUseProgram(m_programObject);
        m_width = w;
        m_height = h;
        m_startSecond = getTime().tv_sec;
    }

    void DemoEntry::draw() {
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_width, m_height);

        timeval now = getTime();
        float animateValue = (now.tv_sec - m_startSecond + now.tv_usec / 1000000.0f) * 2.0f;
        glUniform1f(m_timeVar, animateValue);

        const int dimension = 2;
        const float vertices[] = {
            1.0, 1.0,
            1.0, -1.0,
            -1.0, -1.0
        };
        // GLES2没有glMatrix的ModelView和Projection定义，默认传入Shader的顶点都是归一化定点，如果需要变换，可以将Projection当做参数传入，在Shader中变换。

        glVertexAttribPointer(m_positionVar, dimension, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(m_positionVar);

        glDrawArrays(GL_TRIANGLE_FAN, 0, element_of(vertices) / dimension);
    }
}