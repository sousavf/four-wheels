#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <vector>
#include <string>

using namespace std;

/// Controla a resolução do jogo.
class ScreenMode
{
public:
	enum Mode
	{
		FS_1024x768_32b,
		FS_1024x768_16b,
		FS_800x600_32b,
		FS_800x600_16b,
		Window800x600
	};

	ScreenMode();
	~ScreenMode();

	bool setMode(Mode mode);
	Mode getMode() const;

protected:
	vector< string > resolutions;
	Mode current;

	const char* getResolution(Mode mode);
	static Mode next(Mode mode);
};

#endif