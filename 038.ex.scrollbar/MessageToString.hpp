#ifndef MESSAGE_TO_STRING
#define MESSAGE_TO_STRING

class CWindowsMessageToString
{
	public:
		CWindowsMessageToString();
		~CWindowsMessageToString();
		char *GetStringFromMsg( DWORD dwMessage, bool = true );
};

#endif