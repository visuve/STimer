#include <wx/wxprec.h>

#include "System.hpp"

namespace System
{
#ifdef  _WINDOWS_
    void Shutdown(std::chrono::seconds time)
    {
        const std::string command = "shutdown /s /t " + std::to_string(time.count());
        wxLogMessage(_T("%hs"), command.c_str());
        system(command.c_str());
    }

    void CancelShutdown()
    {
        system("shutdown /a");
    }
#else
    void Shutdown(std::chrono::minutes time)
    {
        const std::string command = "shutdown +" + std::to_string(time.count());
        wxLogMessage(_T("%hs"), command.c_str());
        system(command.c_str());
    }

    void CancelShutdown()
    {
        system("shutdown -c");
    }
#endif
}