/*******************************
����ͼ��ʾ�ĺ�����ͷ�ļ�
*******************************/

#ifndef _PaintMap_H_
#define _PaintMap_H_

typedef struct{
	int x;     
	int y;        
	int height;			
}LOCATION;
/******
����Ļ�϶�ȡ���ƶ���������λ�ã�x��y����Ϣ
flag��ʾ���Ƿ񱻴���
******/
typedef struct{
	int x;
	int y;
	int flag;
}POINT_STORAGE;
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
			  );

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
				);


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
				);
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
			 );
			 
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
					);
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
				);
				
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
				);
				
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
					);
					
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
	);
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
					);
/****
�������ȡ���
const unsigned int map_scale ,//����ͼ��ģ
const char precision ,//����ͼ��ϸ��
const char *str//����ͼ���λ��
****/
char ReadOrder(
			   const unsigned int map_scale ,//����ͼ��ģ
			   const char precision ,//����ͼ��ϸ��
			   const char *str ,//����ͼ���λ��
			   int *return_flag ,
			   Account *account
			   );

/*****
��ȡ����ͼ���ȡ���ģ��Ϣ
******/
void ReadInformation(
			 	   unsigned int *map_scale , 
				   char *precision , 
				   const char *map_str
				   );

#endif
