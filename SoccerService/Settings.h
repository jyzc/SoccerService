#ifndef _SETTINGS_H__
#define _SETTINGS_H__
#pragma once

class DBSettings
{
public:
	DBSettings();
	DBSettings(std::string filename);
	~DBSettings();

	void setDbHost(const std::string & name) {dbHost_ = name;}
	const std::string & dbHost() {return dbHost_;} 
	void setDbName(const std::string & name) {dbName_ = name;}
	const std::string & dbName() {return dbName_;} 
	void setDbUser(const std::string & name) {dbUser_ = name;}
	const std::string & dbUser() {return dbUser_;} 
	void setDbPwd(const std::string & name) {dbPwd_ = name;}
	const std::string & dbPwd() {return dbPwd_;} 
	void setDbPort(const std::string & name) {dbPort_ = name;}
	const std::string & dbPort() {return dbPort_;} 
	void setDbCharset(const std::string & name) {dbCharset_ = name;}
	const std::string & dbCharset() {return dbCharset_;} 
	void setFileName(const std::string & name) {fileName_ = name;}
	const std::string & fileName() {return fileName_;} 


	void loadFile();
	void loadFile(std::string filename);
	void saveFile();
	void saveFile(std::string filename);

private:
	std::string dbHost_;
	std::string dbName_;
	std::string dbUser_;
	std::string dbPwd_;
	std::string dbPort_;
	std::string dbCharset_;

	std::string fileName_;
};


#endif