#include "MVGigE.h"
#include "MVImage.h"
#define WMAX 1300
#define HMAX 980

//Function of Image Copy
void img_copy(MVImage* In_img, MVImage* Ou_img);

//阈值二值化函数
void binary_th(MVImage* In, int th);

//Function of Counter Detection
void counter_detect(MVImage* In_img, MVImage* Ou_img);

//Function of Corrode
void corrode(MVImage* In_img, MVImage* Out_img);
unsigned char get_max(unsigned char* p, int w, int h);
//void hough_circles(MVImage* pro_img);
//void canny_counter(MVImage* In_img, MVImage* Out_img);
