#include <sapi.h>
#include <sphelper.h>
#include <atlbase.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <WinUser.h>
#pragma warning(disable : 4996)
using namespace std;

const long long int buffer_size = 10000;

//https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee431810(v=vs.85)
//https://stackoverflow.com/questions/24846635/using-spvoice-in-c-windows
//svfs flag documentation https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ms720892(v%3Dvs.85)
//virutal key codes https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes

//How to read lines from a file and store them into an array using C
//use fgets and strcpy to lines
int ReadingLines(char **lines, const char *filename)
{
	FILE *fp = fopen(filename, "r");
	int line_count = 0;
	static char buffer[buffer_size];
	//lines = (char**)malloc(sizeof(char*) * buffer_size);

	while (fgets(buffer, sizeof(buffer), fp) != NULL)//Run until it reaches the end of the text file
	{
			lines[line_count] = (char*)malloc(sizeof(char) * buffer_size);
			//printf("%s", buffer);
			strcpy(lines[line_count], buffer); //storing from buffer to lines pointer
			//printf("%s", lines[line_count]);
			line_count++;
	}

	return line_count;
}


int main(int argc, char* argv[])
{
	SHORT GetAsyncKeyState(int vKey);
		
		char **line = new char *[buffer_size];
		//wchar_t **wide_line = new wchar_t *[buffer_size];
		wchar_t wstr[buffer_size];
		//mbstowcs
		//line[0] = (char*)malloc(sizeof(char) * buffer_size);
		//init, do this once
		ISpVoice * pVoice = NULL;
		CoInitialize(NULL);
		CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
		//init done

		int counter = ReadingLines(line, "test.txt");
		
		for (int i = 0; i < counter; i++)
		{
			cout << line[i] << endl;
			mbstowcs(wstr, line[i], buffer_size);
			pVoice->Speak(wstr, SVSFlagsAsync, NULL);
		}
		


		//keep saying things here in a loop
		const wchar_t *input = L"Gorillas live in Central Africa. There are two main species of gorilla, the Eastern Gorilla and the Western Gorilla. The Western Gorilla lives in Western Africa in countries such as Cameroon, the Congo, the Central African Republic, and Gabon. The Eastern Gorilla lives in Eastern African countries such as Uganda and Rwanda.";
		int y;
		//pVoice->Speak(input, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
		for (;;)
		{
			const wchar_t *lev = L"Levent rules";
			const wchar_t *leo = L"Leo is the best league player";
			const wchar_t *daniel = L"Daniel is super smort";
			const wchar_t *james = L"james is a level twenty dwarf with plus ten to drinking";
			const wchar_t *alex = L"alexander chicken butt chicken butt";

			//cin >> y;

			if(GetAsyncKeyState(0x31)) pVoice->Speak(leo, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
			if (GetAsyncKeyState(0x32)) pVoice->Speak(daniel, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
			if (GetAsyncKeyState(0x33)) pVoice->Speak(alex, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
			if (GetAsyncKeyState(0x34)) pVoice->Speak(james, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
			if (GetAsyncKeyState(0x35)) pVoice->Speak(lev, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);
			
			//pVoice->Skip(input, 1000, NULL);
			//pVoice->Pause();
		//	pVoice->Release(;)

			//pVoice->Speak(lev, SVSFlagsAsync | SVSFPurgeBeforeSpeak, NULL);

			//if NumItems is positive, skips forward, negative, skips backward, 0 starts at the beginning

			//wstring stemp = wstring(line.begin(), line.end()); //stores string into SAPI accessible variable 
			//LPCWSTR sw = (LPCWSTR)stemp.c_str(); //variable allowing SAPI to speak stored string
			//pVoice->Speak(sw, SPF_DEFAULT, NULL);

			//pitch change
			//pVoice->Speak(L"This sounds normal <pitch middle = '-600'/> but the pitch drops half way through", SPF_IS_XML, NULL);
			//end of loop

		}
		//cleanup
		//release for when you're done with tts
		/*pVoice->Release();
		pVoice = NULL;
		CoUninitialize();*/
	
		system("pause");
		getchar();
		return 0;
}