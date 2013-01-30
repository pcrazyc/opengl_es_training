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

char* ConfigManager::GetConfigData( ConfigDataType type ) {
	return configData[type];
}

ConfigManager::ConfigManager() {
	for (int i=0; i<ConfigDataMax; i++) {
		for (int j=0; j<100; j++) {
			configData[i][j] = 0;
		}
	}
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
	strData = strData.substr(start+1);
	strcpy(configData[index], strData.c_str());

	printf("%s: %s\n", configKeyArr[index], configData[index]);
}
