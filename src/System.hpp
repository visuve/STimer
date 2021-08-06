#pragma once

#include <chrono>

namespace System
{
    void Execute(const wxString& command);

#ifdef _WINDOWS_
    void Shutdown(std::chrono::seconds);
#else
    void Shutdown(std::chrono::minutes);
#endif
    void CancelShutdown();
};