#include "ConfigManager.h"
#include <stdio.h>
#include "stdlib.h"

ConfigManager* ConfigManager::pSharedConfigManager = NULL;

ConfigManager* ConfigManager::SharedConfigManager() {
	if (pSharedConfigManager == NULL) {
		pSharedConfigManager = new ConfigManager();
	}

	return pSharedConfigManager;
}

void ConfigManager::PurgeConfigManager() {
	if (pSharedConfigManager == NULL) return;

	delete pSharedConfigManager;
	pSharedConfigManager = NULL;
}

int ConfigManager::GetConfigData( ConfigDataType type ) {
	return configData[type];
}

ConfigManager::ConfigManager() {
	LoadConfigData();
}

void ConfigManager::LoadConfigData() {
	FILE *fp = fopen("config.data", "rb");
	char strLine[100];
	for (int i=0; i<100; i++) {
		strLine[i] = 0;
	}
	char ch;
	int index = 0;
	while (1) {
		ch = fgetc(fp);
		if (ch == (char)-1) {
			ChangeConfigData(strLine);
			break;
		}
		if (ch == '\n') {
			ChangeConfigData(strLine);
			
			for (int i=0; i<100; i++) {
				strLine[i] = 0;
			}

			index = 0;
		}

		strLine[index++] = ch;
	}

	fclose(fp);
	fp = NULL;
}

void ConfigManager::ChangeConfigData( string strData ) {
	int start = -1;
	int index = 0;
	for (int i=0; i<ConfigDataMax; i++) {
		start = strData.find(configKeyArr[i]);
		index = i;
		if (start != -1) break;
	}

	if (start == -1) return;

	start = strData.find("=", start);
	configData[index] = atoi(strData.substr(start+1).c_str());

	printf("%s: %d\n", configKeyArr[index], configData[index]);
}
