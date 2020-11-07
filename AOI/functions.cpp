#include "functions.h"
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <direct.h>
#include <share.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>


class config_file_path
{
public:
    std::string strPath;
    config_file_path()
    {
        strPath = getExePath();
        strPath += "\\config.ini";
    }
};

static config_file_path g_config_file_path;
static std::string g_strPath = getExePath();

int open_file()
{
    int nFile = 0;
    char LogFileFullPath[MAX_PATH] = {0};
    std::string strPath = getExePath();
    strPath += "\\log.txt";
    _sopen_s(&nFile,strPath.c_str(),_O_WRONLY|_O_CREAT|O_TRUNC, _SH_DENYNO, _S_IREAD|_S_IWRITE);
    return nFile;
}

static int g_hLogFileHandle = open_file();

int32_t get_server_config_value(std::string strName,std::string strKeyName,int32_t lpDefault,std::string& strFileName)
{
    std::string strPath = g_strPath + "\\" + strFileName;
    return (int32_t)GetPrivateProfileInt(strName.c_str(),strKeyName.c_str(),lpDefault,strPath.c_str());
}

std::string get_server_config_value(std::string strName, std::string strKeyName,LPCTSTR lpDefault, const std::string& strFileName )
{
    std::string strPath = g_strPath + "\\" +strFileName;
    char szVal[MAX_PATH + 1];
    GetPrivateProfileString(strName.c_str(), strKeyName.c_str(), lpDefault, szVal, MAX_PATH, strPath.c_str());
    std::string strVal = szVal;
    return strVal;

}

void set_server_config_value(std::string strName, std::string strKeyName, std::string strValue, const std::string& strFileName)
{
    std::string strPath = g_strPath + "\\" + strFileName;
    WritePrivateProfileString(secName.c_str(), keyName.c_str(), Val.c_str(), strPath.c_str());
}
std::string getExePath()
{
    char buf[MAX_PATH] = {0};
    std::string strBuf = "";
    ::GetModuleFileName( NULL, buf, MAX_PATH);
    strBuf = buf;
    static const char* pszSplit = "/\\";
    size_t found = strBuf.find_last_of(pszSplit);
    if ( std::string::npos != found )
    {
        strBuf = strBuf.substr( 0, found );
    }

    return strBuf;
}
void write_log(const std::string& strInfo)
{
    if(g_hLogFileHandle != -1)
    {
        _write(g_hLogFileHandle,strInfo.c_str(),strInfo.length());
    }
}
