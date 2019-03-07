#pragma once
#include "GfxApp.h"
#include "common.h"
#include <map>

/*As we add GFX apps to our catalog, they can be added here.*/

#ifndef APPS
#define APPS \
X(Default, "Default", true)   \
X(Triangle, "Triangle", false) \
X(TriangleLighting, "TriangleLighting", false) \
X(TriangleSpin, "TriangleSpin", false) \
X(CubeSpin, "CubeSpin", false) \
X(CubeTexture, "CubeTexture", false) \
X(SkyboxCubeSpin, "SkyboxCubeSpin", false) \
X(OpenVR, "OpenVR", false) \
X(OculusVR, "OculusVR", false)
#endif

/*	Our AppManager will be aware of all of our possible apps at runtime.
 *	we can switch things up and implement this with the pImpl idiom, but
 *	it didn't really feel necessary.
 */

namespace AppManager {
#ifndef APPS_PARTS
#define APPS_PARTS
#define X(app, name, finished) app,
	enum Apps : size_t { APPS };
#undef X

#define X(app, name, finished) name,
	char const *app_name[] = { APPS };
#undef X

#define X(app, name, finished) finished,
	bool is_implemented[] = { APPS };
#undef X
#endif

	GFXApp * selectApp(AppManager::Apps id)
	{
		GFXApp * target = nullptr;


		if (!is_implemented[id]) {
			std::cout << app_name[id] << " has not yet been implemented!" << std::endl;
		}
		else {
			switch (id)
			{
			case Default:
				target = new GFXApp();
				break;
			case Triangle:
				//TODO: target = new TriangleApp();
				//break;
			case TriangleLighting:
				//TODO: target = new TriangleLightingApp();
				//break;
			case TriangleSpin:
				//TODO: target = new TriangleSpinApp();
				//break;
			case CubeSpin:
				//TODO: target = new CubeSpinApp();
				//break;
			case CubeTexture:
				//TODO: target = new CubeTextureApp();
				//break;
			case SkyboxCubeSpin:
				//TODO: target = new SkyboxCubeSpinApp();
				//break;
			case OpenVR:
				//TODO: target = new OpenVRApp();
				//break;
			case OculusVR:
				//TODO: target = new OculusVRApp();
				//break;
			default:
				target = new GFXApp();
			}
		}

		return target;
	}

	GFXApp * selectApp(const char * appname)
	{
		if (strcmp(appname, app_name[Default]) == 0) {
			return selectApp(Default);
		}
		else {
			std::cout << "No app by name: \"" << appname << "\" has been implemented!" << std::endl;
			return nullptr;
		}
	}

}