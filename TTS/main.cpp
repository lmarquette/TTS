#include <sapi.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//init, do this once
	ISpVoice * pVoice = NULL;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	//init done

	//keep saying things here in a loop
	//const wchar_t *input = L"Gorillas live in Central Africa. There are two main species of gorilla, the Eastern Gorilla and the Western Gorilla. The Western Gorilla lives in Western Africa in countries such as Cameroon, the Congo, the Central African Republic, and Gabon. The Eastern Gorilla lives in Eastern African countries such as Uganda and Rwanda.";
	//pVoice->Speak(input, 0, NULL);
	//end of loop

	

	pVoice->Speak(L"This sounds normal <pitch middle = '-600'/> but the pitch drops half way through", SPF_IS_XML, NULL);
	//cleanup
	pVoice->Release();
	pVoice = NULL;
	CoUninitialize();
	return 0;
}