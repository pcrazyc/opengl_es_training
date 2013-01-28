#pragma once

#include <string>

using namespace std;


#define PI 3.14159f

enum ConfigDataType {
	CylinderCircleTriangleCount = 0,
	ConeCircleTriangleCount,
	SphereLongitudeCount,
	SphereLatitudeCount,
	
	ConfigDataMax
};

static const char* configKeyArr[] = {"cylinder_circle_triangle_count"
	, "cone_circle_triangle_count"
	, "sphere_longitude_count"
	, "sphere_latitude_count"
};


class ConfigManager {
public:
	static ConfigManager* SharedConfigManager();
	static void PurgeConfigManager();

	void LoadConfigData();
	int GetConfigData(ConfigDataType type);

	
private:
	ConfigManager();
	void ChangeConfigData(string strData);

	int configData[ConfigDataMax];	
	static ConfigManager* pSharedConfigManager;
};