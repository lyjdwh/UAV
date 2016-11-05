#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"
#include "account.h"
#include "head.h"
#include "show.h"
#include "PAINTMAP.h"
#include "MakeMap.h"
#include "InfoShow.h"
#include "ProMap.h"
#include "mouse.h"
#include "button.h"


char KEYINTERRUPT;

void interrupt (*Handle)();

void interrupt KeyInterrupt()
{
	int key;
	key = inportb(0x60);
	switch(key)
	{
		case 0x1c:
			KEYINTERRUPT = 13;
			break;
		case 0x1e:
			KEYINTERRUPT = 'a';
			break;
		case 0x1f:
			KEYINTERRUPT = 's';
			break;
		case 0x20:
			KEYINTERRUPT = 'd';
			break;
		case 0x11:
			KEYINTERRUPT = 'w';
			break;
		case 0x10:
			KEYINTERRUPT = 'q';
			break;
		case 0x12:
			KEYINTERRUPT = 'e';
			break;
		case 0x0c:
			KEYINTERRUPT = '-';
			break;
		case 0x0d:
			KEYINTERRUPT = '=';
			break;
		case 0x47:
			KEYINTERRUPT = '7';
			break;
		case 0x48:
			KEYINTERRUPT = '8';
			break;
		case 0x49:
			KEYINTERRUPT = '9';
			break;
		case 0x4b:
			KEYINTERRUPT = '4';
			break;
		case 0x4d:
			KEYINTERRUPT = '6';
			break;
		case 0x50:
			KEYINTERRUPT = '2';
			break;
		case 0x1a:
			KEYINTERRUPT = '[';
			break;
		case 0x1b:
			KEYINTERRUPT = ']';
			break;
		case 0x0f:
			KEYINTERRUPT = 9;
			break;
		case 0x01:
			KEYINTERRUPT = 27;
			break;
		case 0x0e:
			KEYINTERRUPT = 8;
			break;
		default :
			KEYINTERRUPT = 0;
			break;
	}
	outportb(0x20 , 0x20);
}


void CopyBorder(
				)
{

}

int MatrixConvolution(
					int participate[3][3] , 
					int kernel[3][3]
					)
{

}

void NumberPower(int n)
{

}

/********
���Ƶ���ͼ
const unsigned int map_scale , //��ģ
FILE *map , //����ͼ�ļ�ָ��
const int position_x , //���δ���x����ƫ����
const int position_y , //���δ���y����ƫ����
const int x , //��ʾ����ͼ��λ������x
const int y , //��ʾ����ͼ��λ������y
const int zoom , //���ű���
const int zoom_x , //����λ��ѡ������x
const int zoom_y , //����λ��ѡ������y
POINT_STORAGE *storage ,	//������һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
const float angle_point	//������ת�Ƕ�
**********/
void PaintMap(
			  const unsigned int map_scale , //��ģ
			  FILE *map , //����ͼ�ļ�ָ��
			  const int position_x , //���δ���x����ƫ����
    		  const int position_y , //���δ���y����ƫ����
			  const int x , //��ʾ����ͼ��λ������x
			  const int y , //��ʾ����ͼ��λ������y
			  const int zoom , //���ű���
			  const int zoom_x , //����λ��ѡ������x
			  const int zoom_y , //����λ��ѡ������y
			  POINT_STORAGE *storage ,	//������һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
			  const float angle_point	//������ת�Ƕ�
			  )
{   
	int *color[15];		//һ�ζ�ȡ�����ļ������ٶ��ļ��ķ��ʴ���
	int loop_y , loop_x , loop_temp;
	int zoom_temp , temp_y , temp , map_scale_temp;
	short far *VedioBuffer;
	long int position;
	double element_cos , element_sin;
    register int NewPage = 0 , OldPage = 0;
    const double angle = angle_point / 180 * 3.151492654;
    const long int scale_min = 0, 
    			   scale_max = 400;
    const int load_size = 10; 
    int load_y_loop = scale_max / load_size;

    map_scale_temp = sizeof(int) * map_scale;
	VedioBuffer = (short far *)0xA0000000L;
	zoom_temp =sizeof(int) * (scale_max / zoom);
	element_sin = sin(angle);
	element_cos = cos(angle);

    rewind(map);

	for(loop_y = 0 ; loop_y < load_size ; loop_y++)	
		if( (color[loop_y] = (int *) malloc(map_scale_temp)) == NULL )
		{

		}
	OldPage = ( (map_scale - 1 + position_y) * 800l + position_x ) >> 15;
	
	NewPage = OldPage;
    SelectPage(OldPage);

	/******
	���ǵ�����ͼ��ת���漰�˽϶�ĸ��ӵļ��㣬�����ģ��10�򼶣��ʽ���ֱ�ӽǵĵ���ͼ�������������룬����������
	*******/
    if(angle_point != 90)
    {
		load_y_loop += load_y_loop * element_cos; //ʵ����������ӽǱ仯ʱ�����ķ�ΧҲ�б仯
	    for(loop_y = 0 ; loop_y < load_y_loop ; loop_y++)
		{
			int loop_y_temp = loop_y * load_size;
			for(loop_temp = 0 ; loop_temp < load_size ; loop_temp++)
			{
				fseek(map , sizeof(int) * ((((loop_y_temp+loop_temp) / zoom) + y) * (long)map_scale + (long)x) , 0);
		    	fread(color[loop_temp] , zoom_temp , 1 , map);
			}
			for(loop_temp = 0 ; loop_temp < load_size ; loop_temp++)
				for(loop_x = 0 ; loop_x < scale_max ; loop_x++)
					{
						temp = loop_x / zoom;

						temp_y = (loop_y_temp+loop_temp)*element_sin + color[loop_temp][temp]/50 *element_cos;	
						if(temp_y < scale_min || temp_y > scale_max)
							break;
						position=(((long)(temp_y + position_y)) * 800l + loop_x + position_x);
						NewPage = position >> 15;
						position &= 0x0000ffffl;
						if(NewPage != OldPage)
						{
							SelectPage(NewPage);
							OldPage = NewPage;
						}
						VedioBuffer[position] = color[loop_temp][temp];
					}
		}
    }
    else
	    for(loop_y = 0 ; loop_y < load_y_loop ; loop_y++)
		{
			unsigned long int loop_y_temp , x_temp , y_temp = y;
			if(zoom == 2)
			{
				if((*storage).flag == 0)
				{
					x_temp = x + zoom_x ;
					y_temp = y + zoom_y ;
					(*storage).x = zoom_x;
					(*storage).y = zoom_y;
					(*storage).flag = 1;
				}
				else 
				{
					x_temp = x + (*storage).x ;
					y_temp = y + (*storage).y ;				
				}

			}
			else if(zoom == 4)
			{
				y_temp =y+ (*storage).y + zoom_y / 2;
				x_temp =x+ (*storage).x + zoom_x / 2;
			}
			else 
			{
				(*storage).flag = 0;
				x_temp = x;
			}
			loop_y_temp = loop_y * load_size;
			
			for(loop_temp = 0 ; loop_temp < load_size ; loop_temp++)
			{
				fseek(map , sizeof(int) * ((((loop_y_temp+loop_temp) / zoom) + y_temp) * (long)map_scale + (long)x_temp) , 0);
		    	fread(color[loop_temp] , zoom_temp , 1 , map);
			}
			for(loop_temp = 0 ; loop_temp < load_size ; loop_temp++)
			{
				for(loop_x = 0 ; loop_x < scale_max ; loop_x++)
				{
					temp = loop_x / zoom;
					temp_y = (loop_y_temp+loop_temp);

					position=(((long)(temp_y + position_y)) * 800l + loop_x + position_x);
					NewPage = position >> 15;
					position &= 0x0000ffffl;
					if(NewPage != OldPage)
					{
						SelectPage(NewPage);
						OldPage = NewPage;
					}

					if(zoom == 1)
						VedioBuffer[position] = color[loop_temp][temp];
					else 
					{
						/***********
						�ԷŴ��ͼ�����laplace�������ķ�ʽ�Ŵ�
						�����С�������߶���Ϣ��ż���С��еĸ߶���Ϣͨ�������������С��о����ƽ��ֵ���
						************/
						if(((loop_x % zoom) == 0) && ((loop_y_temp + loop_temp) % zoom) == 0)
							VedioBuffer[position] = color[loop_temp][temp];
						else if(((loop_x % zoom) != 0) && ((loop_y_temp + loop_temp) % zoom) != 0)
							VedioBuffer[position] = (color[loop_temp - 1][temp - 1] / 9
													+ color[loop_temp][temp - 1] / 9
													+ color[loop_temp + 1][temp - 1] / 9
													+ color[loop_temp - 1][temp] / 9
													+ color[loop_temp][temp] / 9
													+ color[loop_temp + 1][temp] / 9
													+ color[loop_temp - 1][temp + 1] / 9
													+ color[loop_temp][temp + 1] / 9
													+ color[loop_temp + 1][temp + 1] / 9);	
					}
				}
			}
		}	
	for(loop_y = 0 ; loop_y < load_size ; loop_y++)	
		free(color[loop_y]);
}









/*********
�������ڵ�����ʮ�ֱ��
const int align_left ,	//����ƫ����x
const int align_top , //����ƫ����y
const int width ,	//���ڿ��
const int height , //���ڸ߶�
const int target_scale , //��ǵĴ�С
const int thick ,	//��ǵĺ��
const int color //��ǵ���ɫ
**********/
void CenterTarget(
				 const int align_left ,	//����ƫ����x
				 const int align_top , //����ƫ����y
				 const int width ,	//���ڿ��
				 const int height , //���ڸ߶�
				 const int target_scale , //��ǵĴ�С
				 const int thick ,	//��ǵĺ��
				 const int color //��ǵ���ɫ
				)
{
	register int NewPage = 0 , OldPage = 0;
	short far *VedioBuffer=(short far *)0xA0000000L;
	int loop_x = width / 2 - target_scale / 2 + align_left ,
	    loop_y = height / 2 - target_scale / 2 + align_top; 
	int loop_x_end = loop_x + target_scale ,
		loop_y_end = loop_y + target_scale;
	int thick_y = loop_y + target_scale / 2 - thick / 2,
		thick_x = loop_x + target_scale / 2 - thick / 2;
	int thick_y_end = thick_y + thick , 
		thick_x_end = thick_x + thick;
	unsigned long int position;
	int loop_temp ,
		loop_x_temp = loop_x;
	unsigned long int loop_y_temp;
	
	/******�������*******/
	for(loop_temp = thick_y ; loop_temp < thick_y_end ; loop_temp++)
	{
		loop_y_temp = loop_temp * 800l;
		for(loop_x = loop_x_temp ; loop_x < loop_x_end ; loop_x++)
			{
				position = loop_y_temp + loop_x;
				NewPage = position >> 15;
				position &= 0x0000ffffl;
				if(NewPage != OldPage)
				{
					SelectPage(NewPage);
					OldPage = NewPage;
				}
				VedioBuffer[position] = color;
			}
	}
	/*****�������******/
	for(loop_y ; loop_y < loop_y_end ; loop_y++)
	{
		loop_y_temp = loop_y * 800l;
		for(loop_temp = thick_x ; loop_temp < thick_x_end ; loop_temp++)
		{
			position = loop_y_temp + loop_temp;
			NewPage = position >> 15;
			position &= 0x0000ffffl;
			if(NewPage != OldPage)
			{
				SelectPage(NewPage);
				OldPage = NewPage;
			}
			VedioBuffer[position] = color;
		}
	}

}


/*****
��ֱ�ߣ�ˮƽ����ֱ��
const int x ,	//���x����
const int y ,	//���y����
const int length ,	//ֱ�߳���
const int direction ,	//ֱ�ߵķ���
						1--��
						2--��
						3--��
						4--��
const int color , //ֱ�ߵ���ɫ
int **line //����ֱ�߸��ǳ��ĸ߶ȣ���ɫ����Ϣ
*****/
void PaintLine(
				const int x ,	//���x����
				const int y ,	//���y����
				const int length ,	//ֱ�߳���
				const int direction ,	//ֱ�ߵķ���
				const int color , //ֱ�ߵ���ɫ
				int **line //����ֱ�߸��ǳ��ĸ߶ȣ���ɫ����Ϣ
				)
{
	short far *VedioBuffer=(short far *)0xA0000000L;
	unsigned long int position;
	register int NewPage = 0 , OldPage = 0;
	int loop_temp = 0;
	/*****δ����PutPixel()��������߻����ٶ�******/
	switch(direction)
	{
		case 1 :
			{
				int loop_y = y , 
				loop_y_end = y - length;
				for(loop_y ; loop_y > loop_y_end ; loop_y--)
				{
					position=(((long)(loop_y)) * 800l + x);
					NewPage = position >> 15;
					position &= 0x0000ffffl;
					if(NewPage != OldPage)
					{
						SelectPage(NewPage);
						OldPage = NewPage;
					}
					(*line)[loop_temp++] = VedioBuffer[position];	//����ֱ�߸��ǵ���Ϣ
					VedioBuffer[position] = color;
				}
			}
			break;

		case 2 :
			{
				int loop_x = x , 
				loop_x_end = x + length;
				unsigned long int line_y = ((long)(y)) * 800l;
				for(loop_x ; loop_x < loop_x_end ; loop_x++)
				{
					position=(line_y + loop_x);
					NewPage = position >> 15;
					position &= 0x0000ffffl;
					if(NewPage != OldPage)
					{
						SelectPage(NewPage);
						OldPage = NewPage;
					}
					(*line)[loop_temp++] = VedioBuffer[position];
					VedioBuffer[position] = color;
				}
			}
			break;

		case 3 :
			{
				int loop_y = y , 
				loop_y_end = y + length;
				for(loop_y ; loop_y < loop_y_end ; loop_y++)
				{
					position=(((long)(loop_y)) * 800l + x);
					NewPage = position >> 15;
					position &= 0x0000ffffl;
					if(NewPage != OldPage)
					{
						SelectPage(NewPage);
						OldPage = NewPage;
					}
					(*line)[loop_temp++] = VedioBuffer[position];
					VedioBuffer[position] = color;
				}
			}
			break;

		case 4 :
			{
				int loop_x = x , 
				loop_x_end = x - length;
				unsigned long int line_y = ((long)(y)) * 800l;
				for(loop_x ; loop_x > loop_x_end ; loop_x--)
				{
					position=(line_y + loop_x);
					NewPage = position >> 15;
					position &= 0x0000ffffl;
					if(NewPage != OldPage)
					{
						SelectPage(NewPage);
						OldPage = NewPage;
					}
					(*line)[loop_temp++] = VedioBuffer[position];
					VedioBuffer[position] = color;
				}
			}
			break;
	}
}

/******
��������ѡ���
const int align_left ,	//ƫ����x
const int align_top ,	//ƫ����y
const int x , //ѡ���λ������x
const int y ,	//ѡ���λ������y
const int paint_scale , //����ͼ��ʾ���ģ
LOCATION **lines	//��������ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
******/
void ZoomArea(
			 const int align_left ,	//ƫ����x
			 const int align_top ,	//ƫ����y
			 const int x , //ѡ���λ������x
			 const int y ,	//ѡ���λ������y
			 const int paint_scale , //����ͼ��ʾ���ģ
			 LOCATION **lines	//��������ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
			 )
{
	int *line[4] , loop = 0;
	int begin_x = x + align_left , 
		begin_y = y + align_top , 
		half_paint_scale = paint_scale / 2 ,
		twice_paint_scale = paint_scale * 2;

	for(loop ; loop < 4 ; loop++)
		if((line[loop] = (int *)malloc(sizeof(int)*half_paint_scale)) == NULL)
		{
			exit(0);
		}
	if(*lines == NULL)
	{
		if((*lines = (LOCATION *)malloc(sizeof(LOCATION)*twice_paint_scale)) == NULL)
		{
			exit(0);
		}
	}
	else 
	{
		for(loop = 0 ;loop < twice_paint_scale ; loop++)
		{
			PutPixel((*lines)[loop].x , (*lines)[loop].y, (*lines)[loop].height);
		}
	}
	PaintLine(begin_x , begin_y , half_paint_scale , 2 , 0xff00 , &line[0]);
	for(loop = 0 ; loop < half_paint_scale; loop++)
	{
		/*****�ָ�ֱ��֮ǰ���ǵ���Ϣ******/
		(*lines)[loop].height = line[0][loop];
		(*lines)[loop].x = begin_x + loop;
		(*lines)[loop].y = begin_y;
	}
	PaintLine(begin_x + half_paint_scale , begin_y , half_paint_scale , 3 , 0xff00 , &line[1]);
	for(loop = half_paint_scale; loop < paint_scale ; loop++)
	{
		(*lines)[loop].height = line[1][loop - half_paint_scale];
		(*lines)[loop].x = begin_x + half_paint_scale;
		(*lines)[loop].y = begin_y + loop - half_paint_scale;
	}
	PaintLine(begin_x + half_paint_scale , begin_y + half_paint_scale , half_paint_scale , 4 , 0xff00 , &line[2]);
	for(loop = half_paint_scale ; loop > 0; loop--)
	{
		(*lines)[half_paint_scale - loop + paint_scale].height = line[2][half_paint_scale - loop];
		(*lines)[half_paint_scale - loop + paint_scale].x = begin_x + loop;
		(*lines)[half_paint_scale - loop + paint_scale].y = begin_y + half_paint_scale;
	}
	PaintLine(begin_x , begin_y + half_paint_scale , half_paint_scale , 1 , 0xff00 , &line[3]);
	for(loop = paint_scale / 2 ; loop > 0 ; loop--)
	{
		(*lines)[twice_paint_scale - loop].height = line[3][half_paint_scale - loop];
		(*lines)[twice_paint_scale - loop].x = begin_x;
		(*lines)[twice_paint_scale - loop].y = begin_y + loop;
	}
	//CenterTarget(begin_x , begin_y , half_paint_scale, half_paint_scale , 16 , 2 , 0xff00);
	for(loop = 0 ; loop < 4 ;loop++)
		free(line[loop]);
}

/*******
�������ͼ��ʾ����
const int align_left ,	//����ͼƫ����x 
const int align_top , //����ͼƫ����y
const int width , //����ͼ���
const int height //����ͼ�߶�
*********/
void ClearViewport(
					const int align_left ,	//����ͼƫ����x 
					const int align_top , //����ͼƫ����y
					const int width , //����ͼ���
					const int height //����ͼ�߶�
					)
{
	short far *VedioBuffer=(short far *)0xA0000000L;
	long int position;
	int loop_x , loop_y;
	int width_new = width + 5 ,//�����5px�Ա�֤�ܹ������ȫ
		height_new = height + 5;
	register int NewPage = 0 , OldPage = 0;

	OldPage = ( (align_top) * 800l + align_left ) >> 15;
	NewPage = OldPage;
	SelectPage(OldPage);
	
	for(loop_y = -5 ; loop_y < height_new ; loop_y++)
	{
		for(loop_x = -15 ; loop_x < width_new ; loop_x++)
		{
			position=(((long)(loop_y + align_top)) * 800l + loop_x + align_top);
			NewPage = position >> 15;
			position &= 0x0000ffffl;
			if(NewPage != OldPage)
			{
				SelectPage(NewPage);
				OldPage = NewPage;
			}
			VedioBuffer[position] = 0x0000;
		}
	}
}

/*****
��ȡ������������
const char order , //�������
const unsigned int map_scale , //����ͼ��ģ
const int x ,	//��ʾ����ͼλ��x
const int y , //��ʾ����ͼλ��x
const int align_left , //ƫ����x
const int align_top ,	//ƫ����y
const int paint_scale ,//��ʾ���ڹ�ģ
const int zoom , //���ű���
const int zoom_dis_x ,//����ѡ�����ʾ��Ϣλ��x
const int zoom_dis_y ,//����ѡ�����ʾ��Ϣλ��y
const int angle_point , //��ת�Ƕ�
FILE *map ,  //����ͼ�ļ�ָ��
LOCATION **lines ,	//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
int *zoom_pos_x ,	//����λ��ѡ������x
int *zoom_pos_y ,	//����λ��ѡ������y
int *speed_zoom , //���ſ��ƶ��ٶ�
const int speed_zoom_x , //���ſ��ƶ��ٶ���ʾ����x
const int speed_zoom_y	//���ſ��ƶ��ٶ���ʾ����y
*******/
void ReadOrderZoom(
					const char order , //�������
					const unsigned int map_scale , //����ͼ��ģ
					const int x ,	//��ʾ����ͼλ��x
					const int y , //��ʾ����ͼλ��x
					const int align_left , //ƫ����x
					const int align_top ,	//ƫ����y
					const int paint_scale ,//��ʾ���ڹ�ģ
					const int zoom , //���ű���
					const int zoom_dis_x ,//����ѡ�����ʾ��Ϣλ��x
					const int zoom_dis_y ,//����ѡ�����ʾ��Ϣλ��y
					const int angle_point , //��ת�Ƕ�
					FILE *map ,  //����ͼ�ļ�ָ��
					LOCATION **lines ,	//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
					int *zoom_pos_x ,	//����λ��ѡ������x
					int *zoom_pos_y ,	//����λ��ѡ������y
					int *speed_zoom , //���ſ��ƶ��ٶ�
					const int speed_zoom_x , //���ſ��ƶ��ٶ���ʾ����x
					const int speed_zoom_y	//���ſ��ƶ��ٶ���ʾ����y
				)
{


	switch(order)
	{
		case '8':
			//PaintMap(map_scale,map,50,50,x,y,zoom,angle_point);
			(*zoom_pos_y) -= (*speed_zoom);
			if((*zoom_pos_y) <= 0)
				(*zoom_pos_y) = 0;
			ZoomArea(align_left ,align_top , *zoom_pos_x , *zoom_pos_y ,paint_scale,lines);
			ConstructeStr("","(d,d)" , *zoom_pos_x , *zoom_pos_y , zoom_dis_x , zoom_dis_y);
			// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
			break;
		case '6':
			(*zoom_pos_x) += (*speed_zoom);
			if((*zoom_pos_x) >= paint_scale / 2 - 1)
				(*zoom_pos_x) = paint_scale / 2 - 1;
			//PaintMap(map_scale,map,50,50,x,y,zoom,angle_point);
			ZoomArea(align_left ,align_top , *zoom_pos_x , *zoom_pos_y ,paint_scale,lines);
			ConstructeStr("","(d,d)" , *zoom_pos_x , *zoom_pos_y , zoom_dis_x , zoom_dis_y);
			// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
			break;
		case '2':
			(*zoom_pos_y) += (*speed_zoom);
			if((*zoom_pos_y) >= paint_scale / 2 - 1)
				(*zoom_pos_y) = paint_scale / 2 - 1;
			//PaintMap(map_scale,map,50,50,x,y,zoom,angle_point);
			ZoomArea(align_left ,align_top , *zoom_pos_x , *zoom_pos_y ,paint_scale,lines);
			ConstructeStr("","(d,d)" , *zoom_pos_x , *zoom_pos_y , zoom_dis_x , zoom_dis_y);
			// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
			break;
		case '4':
			(*zoom_pos_x) -= (*speed_zoom);
			if((*zoom_pos_x) <= 0)
				(*zoom_pos_x) = 0;
			//PaintMap(map_scale,map,50,50,x,y,zoom,angle_point);
			ZoomArea(align_left ,align_top ,*zoom_pos_x , *zoom_pos_y ,paint_scale,lines);
			ConstructeStr("","(d,d)" , *zoom_pos_x , *zoom_pos_y , zoom_dis_x , zoom_dis_y);
			// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
			break;
		case '7' : 
			(*speed_zoom) ++;
			if((*speed_zoom) >= paint_scale / 2)
				(*speed_zoom) = paint_scale / 2;
			ConstructeStr("","d" , *speed_zoom , 0 , speed_zoom_x , speed_zoom_y);
			break;
		case '9':
			(*speed_zoom) --;
			if((*speed_zoom) <= 0)
				(*speed_zoom) = 1;
			ConstructeStr("","d" , *speed_zoom , 0 , speed_zoom_x , speed_zoom_y);
			break;
	}
}

/*******
��ȡ����ͼ�ƶ�����
const char order , //�������
const unsigned int map_scale ,	//����ͼ��ģ 
int *x ,	//����ͼ��ʾ����x
int *y , 	//����ͼ��ʾ����y
const int align_left , //���Ӵ���ƫ����x
const int align_top ,//���Ӵ���ƫ����y
const int paint_scale ,//���Ӵ��ڹ�ģ
const int bar_length , //����ʮ�ֱ�ǹ�ģ
const int bar_thick , //����ʮ�ֱ�Ǻ��
const int bar_color ,//����ʮ�ֱ����ɫ
const int zoom , //���ű���
const int zoom_x , //���ſ�λ������x
const int zoom_y ,//����λ��ѡ������y
POINT_STORAGE *storage ,//��һ������λ����Ϣ����
LOCATION **lines ,//���ſ�߽縲������
const int angle_point , //����ͼ��ת��
FILE *map ,  //����ͼ�ļ�ָ��
const int speed , //���˻��ƶ��ٶ�
const int center , //�������������ڵ���ͼ���������λ��
const int position_x , //��ʾ���˻�λ����Ϣ����x
const int position_y ,//��ʾ���˻�λ����Ϣ����y
const int max_speed //���˻��������ٶ�
********/
void ReadOrderMove(
					const char order , //�������
					const unsigned int map_scale ,	//����ͼ��ģ 
					int *x ,	//����ͼ��ʾ����x
					int *y , 	//����ͼ��ʾ����y
					const int align_left , //���Ӵ���ƫ����x
					const int align_top ,//���Ӵ���ƫ����y
					const int paint_scale ,//���Ӵ��ڹ�ģ
					const int bar_length , //����ʮ�ֱ�ǹ�ģ
					const int bar_thick , //����ʮ�ֱ�Ǻ��
					const int bar_color ,//����ʮ�ֱ����ɫ
					const int zoom , //���ű���
					const int zoom_x , //���ſ�λ������x
					const int zoom_y ,//����λ��ѡ������y
					POINT_STORAGE *storage ,//��һ������λ����Ϣ����
					LOCATION **lines ,//���ſ�߽縲������
					const int angle_point , //����ͼ��ת��
					FILE *map ,  //����ͼ�ļ�ָ��
					const int speed , //���˻��ƶ��ٶ�
					const int center , //�������������ڵ���ͼ���������λ��
					const int position_x , //��ʾ���˻�λ����Ϣ����x
					const int position_y ,//��ʾ���˻�λ����Ϣ����y
					const int max_speed //���˻��������ٶ�
				)
{
	switch(order)
	{
		case 'a':
		case 'A':
			(*x) -= speed; 
			if((*x) < 0)
				(*x) = 0;
			else 
			{
				if(angle_point != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				} 
				PaintMap(map_scale,map,align_left , align_top , (*x),(*y),zoom,zoom_x,zoom_y,storage,angle_point);
				// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				// ConstructeStr("(d,d)" , (*x) - center , (*y) - center , position_x , position_y);
			}
			break;
			
		case 'd':
		case 'D':
			(*x) += speed;			
			if((*x) > (map_scale -  paint_scale ))
				(*x) = map_scale -  paint_scale ;
			else
			{	
				if(angle_point != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				}
				PaintMap(map_scale,map, align_left , align_top ,(*x),(*y),zoom,zoom_x,zoom_y,storage,angle_point);
				// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				// ConstructeStr("(d,d)" , (*x) - center , (*y) - center , position_x , position_y);
			}
			break;
		
		case 'w':
		case 'W':
			(*y) -= speed; 
			if((*y) < 0)
				(*y) = 0;
			else
			{
				if(angle_point != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale  , paint_scale );
				}
				PaintMap(map_scale,map,align_left , align_top ,(*x),(*y),zoom,zoom_x,zoom_y,storage,angle_point);
				// CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				// ConstructeStr("(d,d)" , (*x) - center , (*y) - center , position_x , position_y);
			}
			break;
		
		case 's':
		case 'S' :
			(*y) += speed;  
			if((*y) > (map_scale -  paint_scale))
				(*y) = map_scale -  paint_scale ;
			else
			{
				if(angle_point != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale ,  paint_scale );
				}
				PaintMap(map_scale,map,align_left , align_top ,(*x),(*y),zoom,zoom_x,zoom_y,storage,angle_point);
			}
			break;
	}
	/*****������˻�������ͷ����ת������������*****/
	if (angle_point == 90)
	{
		ZoomArea(align_left ,align_top , zoom_x , zoom_y ,paint_scale,lines);
	}
	CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
	ConstructeStr("","(d,d)" , (*x) - center , (*y) - center , position_x , position_y);
}

/******
��ȡ���˻������ٶ���Ϣ
const char order , //�������
const int speed_x , //�ٶ���ʾ��Ϣλ��x
const int speed_y ,//�ٶ���ʾ��Ϣλ��y
const int max_speed , //����ٶ�
int *speed //���˻������ٶ�
******/
void ReadOrderSpeed(
					const char order , //�������
					const int speed_x , //�ٶ���ʾ��Ϣλ��x
					const int speed_y ,//�ٶ���ʾ��Ϣλ��y
					const int max_speed , //����ٶ�
					int *speed //���˻������ٶ�
					)
{
	switch(order)
	{	
		case '[' :
		case '{':
			(*speed) ++ ;
			if((*speed) >= max_speed)
				(*speed) = max_speed; 
			ConstructeStr("","d" , *speed , 0 , speed_x , speed_y);
			break;
		case ']' :
		case '}':
			(*speed) -- ;
			if((*speed) <= 0)
				(*speed) = 0;
			ConstructeStr("","d" , *speed , 0 , speed_x , speed_y);
			break;
	}
}

/*******
���Ƶ���ͼ���ź�ĵ���
const char order , //�������
const unsigned int map_scale , //����ͼ��ģ
const int x ,//���˻�λ��x
const int y ,//���˻�λ��y 
const int align_left , //ƫ����x
const int align_top ,//ƫ����y
const int paint_scale ,//���Ӵ��ڹ�ģ
const int bar_length , //�������ı�Ǵ�С
const int bar_thick , //�������ı�Ǻ��
const int bar_color ,//�������ı����ɫ
int *zoom , //���ű���
const int zoom_pos_x ,//���Ŵ���λ��x 
const int zoom_pos_y ,//���Ŵ���λ��y
POINT_STORAGE *storage ,//��һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
LOCATION **lines ,//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
const int angle_point , //����ͼ��ת��
FILE *map ,  //����ͼ�ļ�ָ��
const int speed , //���˻������ٶ�
const int center , //���Ӵ�������ڵ���ͼ��λ��
const int position_x , //������Ϣ��ʾλ��x
const int position_y ,	//������Ϣ��ʾλ��y
const int max_speed	//�������ٶ�
******/
void ReadOrderPaintZoom(
					const char order , //�������
					const unsigned int map_scale , //����ͼ��ģ
					const int x ,//���˻�λ��x
					const int y ,//���˻�λ��y 
					const int align_left , //ƫ����x
					const int align_top ,//ƫ����y
					const int paint_scale ,//���Ӵ��ڹ�ģ
					const int bar_length , //�������ı�Ǵ�С
					const int bar_thick , //�������ı�Ǻ��
					const int bar_color ,//�������ı����ɫ
					int *zoom , //���ű���
					const int zoom_pos_x ,//���Ŵ���λ��x 
					const int zoom_pos_y ,//���Ŵ���λ��y
					POINT_STORAGE *storage ,//��һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
					LOCATION **lines ,//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
					const int angle_point , //����ͼ��ת��
					FILE *map ,  //����ͼ�ļ�ָ��
					const int speed , //���˻������ٶ�
					const int center , //���Ӵ�������ڵ���ͼ��λ��
					const int position_x , //������Ϣ��ʾλ��x
					const int position_y ,	//������Ϣ��ʾλ��y
					const int max_speed	//�������ٶ�
	)
{
	switch(order)
	{
		case '=':
			(*zoom) *= 2;
			if((*zoom) > 4)
				(*zoom) = 4;
			else
			{
				/*****��Ϊ����ͼ�ľ��ȵ�����Щ�㲻�ử����һ����Ҫ����******/
				ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				PaintMap(map_scale,map,align_left , align_top ,x,y,(*zoom),zoom_pos_x,zoom_pos_y,storage,angle_point);
				CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				ConstructeStr("","d" , (*zoom) , 0 , position_x , position_y);
			}
			break;
		
		case '-':
			(*zoom) /= 2;
			if((*zoom) < 1)
				(*zoom) = 1;				
			else
			{
				ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				PaintMap(map_scale,map,align_left , align_top ,x,y,(*zoom),zoom_pos_x,zoom_pos_y,storage,angle_point);
				CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				ConstructeStr("","d" , (*zoom) , 0 , position_x , position_y);
			}
			break;
	}

	ZoomArea(align_left ,align_top , zoom_pos_x , zoom_pos_y ,paint_scale,lines);
}

/*********
��ȡ����ͼ��ת�Ƕ�
const char order , //�������
const unsigned int map_scale , //����ͼ��ģ
const int x ,//����ͼ��ģ
const int y , //���˻�λ��y 
const int align_left , //ƫ����x
const int align_top ,//ƫ����x
const int paint_scale ,//���Ӵ��ڹ�ģ
const int bar_length , //�������ı�Ǵ�С
const int bar_thick , //�������ı�Ǻ��
const int bar_color ,//�������ı����ɫ
const int zoom , //���ű���
const int zoom_x , //���Ŵ���λ��x 
const int zoom_y ,//���Ŵ���λ��y
POINT_STORAGE *storage ,//��һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
LOCATION **lines ,//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
int *angle_point , //����ͼ��ת��
FILE *map ,  //����ͼ�ļ�ָ��
const int speed , //����ͼ�ļ�ָ��
const int center , //���Ӵ�������ڵ���ͼ��λ��
const int gre_x , //��ת����Ϣ��ʾλ��x
const int gre_y ,//��ת����Ϣ��ʾλ��x
const int max_speed//�������ٶ�
*********/
void ReadOrderAngle(
					const char order , //�������
					const unsigned int map_scale , //����ͼ��ģ
					const int x ,//����ͼ��ģ
					const int y , //���˻�λ��y 
					const int align_left , //ƫ����x
					const int align_top ,//ƫ����x
					const int paint_scale ,//���Ӵ��ڹ�ģ
					const int bar_length , //�������ı�Ǵ�С
					const int bar_thick , //�������ı�Ǻ��
					const int bar_color ,//�������ı����ɫ
					const int zoom , //���ű���
					const int zoom_x , //���Ŵ���λ��x 
					const int zoom_y ,//���Ŵ���λ��y
					POINT_STORAGE *storage ,//��һ������λ����Ϣ��һ��ͼ���ܹ�����ԭ��λ�û�ԭ
					LOCATION **lines ,//����ѡ�����߸��ǲ��ֵ���ɫ���߶ȣ���λ����Ϣ
					int *angle_point , //����ͼ��ת��
					FILE *map ,  //����ͼ�ļ�ָ��
					const int speed , //����ͼ�ļ�ָ��
					const int center , //���Ӵ�������ڵ���ͼ��λ��
					const int gre_x , //��ת����Ϣ��ʾλ��x
					const int gre_y ,//��ת����Ϣ��ʾλ��x
					const int max_speed//�������ٶ�
					)
{
	switch(order)
	{
		case 'q':
		case 'Q':
			(*angle_point) += 5;
			if((*angle_point) > 135)
				(*angle_point) = 135;
			else
			{	
				if((*angle_point) != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				}
				PaintMap(map_scale,map,align_left , align_top ,x,y,zoom,zoom_x,zoom_y,storage ,(*angle_point));
				CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				ConstructeStr("","dg" , (*angle_point) , 0 , gre_x , gre_y);
			}
			break;
		
		case 'e':
		case 'E':
			(*angle_point) -= 5;
			if((*angle_point) < 45)
				(*angle_point) = 45;
			else
			{
				if((*angle_point) != 90)
				{
					ClearViewport(align_left , align_top ,  paint_scale  ,  paint_scale );
				}
				PaintMap(map_scale,map,align_left , align_top ,x,y,zoom,zoom_x,zoom_y,storage ,(*angle_point));
				CenterTarget(align_left , align_top ,  paint_scale  ,  paint_scale , bar_length , bar_thick , bar_color);
				ConstructeStr("","dg" , (*angle_point) , 0 , gre_x , gre_y);
			}
			break;
	}
	if((*angle_point) == 90)
		ZoomArea(align_left ,align_top , zoom_x , zoom_y ,paint_scale,lines);
}

/******
����ҳ�������ʾҳ��
*******/
void OrderHelp(char *path)
{
	short mouse_buffer[16*16];
	Coord mouse;
	char a;
	
	ReadBmp(0,0,path);
	MouseInit();
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCopy(&mouse,mouse_buffer);
	MouseShow(&mouse);
	MouseReshow(&mouse,mouse_buffer);
	
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&a);
		MouseCopy(&mouse,mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,mouse_buffer);
		if(Button(47,40,147,103)==1)//����
		{
			return;
		}
	}
}

void AskDelete()
{
	short mouse_buffer[16*16];
	Coord mouse;
	char a;
	
	MouseInit();
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCopy(&mouse,mouse_buffer);
	MouseShow(&mouse);
	MouseReshow(&mouse,mouse_buffer);
}


/******
��������ĵ������
 char *flag �������Ŀ�ı�ǣ������������
 char *str ����ҳ��ı���ͼ
 ����    ����
  0       �������
  1		 �Զ�
  2		ɾ������
  3		��ʾ����
  5		������ݿ�
  6     ���ͼ���
****/
int MouseProcess(
				char *flag , 
				char *str ,
				Account *account
				)
{
	short mouse_buffer[16*16];
	Coord mouse;
	char a;
	
	MouseInit();
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	ReadMouse(&mouse.x,&mouse.y,&a);
	MouseCopy(&mouse,mouse_buffer);
	MouseShow(&mouse);
	MouseReshow(&mouse,mouse_buffer);
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&a);
		MouseCopy(&mouse,mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,mouse_buffer);
		if(Button(70,510,175,550)==1)//����
		{
			(*flag) = 0;
			return 0;
		}
		if(Button(206,510,311,550)==1)//�Զ�
		{
			(*flag) = 1;
			Handle = getvect(0x09);
			setvect(0x09 , KeyInterrupt);
			return 1;
		}
		if(Button(345,510,450,550)==1)//ɾ��
		{
			FILE *delete_map;
			if(!(delete_map = fopen(str , "w")))
			{
				
			}
			(*flag) = 2;
			fclose(delete_map);
			DeleteMap(account);
			AddLog(account , "Delete A Map Data!ɾ����һ���ļ���");
			return 2;
		}
		if(Button(483,510,588,550)==1)//����
		{
			(*flag) = 3;
			OrderHelp(".\\back\\MapHelp.bmp");
			return 3;
		}
		if(Button(620,510,735,550)==1)//�˳�
		{
			(*flag) = 4;
			exit(1);
		}
		if(Button(465,20,775,490)==1)//���ݿ�
		{
			(*flag) = 5;
			return 5;
		}
		if(Button(50,58,450,458)==1)//����ͷ��
		{
			(*flag) = 6;
			return 6;
		}
	}
}


/****
�������ȡ���
const unsigned int map_scale ,//����ͼ��ģ
const char precision ,//����ͼ��ϸ��
const char *str//����ͼ���λ��
����	����
0		�������
-1 		���ɾ��������ͼ���ݱ���գ�������
****/
char ReadOrder(
			   const unsigned int map_scale ,//����ͼ��ģ
			   const char precision ,//����ͼ��ϸ��
			   const char *str ,//����ͼ���λ��
			   int *return_flag ,
			   Account *account 
			   )
{
	char ch = 0;
	
	FILE *map;
	LOCATION *lines = NULL;
							
	char target;
	char flag = -1;
	char rand_order[6] = {'a' , 's' , 'd' , 'w','[',']'};
	char count = 0;
	
	POINT_STORAGE storage;
	
	const int position_x = 580 , 
			  position_y = 250 ,
			  zoom_x = 580 , 
			  zoom_y = 300 ,
			  gre_x = 580 , 
			  gre_y = 400 ,
			  speed_x = 580 ,
			  speed_y = 200 ,
			  speed_zoom_x = 580 ,
			  speed_zoom_y = 450 ,
			  zoom_dis_x = 580 , 
			  zoom_dis_y = 350 ,
			  align_left = 50 ,
			  align_top = 58 , 
			  paint_scale = 400 ,
			  bar_length = 20 , 
			  bar_thick = 2 ,
			  bar_color = 0xfc00 , 
			  max_speed = 50 ,
			  center = map_scale / 2 - paint_scale / 2;

	int x = center,
	    y = x, 
	    zoom_pos_x = paint_scale / 4 , zoom_pos_y = paint_scale / 4 , zoom = 1 , angle_point = 90 , speed = 10 , speed_zoom = 1 ;
			  
	srand((unsigned int)time(NULL));		  
	map=fopen(str , "rb");
	storage.flag = 0;
	
	while(1)
	{
		ReadBmp(0 , 0 ,".\\back\\Fly.bmp");
	
		ConstructeStr("��ͼ��ģ��","(d,d)" , map_scale , map_scale , 580 , 50);
		ConstructeStr("��ͼ���ȣ�","d" , precision , 0 , 580 , 150);
		ConstructeStr("�Ӵ���ģ��","(d,d)" , paint_scale , paint_scale , 580 , 100);
		ConstructeStr("����λ�ã�","(d,d)" , x - center , y - center , position_x , position_y);
		ConstructeStr("����λ�ã�","(d,d)" , zoom_pos_x , zoom_pos_y , 580 , 350);
		ConstructeStr("�����ٶȣ�","d" , speed_zoom , 0 , zoom_x , zoom_y);
		ConstructeStr("��ת�Ƕȣ�","dg" , angle_point , 0 , gre_x , gre_y);
		ConstructeStr("�����ٶȣ�","d" , speed , 0 , speed_x , speed_y);
		ConstructeStr("���ű�����","d" , zoom , 0 , speed_zoom_x , speed_zoom_y);
		
		PaintMap(map_scale ,
				 map ,
				 align_left , 
				 align_top ,
				 x ,
				 y ,
				 zoom ,
				 zoom_pos_x ,
				 zoom_pos_y ,
				 &storage ,
				 angle_point);
		CenterTarget(align_left , 
					 align_top ,  
					 paint_scale ,  
					 paint_scale , 
					 bar_length , 
					 bar_thick , 
					 bar_color);
		ZoomArea(align_left ,
				 align_top ,
				 zoom_pos_x , 
				 zoom_pos_y ,
				 paint_scale , 
				 &lines
				 );
		
		while(1)
		{	
			if(flag == 3)
			{
				ch = 0;
				flag = -1;
				break;
			}
			else if(flag == 1)
			{
				if(count == 0)
				{
					ch = rand_order[rand()%6];
					count = 10;
				}
				else count--;
				if(KEYINTERRUPT == 27)
					exit(1);
				if(KEYINTERRUPT == 8)//backspace
				{
					setvect(0x09 , Handle);
					KEYINTERRUPT = 0;
					flag = -1;
					count = 0;
				}
			}
			else
				ch = getch();
			switch(ch)
			{
				case 13:
						target = MouseProcess(&flag , str , account);
						switch(target)
						{
							case 0:
								(*return_flag) = 8;
								return 0;
								break;
							case 2:
								(*return_flag) = 8;
								return 0;
								break;
							default:
								break;
						}
					ch = 0;
					break;
				case '2':
				case '4':
				case '6':
				case '8':
				case '7':
				case '9':
					if(angle_point == 90)
						ReadOrderZoom(
							ch, 
							map_scale , 
							x ,
							y , 
							align_left , 
							align_top ,
							paint_scale ,
							zoom ,
							zoom_dis_x ,
							zoom_dis_y , 
							angle_point , 
							map ,  
							&lines ,
							&zoom_pos_x ,
							&zoom_pos_y ,
							&speed_zoom ,
							zoom_x , 
							zoom_y
						);
					break;
				case '[':
				case '{':
				case '}':
				case ']':
					ReadOrderSpeed(
						ch , 
						speed_x , 
						speed_y ,
						max_speed ,
						&speed
						);
					break;
				case 'a':
				case 'A':
				case 'S':
				case 'W':
				case 'D':
				case 's':
				case 'd':
				case 'w':
					ReadOrderMove(
						ch , 
						map_scale , 
						&x ,
						&y , 
						align_left , 
						align_top ,
						paint_scale ,
						bar_length , 
						bar_thick , 
						bar_color ,
						zoom , 
						zoom_pos_x ,
						zoom_pos_y ,
						&storage ,
						&lines ,
						angle_point , 
						map ,  
						speed , 
						center , 
						position_x , 
						position_y , 
						max_speed
					);
					break;			
				case '-':
				case '+':
				case '_':
				case '=':
					if(angle_point == 90)
						ReadOrderPaintZoom(
							ch , 
							map_scale , 
							x ,
							y , 
							align_left , 
							align_top ,
							paint_scale ,
							bar_length , 
							bar_thick , 
							bar_color ,
							&zoom , 
							zoom_pos_x ,
							zoom_pos_y ,
							&storage ,
							&lines ,
							angle_point , 
							map ,  
							speed , 
							center , 
							speed_zoom_x , 
							speed_zoom_y , 
							max_speed
							);
					break;
				
				case 'e':
				case 'Q':
				case 'E':
				case 'q':
					if(zoom == 1)
						ReadOrderAngle(
							ch , 
							map_scale , 
							x ,
							y , 
							align_left , 
							align_top ,
							paint_scale ,
							bar_length , 
							bar_thick , 
							bar_color ,
							zoom , 
							zoom_pos_x ,
							zoom_pos_y ,
							&storage ,
							&lines ,
							&angle_point , 
							map ,  
							speed , 
							center , 
							gre_x , 
							gre_y , 
							max_speed
						);
					break;
				
				case 27:
					exit(1);
					break;
				
				default :
					break;
			}	
		}
	}

	fclose(map);
	
	return 0;
}


/*****
��ȡ����ͼ���ȡ���ģ��Ϣ
******/
void ReadInformation(
			 	   unsigned int *map_scale , 
				   char *precision , 
				   const char *map_str
				   )
{
	FILE *map;
	map = fopen(map_str , "ab+");
	fseek(map , (long)(sizeof(int) + sizeof(char)) , 2);
	fread(map_scale , sizeof(int) , 1 , map);
	fread(precision , sizeof(char) , 1 , map);
	fclose(map);
}
