#pragma once

#include <wx/frame.h>

#include <chrono>

class MainWindow : public wxFrame
{
public:
    MainWindow();

private:
    std::chrono::hours m_hour = std::chrono::hours(0);
    std::chrono::minutes m_minute = std::chrono::minutes(0);
};
