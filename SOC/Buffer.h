#pragma once

#if defined(WIN32) && !defined(_USE_GL_DEFINES)

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Surface.h"

#elif defined(__APPLE__) || defined(_USE_GL_DEFINES)

#include "VertexBufferGL.h"
#include "IndexBufferGL.h"

namespace Rendering
{
	namespace Buffer
	{
		typedef VertexBufferGL	VertexBuffer;
		typedef IndexBufferGL	IndexBuffer;
	}
}


#endif