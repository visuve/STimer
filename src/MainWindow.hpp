#pragma once

class MainWindow : public wxFrame
{
public:
	MainWindow();

private:
	std::chrono::hours _hour = std::chrono::hours(0);
	std::chrono::minutes _minute = std::chrono::minutes(0);
};