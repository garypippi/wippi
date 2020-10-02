#ifndef WIPPI_GRAPHIC_SHADER
#define WIPPI_GRAPHIC_SHADER

#include <vector>
#include <GL/glew.h>

namespace wippi
{
    namespace graphic
    {
        class shader
        {
            public:
                shader();
                GLuint pid();
                void compile(GLuint id, const char* file);
                void link();
            private:
                GLuint id;
                std::vector<GLuint> ids;
                void attach();
                void detach();
        };
    }
}

#endif
