#include "dxtk_all.h"
#include "GfxApp.h"
#include "AppMan.h"
#include "common.h"

int main()
{
	AppManager::Apps which = AppManager::Apps::Default;

	GFXApp * App = AppManager::selectApp(which);

	App->main();

	return 0;
}