#include "stdafx.h"
#include "Settings.h"
#include "Config.h"

DBSettings::DBSettings()
{
	dbHost_ = "";
	dbName_ = "";
	dbUser_ = "";
	dbPwd_ = "";
	dbPort_ = "";
	dbCharset_ = "";
	fileName_ = "";

}

DBSettings::DBSettings(std::string filename)
{
	dbHost_ = "";
	dbName_ = "";
	dbUser_ = "";
	dbPwd_ = "";
	dbPort_ = "";
	dbCharset_ = "";
	fileName_ = filename;
}

DBSettings::~DBSettings()
{

}

void DBSettings::loadFile()
{
	if (fileName_!="")
		loadFile(fileName_);
}

void DBSettings::loadFile(std::string filename)
{
	Config config(filename);
	dbHost_ = config.Read<string>("DBHost");
	dbName_ = config.Read<string>("DBName");
	dbUser_ = config.Read<string>("DBUser");
	dbPwd_ = config.Read<string>("DBPwd");
	dbPort_ = config.Read<string>("DBPort");
// 	dbHost_ = config.Read<string>("DBHost");
}

void DBSettings::saveFile()
{
	if (fileName_!="")
		saveFile(fileName_);
}

void DBSettings::saveFile(std::string filename)
{

}