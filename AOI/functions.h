#pragma once

#include <string>
#include <stdint.h>
#include <windows.h>

int32_t get_server_config_value(std::string strName,std::string strKeyName,int32_t lpDefault,std::string& strFileName);
std::string get_server_config_value(std::string strName, std::string strKeyName,LPCTSTR lpDefault, const std::string& strFileName );
void set_server_config_value(std::string strName, std::string strKeyName, std::string strValue, const std::string& strFileName);
std::string getExePath();
void write_log(const std::string& strInfo);

