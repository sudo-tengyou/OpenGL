#include "glerror.h"

void clearGlError() {
	while (glGetError() != GL_NO_ERROR);
}

bool checkGlError(const char* expression, const char* file, int line) {
	bool isWrong = true;
	while (GLenum error = glGetError()) {
		isWrong = false;
		std::cout << "[OpenGL Error]: " << error << ' ' << expression << ' ' <<
			file << ' ' << line << std::endl;
	}
	return isWrong;
}
