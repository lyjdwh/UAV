#ifndef _SHOW_H_
#define _SHOW_H_


void UAVInit(UAVPara *para,UAVMap *map);
void LoginCheck(UAVPara *para,Account * account,int * flag);
void LoginInit();
void RegisterInit();
void RegisterCheck(UAVPara *para,Account *account,int *flag);
void Forget1Init();
void Forget1Check(UAVPara *para,Account *account,int *flag);
void Forget2Init();
void Forget2Check(UAVPara *para,Account *account,int *flag);
void HelpInit(char *page);
void HelpCheck(char *page,int *flag);
void ErrorInfo(int error);
void ErrorCheck();
void OpenMapCheck(UAVPara *para,Account *account,int *flag);
void OpenMapInit();
void MainCheck(UAVPara *para,Account *account,int *flag);
void MainInit();
void LogInit();
void LogCheck(UAVPara *para,Account *account,int *flag);

#endif