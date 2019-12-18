#pragma once
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <array>
#include <chrono>

class Logger
{
public:
	static size_t lvl;
	static size_t width;
	static std::ofstream out_html_log_file;
	static std::list<std::chrono::high_resolution_clock::time_point> section_begin_times;
	static std::list<long long> elapsed_subsections_times;
	
	static size_t write_console_log_false_min_lvl;
	static bool write_console_log_Q;
	static size_t write_html_log_false_min_lvl;
	static bool write_html_log_Q;
	static std::list<std::array<size_t, 10>> list_of_warnings;
	static std::list<long> begin_section_warnings_positions;

	Logger();
	~Logger();

	static void OpenFileStreamForHTMLLog(const std::string path_to_html_log);
	static void CloseFileStreamForHTMLLog();

	static void EndSection();
	static void BeginSection(const std::string head_text, const size_t font_size = 3);
	static void Log(const std::string log_text);
	static void Log(const std::string log_text, const size_t warning);
	static void DontLogHTML();
	static void DoLogHTML();
	static void DontLogConsole();
	static void DoLogConsole();
	static void DontLogAll();
	static void DoLogAll();
	static std::string ReturnHead();

	template <typename containerType>
	static std::string ContainerToString(containerType container) 
	{
		std::string container_string = "{ ";

		if (!container.empty()) {
			for (auto& element : container)
				container_string += ContainerToString(element) + ", ";

			container_string.pop_back();
			container_string.pop_back();
		}

		container_string += " }";

		return container_string;
	};

	static std::string ContainerToString(size_t number) 
	{
		return std::to_string(number);
	};
};

