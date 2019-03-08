#pragma once
#include <Windows.h>
#include <string>
#include <istream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class JConfig {

public:
	json in;

	struct AppConfig {
		std::string		appName;
		UINT			wX = 0;
		UINT			wY = 0;
	};

	//TODO
	struct GfxConfig {
		UINT dummy;
	};

	JConfig(std::string filename) 
	{ 
		std::ifstream inFile(filename);
		if (inFile.is_open()){
			inFile >> in;
		}

		inFile.close();
	};

	~JConfig() = default;

	AppConfig GetAppConfig()
	{
		json appConf = in["AppConfig"];
		AppConfig out;
		out.appName = appConf["appName"].get<std::string>();
		out.wX = appConf["wX"].get<UINT>();
		out.wY = appConf["wY"].get<UINT>();

		return out;
	}

};