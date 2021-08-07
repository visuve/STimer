#include "PCH.hpp"
#include "STimer.hpp"
#include "MainWindow.hpp"
#include "../res/STimer.xpm"

wxIMPLEMENT_APP(ExampleApp);

bool ExampleApp::OnInit()
{
    wxLog::SetActiveTarget(new wxLogStderr());
    auto window = new MainWindow();
    window->SetIcon(STimerIcon);
    window->Show(true);
    window->CenterOnScreen();

    SetTopWindow(window);

    return true;
}