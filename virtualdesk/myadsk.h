#pragma once

// Cmyadsk ÃüÁîÄ¿±ê

class Cmyadsk : public CObject
{
public:
	Cmyadsk();
	virtual ~Cmyadsk();
	BOOL SetWallPaper(LPWSTR strPicFile, DWORD dwStyle);
public:
	// Active check
	BOOL CheckEnableActive(void);
};


