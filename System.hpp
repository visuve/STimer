#pragma once

#include <chrono>

namespace System
{
#ifdef _WINDOWS_
    void Shutdown(std::chrono::seconds);
#else
    void Shutdown(std::chrono::minutes);
#endif
    void CancelShutdown();
};

