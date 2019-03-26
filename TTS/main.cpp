#include <sapi.h>
#include <sphelper.h>
#include <atlbase.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

//https://docs.microsoft.com/en-us/previous-versions/windows/desktop/ee431810(v=vs.85)
//https://stackoverflow.com/questions/24846635/using-spvoice-in-c-windows


void lines(/*char **lines, int *n_lines,*/ const char *filename)
{
	string line;
	ifstream readme;
	readme.open(filename);
	while ( getline(readme, line))
	{
		cout << line << endl;
	}
	readme.close();

	cout << "File Closed"<<endl;
}


int main(int argc, char* argv[])
{
	//lines("test.txt");

	string line;
	ifstream readme;
	readme.open("test.txt");
	while (getline(readme, line))
	{
		cout << line << endl;
	}
	readme.close();


	/*
	HRESULT hr = S_OK;
	CComPtr<ISpObjectTokenCategory> cpSpCategory = NULL;
	if (SUCCEEDED(hr = SpGetCategoryFromId(SPCAT_VOICES, &cpSpCategory)))
	{
		CComPtr<IEnumSpObjectTokens> cpSpEnumTokens;
		if (SUCCEEDED(hr = cpSpCategory->EnumTokens(L"Name=Microsoft Anna", NULL, &cpSpEnumTokens)))
		{
			CComPtr<ISpObjectToken> pSpTok;
			while (SUCCEEDED(hr = cpSpEnumTokens->Next(1, &pSpTok, NULL)))
			{
				// do something with the token here; for example, set the voice
				//pVoice->SetVoice(pSpTok, FALSE);
				// NOTE:  IEnumSpObjectTokens::Next will *overwrite* the pointer; must manually release
				pSpTok.Release();
			}

		}*/


		//init, do this once
		ISpVoice * pVoice = NULL;
		CoInitialize(NULL);
		CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
		//init done

		//keep saying things here in a loop
		const wchar_t *input = L"Gorillas live in Central Africa. There are two main species of gorilla, the Eastern Gorilla and the Western Gorilla. The Western Gorilla lives in Western Africa in countries such as Cameroon, the Congo, the Central African Republic, and Gabon. The Eastern Gorilla lives in Eastern African countries such as Uganda and Rwanda.";
		//pVoice->Speak(input, 0, NULL);

		wstring stemp = wstring(line.begin(), line.end()); //stores string into SAPI accessible variable 
		LPCWSTR sw = (LPCWSTR)stemp.c_str(); //variable allowing SAPI to speak stored string
		pVoice->Speak(sw, SPF_DEFAULT, NULL);

		//pitch change
		//pVoice->Speak(L"This sounds normal <pitch middle = '-600'/> but the pitch drops half way through", SPF_IS_XML, NULL);
		//end of loop


		//cleanup
		pVoice->Release();
		pVoice = NULL;
		CoUninitialize();
		
	

	system("pause");
	return 0;
}