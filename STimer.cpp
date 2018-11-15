#include <wx/wxprec.h>
#include <wx/spinctrl.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "STimer.hpp"

IMPLEMENT_APP(ExampleApp);

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

bool ExampleApp::OnInit()
{
    wxLog::SetActiveTarget(new wxLogStderr());

    long style = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX);
    auto frame = new wxFrame(nullptr, wxID_ANY, wxT("SHUTDOWN TIMER"), wxDefaultPosition, wxSize(300, 180), style);
    
    {
        auto hourSpin = new wxSpinCtrl(frame, wxID_ANY, _T("HOURS"), wxPoint(20, 5), wxSize(240, 25), wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 100, 0);

        hourSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
        {
            wxLogMessage(_T("HOUR: %d"), e.GetValue());
            m_hour = std::chrono::hours(e.GetValue());
        });
    }

    {
        auto minuteSpin = new wxSpinCtrl(frame, wxID_ANY, _T("MINUTES"), wxPoint(20, 35), wxSize(240, 25), wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 60, 0);

        minuteSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
        {
            wxLogMessage(_T("MINUTE: %d"), e.GetValue());
            m_minute = std::chrono::minutes(e.GetValue());
        });
    }

    {
        auto shutdownButton = new wxButton(frame, wxID_ANY, wxT("INIT SHUTDOWN"), wxPoint(20, 75), wxSize(240, 25));

        shutdownButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)->void
        {
            System::Shutdown(m_hour + m_minute);
        });
    }

    {
        auto cancelButton = new wxButton(frame, wxID_ANY, wxT("ABORT SHUTDOWN"), wxPoint(20, 105), wxSize(240, 25));

        cancelButton->Bind(wxEVT_BUTTON, [](wxCommandEvent&)->void
        {
            System::CancelShutdown();
        });
    }

    frame->Show(true);
    frame->CenterOnScreen();

    SetTopWindow(frame);
    return true;
}