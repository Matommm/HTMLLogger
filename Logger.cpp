#include "Logger.h"
#include <iostream>
#include <algorithm>
//#define __DONT_LOG__

size_t Logger::lvl = 0;
size_t Logger::width = 100;
std::ofstream Logger::out_html_log_file;
std::list<std::chrono::high_resolution_clock::time_point> Logger::section_begin_times;
std::list<long long> Logger::elapsed_subsections_times;
std::list<std::array<size_t, 10>> Logger::list_of_warnings;
std::list<long> Logger::begin_section_warnings_positions;

size_t Logger::write_console_log_false_min_lvl = 9999;
bool Logger::write_console_log_Q = true;
size_t Logger::write_html_log_false_min_lvl = 9999;
bool Logger::write_html_log_Q = true;

Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::OpenFileStreamForHTMLLog(const std::string path_to_html_log)
{
#ifndef __DONT_LOG__
	// source: https://www.w3schools.com/howto/howto_js_collapsible.asp
	
	out_html_log_file.open(path_to_html_log, std::ios::out);

	out_html_log_file << "<!DOCTYPE html>" << "\n";
	out_html_log_file << "<html>" << "\n";
	out_html_log_file << "<head>" << "\n";
	out_html_log_file << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" << "\n";
	out_html_log_file << "<style>" << "\n";

	out_html_log_file << ".collapsible{" << "\n";
	out_html_log_file << "	background-color: #252525;" << "\n";
	out_html_log_file << "	color: #dcdcdc;" << "\n";
	out_html_log_file << "	cursor: pointer;" << "\n";
	out_html_log_file << "	padding: 8px;" << "\n";
	out_html_log_file << "	width: 100% ;" << "\n";
	out_html_log_file << "	border-style: solid;" << "\n";
	out_html_log_file << "	text-align: left;" << "\n";
	out_html_log_file << "	outline: none;" << "\n";
	out_html_log_file << "	font-family: Sans-serif;" << "\n";
	out_html_log_file << "	font-size: 12px;" << "\n";
	out_html_log_file << "	border-bottom: 3px solid #474747;" << "\n";
	out_html_log_file << "	border-top: 3px solid #474747;" << "\n";
	out_html_log_file << "	border-left: 3px solid #474747;" << "\n";
	out_html_log_file << "	border-right: 3px solid #474747;" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "" << "\n";

	out_html_log_file << ".active {" << "\n";
	out_html_log_file << "	background-color: #005893;" << "\n";
	out_html_log_file << "	border-bottom: none;" << "\n";
	out_html_log_file << "	border-top: 3px solid #005893;" << "\n";
	out_html_log_file << "	border-left: 3px solid #005893;" << "\n";
	out_html_log_file << "	border-right: 3px solid #005893;" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "" << "\n";

	out_html_log_file << ".collapsible:hover {" << "\n";
	out_html_log_file << "	background-color: #008200;" << "\n";
	out_html_log_file << "	border-bottom: 3px solid #008200;" << "\n";
	out_html_log_file << "	border-top: 3px solid #008200;" << "\n";
	out_html_log_file << "	border-left: 3px solid #008200;" << "\n";
	out_html_log_file << "	border-right: 3px solid #008200;" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "" << "\n";

	out_html_log_file << ".active.collapsible:hover{ " << "\n";
	out_html_log_file << "	background-color: #820000;" << "\n";
	out_html_log_file << "	border-bottom: none;" << "\n";
	out_html_log_file << "	border-top: 3px solid #820000;" << "\n";
	out_html_log_file << "	border-left: 3px solid #820000;" << "\n";
	out_html_log_file << "	border-right: 3px solid #820000;" << "\n";
	out_html_log_file << "}" << "\n";

	out_html_log_file << ".collapsible:after {" << "\n";
	out_html_log_file << "  content: '+';" << "\n";
	out_html_log_file << "  color: white;" << "\n";
	out_html_log_file << "  font-weight: bold;" << "\n";
	out_html_log_file << "  float: right;" << "\n";
	out_html_log_file << "  margin-left: 5px;" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "\n";

	out_html_log_file << ".active:after {" << "\n";
	out_html_log_file << "  content: '-';" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "\n";

	out_html_log_file << ".content{" << "\n";
	out_html_log_file << "	padding: 0 8px;" << "\n";
	out_html_log_file << "	font-size: 12px;" << "\n";
	out_html_log_file << "	font-family: Sans-serif;" << "\n";
	out_html_log_file << "	display: none;" << "\n";
	out_html_log_file << "	overflow: hidden;" << "\n";
	out_html_log_file << "	background-color: #333333;" << "\n";
	out_html_log_file << "	color: #dcdcdc;" << "\n";
	out_html_log_file << "	border-bottom: 3px solid #005893;" << "\n";
	out_html_log_file << "	border-left: 3px solid #005893;" << "\n";
	out_html_log_file << "	border-right: 3px solid #005893;" << "\n";
	out_html_log_file << "}" << "\n";

	out_html_log_file << "</style>" << "\n";
	
	out_html_log_file << "</head>" << "\n";
	out_html_log_file << "<body style=\"background-color:black; \">" << "\n";
	out_html_log_file << "\n";
#endif // !__DONT_LOG__
}

void Logger::CloseFileStreamForHTMLLog()
{
#ifndef __DONT_LOG__
	out_html_log_file << "\n";
	out_html_log_file << "<script>" << "\n";
	out_html_log_file << "var coll = document.getElementsByClassName(\"collapsible\");" << "\n";
	out_html_log_file << "var i;" << "\n";
	out_html_log_file << "" << "\n";
	out_html_log_file << "for (i = 0; i < coll.length; i++) {" << "\n";
	out_html_log_file << "	coll[i].addEventListener(\"click\", function() {" << "\n";
	out_html_log_file << "		this.classList.toggle(\"active\");" << "\n";
	out_html_log_file << "		var content = this.nextElementSibling;" << "\n";
	out_html_log_file << "		if (content.style.display === \"block\") {" << "\n";
	out_html_log_file << "			content.style.display = \"none\";" << "\n";
	out_html_log_file << "		}" << "\n";
	out_html_log_file << "		else {" << "\n";
	out_html_log_file << "			content.style.display = \"block\";" << "\n";
	out_html_log_file << "		}" << "\n";
	out_html_log_file << "	});" << "\n";
	out_html_log_file << "}" << "\n";
	out_html_log_file << "</script>" << "\n";
	out_html_log_file << "" << "\n";
	out_html_log_file << "</body>" << "\n";
	out_html_log_file << "</html>" << "\n";

	out_html_log_file.close();
#endif // !__DONT_LOG__
}

void Logger::EndSection()
{
#ifndef __DONT_LOG__
	if (write_console_log_Q || write_html_log_Q) {
		{//time measurement things
			auto section_end_time = std::chrono::high_resolution_clock::now();
			auto section_begin_time = section_begin_times.back();
			section_begin_times.pop_back();

			auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(section_end_time - section_begin_time).count();

			if (elapsed_subsections_times.back() == 0LL) {
				elapsed_subsections_times.pop_back();
				if(!elapsed_subsections_times.empty())
					elapsed_subsections_times.back() += elapsed_time;
			}
			else {
				long long elapsed_subsections_time = elapsed_subsections_times.back();
				Log("Sum of times of recursive subsection in seconds: " + std::to_string(elapsed_subsections_time / 1000000.));
				elapsed_subsections_times.pop_back();
				if (!elapsed_subsections_times.empty())
					elapsed_subsections_times.back() += elapsed_subsections_time;
			}

			Log("Elapsed time of this section in seconds: " + std::to_string(elapsed_time / 1000000.));
		}

		if (write_console_log_Q) { // console write
			std::string head = "";
			head.append(lvl - 1, '|');
			head.append(std::max(width - (lvl - 1), (size_t)0), '-');

			std::cout << head << std::endl;
		}

		if (write_html_log_Q) // html file write
			if (out_html_log_file.is_open()) {
				out_html_log_file << "</div>" << "\n";
				out_html_log_file << "\n";
				if (!begin_section_warnings_positions.empty()) {
					out_html_log_file.flush();
					auto end_position = out_html_log_file.tellp();
					auto begin_section_warnings_position = begin_section_warnings_positions.back();
					begin_section_warnings_positions.pop_back();

					out_html_log_file.seekp(begin_section_warnings_position);
					if (!list_of_warnings.empty()) {
						auto warnings = list_of_warnings.back();
						for (size_t warning = 0; warning < 10; ++warning) {
							auto num_of_warnings = warnings[warning];
							if (num_of_warnings > 0) {
								out_html_log_file << warning << ":";
								if (num_of_warnings < 10)
									out_html_log_file << "0";
								out_html_log_file << num_of_warnings << ",";
							}
						}
					}

					out_html_log_file.flush();
					out_html_log_file.seekp(end_position);
				}
			}

		lvl--;
	}
	auto warnings = list_of_warnings.back();
	if (!list_of_warnings.empty())
		list_of_warnings.pop_back();
	if (!list_of_warnings.empty()) {
		auto& above_warnings = list_of_warnings.back();
		for (size_t warning = 0; warning < 10; ++warning) {
			above_warnings[warning] += warnings[warning];
		}
	}
#endif // !__DONT_LOG__
}

void Logger::BeginSection(const std::string head_text, const size_t font_size)
{
#ifndef __DONT_LOG__
	list_of_warnings.emplace_back();
	if (write_console_log_Q || write_html_log_Q) {
		lvl++;
		if (write_console_log_Q) { // console write

			std::string head = "";
			head.append(lvl - 1, '|');
			head.append(std::max(width - (lvl - 1), (size_t)0), '-');

			std::cout << head << std::endl;

			std::cout << ReturnHead() << head_text << "\n";
		}


		if (write_html_log_Q) // html file write
			if (out_html_log_file.is_open()) {
				out_html_log_file << "<button class=\"collapsible\">" << "<font size=\""<< font_size <<"px\">" << head_text << "</font>" << " <font color=\"red\">";
				begin_section_warnings_positions.push_back(out_html_log_file.tellp());
				out_html_log_file << "                              ";
				out_html_log_file << "</font></button>" << "\n";
				out_html_log_file << "<div class=\"content\">" << "\n";
			}

		{// time measurement things
			elapsed_subsections_times.push_back(0LL);
			section_begin_times.push_back(std::chrono::high_resolution_clock::now());
		}
	}
#endif // !__DONT_LOG__
}

void Logger::Log(const std::string log_text)
{
#ifndef __DONT_LOG__
	if (write_console_log_Q) // console write
		std::cout << ReturnHead() << log_text << "\n";


	if (write_html_log_Q) // html file write
		if(out_html_log_file.is_open())
			out_html_log_file << "<p>" << log_text << "</p>" << "\n";
#endif // !__DONT_LOG__
}

void Logger::Log(const std::string log_text, const size_t warning)
{
#ifndef __DONT_LOG__
	Log("<font color = \"red\">" + log_text + "</font>");
	if (!list_of_warnings.empty())
		list_of_warnings.back()[std::min(warning, size_t(9))]++;
#endif // !__DONT_LOG__
}

void Logger::DontLogHTML()
{
#ifndef __DONT_LOG__
	if (lvl < write_html_log_false_min_lvl) {
		write_html_log_false_min_lvl = lvl;
		write_html_log_Q = false;
	}
#endif // !__DONT_LOG__
}

void Logger::DoLogHTML()
{
#ifndef __DONT_LOG__
	if (lvl <= write_html_log_false_min_lvl) {
		write_html_log_Q = true;
		write_html_log_false_min_lvl = 9999;
	}
#endif // !__DONT_LOG__
}

void Logger::DontLogConsole()
{
#ifndef __DONT_LOG__
	if (lvl < write_console_log_false_min_lvl) {
		write_console_log_false_min_lvl = lvl;
		write_console_log_Q = false;
	}
#endif // !__DONT_LOG__
}

void Logger::DoLogConsole()
{
	if (lvl <= write_console_log_false_min_lvl) {
		write_console_log_Q = true;
		write_console_log_false_min_lvl = 9999;
	}
}

void Logger::DontLogAll()
{
#ifndef __DONT_LOG__
	BeginSection("Not logging this part");
	Log("???");
	DontLogHTML();
	DontLogConsole();
#endif // !__DONT_LOG__
}

void Logger::DoLogAll()
{
#ifndef __DONT_LOG__
	DoLogHTML();
	DoLogConsole();
	EndSection();
#endif // !__DONT_LOG__
}

std::string Logger::ReturnHead()
{
#ifndef __DONT_LOG__
	std::string head = "";
	head.append(lvl, '|');
	return head;
#endif // !__DONT_LOG__
}
