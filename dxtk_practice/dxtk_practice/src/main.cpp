#include "Configurator.h"
#include "dxtk_all.h"
#include "GfxApp.h"
#include "AppMan.h"
#include "common.h"

int main()
{

	JConfig jconf("./config/config.json");

	JConfig::AppConfig appConf = jconf.GetAppConfig();

	GFXApp * App = AppManager::selectApp(appConf.appName.c_str());

	if(App != nullptr) App->main(appConf.wX, appConf.wY);

	return 0;
}