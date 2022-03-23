#include "MVGigE.h"
#include "MVImage.h"
#define WMAX 1300
#define HMAX 980

//Function of Image
void img_copy(MVImage* In_img, MVImage* Ou_img);
void img_inv(MVImage* In_img);

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

//int count_num(MVImage* In_img);

double Distance(int x1, int y1, int x2, int y2, int type);
void distance_trans(MVImage* In_img, MVImage* Ou_img, int disty);

int count_num(MVImage* In_img, MVImage* cp_img, int type);

void get_final(MVImage* In_img);