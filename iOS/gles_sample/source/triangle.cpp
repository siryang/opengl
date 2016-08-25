#include "triangle.h"
#include <stdio.h>
#include <OpenGLES/ES2/gl.h>

#define YUN_LOG(format, ...) printf("[YunMap]%s %d:"#format"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

namespace gles {
    void DemoEntry::init() {
        YUN_LOG("init");
    }

    void DemoEntry::draw() {
        YUN_LOG("draw");
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}