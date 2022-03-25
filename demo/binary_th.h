#include "MVGigE.h"
#include "MVImage.h"
#define WMAX 1300
#define HMAX 980

//Function of Image
void img_copy(MVImage* In_img, MVImage* Ou_img);
void img_copy_col(MVImage* In_img, MVImage* Ou_img);
void img_inv(MVImage* In_img);
int img_comp_col(MVImage* In1_img, MVImage* In2_img);

//阈值二值化函数
void binary_th(MVImage* In, int th);

//Function of Counter Detection
void counter_detect(MVImage* In_img, MVImage* Ou_img);

//Function of Corrode
void corrode(MVImage* In_img, MVImage* Out_img, int mode);
unsigned char get_max(unsigned char* p, int w, int h);

//Function of expand
void expand(MVImage* In_img, MVImage* Out_img);

//Function of Subtraction
void Subtraction(MVImage* In_img1, MVImage* In_img2, MVImage* Out_img);

int count_num(MVImage* In_img, MVImage* cp_img, int type);
int pdis(int x1, int y1, int x2, int y2);

void get_final(MVImage* In_img);
int show_weight(unsigned char* pDst, unsigned char* ptemp, const char* color,int type);//pDst原图，ptemp是处理后

double Distance(int x1, int y1, int x2, int y2, int type);
void distance_trans(MVImage* In_img, MVImage* Ou_img, int disty);