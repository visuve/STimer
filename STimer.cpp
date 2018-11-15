#include <wx/wxprec.h>
#include <wx/spinctrl.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "STimer.hpp"

#include <chrono>

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

class MainWindow : public wxFrame
{
public:
    MainWindow() :
        wxFrame(nullptr, wxID_ANY, wxT("SHUTDOWN TIMER"), wxDefaultPosition, wxSize(300, 180), m_frameStyle)
    {
        auto sizer = new wxBoxSizer(wxVERTICAL);

        {
            auto hourSpin = new wxSpinCtrl(this, wxID_ANY, _T("HOURS"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 100, 0);

            hourSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
            {
                wxLogMessage(_T("HOUR: %d"), e.GetValue());
                m_hour = std::chrono::hours(e.GetValue());
            });

            sizer->Add(hourSpin, 1, wxEXPAND | wxALL, m_border);
        }

        {
            auto minuteSpin = new wxSpinCtrl(this, wxID_ANY, _T("MINUTES"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 60, 0);

            minuteSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
            {
                wxLogMessage(_T("MINUTE: %d"), e.GetValue());
                m_minute = std::chrono::minutes(e.GetValue());
            });

            sizer->Add(minuteSpin, 1, wxEXPAND | wxALL, m_border);
        }

        {
            auto shutdownButton = new wxButton(this, wxID_ANY, wxT("INIT SHUTDOWN"));

            shutdownButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)->void
            {
                System::Shutdown(m_hour + m_minute);
            });

            sizer->Add(shutdownButton, 1, wxEXPAND | wxALL, m_border);
        }

        {
            auto cancelButton = new wxButton(this, wxID_ANY, wxT("ABORT SHUTDOWN"));

            cancelButton->Bind(wxEVT_BUTTON, [](wxCommandEvent&)->void
            {
                System::CancelShutdown();
            });

            sizer->Add(cancelButton, 1, wxEXPAND | wxALL, m_border);
        }

        SetSizer(sizer);
    }

private:
    static constexpr long m_frameStyle = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX);
    static constexpr int m_border = 3;

    std::chrono::hours m_hour = std::chrono::hours(0);
    std::chrono::minutes m_minute = std::chrono::minutes(0);
};

bool ExampleApp::OnInit()
{
    wxLog::SetActiveTarget(new wxLogStderr());

    auto window = new MainWindow();
    window->Show(true);
    window->CenterOnScreen();

    SetTopWindow(window);

    return true;
}