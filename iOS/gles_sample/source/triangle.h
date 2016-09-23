#ifndef GLES_TRIANGLE_H
#define GLES_TRIANGLE_H

#include <OpenGLES/ES2/gl.h>

namespace gles {
    class DemoEntry {
    public:
        void init(int w, int h);
        void draw();
        void cleanup();
    private:
        GLuint m_programObject;
        int m_width, m_height;
        GLuint m_positionVar;
        GLuint m_timeVar;
        long m_startSecond;
    };
}

#endif