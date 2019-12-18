#include "Logger.h"
#include <iostream>

int DummyFunction() {
	Logger::BeginSection("Dummy function body");

	static int return_int = 0;

	return_int++;
	Logger::Log("return_int: " + std::to_string(return_int));

	Logger::EndSection();
	return return_int;
}

int main(int argc, char* argv[]) {
	Logger::OpenFileStreamForHTMLLog("LogExample.html");

	DummyFunction();
	Logger::BeginSection("Section 1", 5);
	{
		DummyFunction();
		// more code
		Logger::BeginSection("Subsection 1.1");
		{
			int i = 0;
			DummyFunction();
			// more code
			Logger::Log("i: " + std::to_string(i));
			Logger::Log("Some warning.", 1);
		}
		Logger::EndSection();

		// some code
		Logger::BeginSection("Subsection 2.1");
		{
			int j = 0;
			// more code
			Logger::Log("j: " + std::to_string(j));
			Logger::Log("Some warning.", 2);
		}
		Logger::EndSection();
	}
	Logger::EndSection();

	Logger::BeginSection("Section 2");
	Logger::Log("Some text.");
	DummyFunction();
	// some code
	Logger::EndSection();

	Logger::BeginSection("Section 3");
	Logger::Log("Some text.");
	// some code
	Logger::EndSection();

	Logger::CloseFileStreamForHTMLLog();

	std::cout << "Press Enter to continue\n";
	getchar();

	return 0;
}