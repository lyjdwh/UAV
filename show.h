#ifndef _SHOW_H_
#define _SHOW_H_




void UAVInit(UAVPara *para);
void LoginCheck(UAVPara *para,Account * account,int * flag);
void LoginInit();
void RegisterInit();
void RegisterCheck(UAVPara *para,Account *account,int *flag);
void Forget1Init();
void Forget1Check(UAVPara *para,Account *account,int *flag);
void Forget2Init();
void Forget2Check(UAVPara *para,Account *account,int *flag);


#endif