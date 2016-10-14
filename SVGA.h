/*******************************
ͼƬ��ʾ�ĺ�����ͷ�ļ�
*******************************/

#ifndef _SVGA_H_
#define _SVGA_H_
void  PutPixel(int  x,int  y,short color);
short int GetPixel(int x, int y);
void XLine(int x,int y,int length, int color);
void YLine(int x,int y,int length, int color);
unsigned char SetSVGAMode(unsigned int mode);
unsigned char GetSVGAMode();
unsigned int SelectPage(unsigned char index);
void ReturnMode()  ; 
char ReadBmp(int x,int y,char *FileName);
char ReadPartBMP(int x,int y,int x0,int y0,int w,int h,char *FileName);
void SetScreenWidth(unsigned pixels);
void SetShowBegin(int x,int y) ;


/*�ļ�ͷ�ṹ*/
typedef struct{
	int	bfType;				/*  ͨ���� 'BM' �����������ƺ��ж� OS/2 �ı�ʶ����ʲô����*/
	long	 bfSize;		/*  �ļ���С�����ֽ�Ϊ��λ*/
	int	bfReserved1;		/*��������������Ϊ 0*/
	int	bfReserved2;		/*��������������Ϊ 0*/
	long	bfOffBits;		/*���ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ��������*/
							/*�������Ƿǳ����õģ���Ϊλͼ��Ϣͷ�͵�ɫ��ĳ��Ȼ�*/
							/*���ݲ�ͬ������仯�����������ƫ��ֵѸ�ٵĴ��ļ���*/
							/*��ȡ��λ���ݡ� */
} BITMAPFILEHEADER;

/*��Ϣͷ�ṹ*/
typedef struct tagBITMAPINFOHEADER
{
	long	biSize;			/* ��Ϣͷ��С */
	long	biWidth;		/* ͼ���� */
	long	biHeight;		/* ͼ��߶� */
	int	biPlanes;			/*  ����Ϊ 1 */
	int	biBitCount;			/*  ÿ����λ���������� 1, 4, 8 �� 24 */
	long	biCompression;	/*  ѹ������ */
	long	biSizeImage;	/* ʵ��ͼ���С�������� 4 �ı��� */
	long	biXPelsPerMeter;/*  ˮƽ����ÿ�������� */
	long	biYPelsPerMeter;/*  ��ֱ����ÿ��������*/
	long	biClrUsed;		/*  ������ɫ��*/
	long	biClrImportant;	/* ��Ҫ����ɫ�� */
} BITMAPINFOHEADER;


#endif