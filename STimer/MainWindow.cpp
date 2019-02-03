#include <wx/wxprec.h>
#include <wx/spinctrl.h>

#include "MainWindow.hpp"
#include "System.hpp"

namespace Styles
{
    constexpr long Frame = wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX);
    constexpr int Border = 3;
}

MainWindow::MainWindow() :
    wxFrame(nullptr, wxID_ANY, wxT("SHUTDOWN TIMER"), wxDefaultPosition, wxSize(200, 200), Styles::Frame)
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    {
        auto hourSpin = new wxSpinCtrl(this, wxID_ANY, wxT("HOURS"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 100, 0);

        hourSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
        {
            wxLogMessage(wxT("HOUR: %d"), e.GetValue());
            m_hour = std::chrono::hours(e.GetValue());
        });

        sizer->Add(hourSpin, 1, wxEXPAND | wxALL, Styles::Border);
    }

    {
        auto minuteSpin = new wxSpinCtrl(this, wxID_ANY, wxT("MINUTES"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 60, 0);

        minuteSpin->Bind(wxEVT_SPINCTRL, [this](wxSpinEvent& e)->void
        {
            wxLogMessage(wxT("MINUTE: %d"), e.GetValue());
            m_minute = std::chrono::minutes(e.GetValue());
        });

        sizer->Add(minuteSpin, 1, wxEXPAND | wxALL, Styles::Border);
    }

    {
        auto shutdownButton = new wxButton(this, wxID_ANY, wxT("INIT SHUTDOWN"));

        shutdownButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&)->void
        {
            System::Shutdown(m_hour + m_minute);
        });

        sizer->Add(shutdownButton, 1, wxEXPAND | wxALL, Styles::Border);
    }

    {
        auto cancelButton = new wxButton(this, wxID_ANY, wxT("ABORT SHUTDOWN"));

        cancelButton->Bind(wxEVT_BUTTON, [](wxCommandEvent&)->void
        {
            System::CancelShutdown();
        });

        sizer->Add(cancelButton, 1, wxEXPAND | wxALL, Styles::Border);
    }

    SetSizer(sizer);
}