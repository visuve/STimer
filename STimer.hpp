#pragma once

#include <wx/app.h>

#include <chrono>

class ExampleApp : public wxApp
{
public:
    virtual bool OnInit();
private:
    std::chrono::hours m_hour = std::chrono::hours(0);
    std::chrono::minutes m_minute = std::chrono::minutes(0);
};
