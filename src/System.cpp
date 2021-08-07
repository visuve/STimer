#include "PCH.hpp"
#include "System.hpp"

namespace System
{
    void Execute(const wxString& command)
    {
        wxArrayString out;
        long exitCode = wxExecute(command, out, wxEXEC_SYNC | wxEXEC_HIDE_CONSOLE);
        wxLogMessage(wxT("Command '%s' exited with: %ld / 0x%.8lX"), command, exitCode, exitCode);

        if (!out.IsEmpty())
        {
            wxLogMessage(wxT("Output:"));

            for (const wxString& line : out)
            {
                wxLogMessage(line);
            }
        }
    }

#ifdef  _WINDOWS_
    const wxString ShutdownExe = wxT("C:\\Windows\\System32\\shutdown.exe");

    void Shutdown(std::chrono::seconds time)
    {
        Execute(ShutdownExe + wxT(" /s /t ") + std::to_wstring(time.count()));
    }

    void CancelShutdown()
    {
        Execute(ShutdownExe + wxT(" /a"));
    }
#else
    const wxString ShutdownExe = wxT("/sbin/shutdown");

    void Shutdown(std::chrono::minutes time)
    {
        Execute(ShutdownExe + wxT(" +") + std::to_string(time.count()));
    }

    void CancelShutdown()
    {
        Execute(ShutdownExe + wxT(" -c"));
    }
#endif
}