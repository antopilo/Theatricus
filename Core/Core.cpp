#include "Core.h"

namespace Core
{
	Window* Core::CreateWindow(uint32_t width, uint32_t height)
	{
		auto window = new Window("Theatricus Studio", { width, height });
		return window;
	}
}
