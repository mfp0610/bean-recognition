#include "pch.h"
#include "binary_th.h"
#include "stdio.h"
#define INF 0x7f7f7f
#define W 255
#define B 0

double gradXY[HMAX][WMAX];
double theta[HMAX][WMAX];
double LMV_dst[HMAX][WMAX];
MVImage grad_img, theta_img;

void img_copy(MVImage* In_img, MVImage* Ou_img)
{
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* pi = NULL;
    unsigned char* po = NULL;
    pi = (unsigned char*)In_img->GetBits();
    po = (unsigned char*)Ou_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            unsigned char tmp;
            tmp = *pi;
            *po = tmp;
            pi++;
            po++;
        }
    }
}

void binary_th(MVImage* In, int th)
{
	int w,h;
	w = In->GetWidth(); //width
	h = In->GetHeight(); //hight

	unsigned char* p = NULL;
	p =(unsigned char*) In->GetBits();
	for (int i = 0;i < h;i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (*p>=th)
			{
				*p = 255;
			}
			else
			{
				*p = 0;
			}
			p++;
		}
	}
}


//Function of Counter Detection
void counter_detect(MVImage* In_img, MVImage* Ou_img)
{   
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* pi = NULL;
    unsigned char* po = NULL;
    pi = (unsigned char*)In_img->GetBits();
    po = (unsigned char*)Ou_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                *po = 0;
                pi++;
                po++;
                continue;
            }
            if (*pi == W)
                *po = B;
            else if (*(pi - 1) == W || *(pi + 1) == W ||
                *(pi - w - 1) == W || *(pi - w) == W || *(pi - w + 1) == W ||
                *(pi + w - 1) == W || *(pi + w) == W || *(pi + w + 1) == W)
                *po = W;
            else *po = B;
            pi++;
            po++;
        }
    }
}

//Function of Corrode
void corrode(MVImage* In_img, MVImage* Out_img)
{
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* pi = NULL;
    unsigned char* po = NULL;
    pi = (unsigned char*)In_img->GetBits();
    po = (unsigned char*)Out_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                *po = 0;
                pi++;
                po++;
                continue;
            }
            if (*pi == W)
                *po = W;
            else if (*(pi - 1) == W && *(pi + 1) == W &&
                *(pi - w - 1) == W && *(pi - w) == W && *(pi - w + 1) == W &&
                *(pi + w - 1) == W && *(pi + w) == W && *(pi + w + 1) == W)
                *po = B;
            else if (*(pi - 1) == W || *(pi + 1) == W ||
                *(pi - w - 1) == W || *(pi - w) == W || *(pi - w + 1) == W ||
                *(pi + w - 1) == W || *(pi + w) == W || *(pi + w + 1) == W)
                *po = W;
            else *po = B;
            pi++;
            po++;
        }
    }
}/*
void corrode(MVImage* In_img, MVImage* Out_img)
{
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* pi = NULL;
    unsigned char* po = NULL;
    pi = (unsigned char*)In_img->GetBits();
    po = (unsigned char*)Out_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                *po = 0;
                pi++;
                po++;
                continue;
            }

            *po = get_max(pi, w, h);

            pi++;
            po++;
        }
    }
}*/

//得到一个像素点周围3*3矩阵的最大点
unsigned char get_max(unsigned char* p, int w, int h)
{
    unsigned char max;
    unsigned char *p1 = p - w - 1;
    max = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (max <= (*p1))
            {
                max = *p1;
            }
            p1++;
        }
        p1 = p1 + w - 3;
    }
    p1 = p;
    return max;
}

/* FILE* stream1;
    freopen_s(&stream1, "test.out", "w", stdout);
    printf("%d\n", *p);
    fclose(stdout);*/

    /* FILE* stream1;
     freopen_s(&stream1, "test.out", "w", stdout);
     for (int i = 0; i < h; i++)
     {
         for (int j = 0; j < w; j++)
         {
             printf("%.4lf \n", gradXY[i][j]);
         }
         printf("\n");
     }*/
     //for (int i = 0; i < h; i++)
     //{
     //    for (int j = 0; j < w; j++)
     //    {
     //        printf("%.4lf \n", theta[i][j]);
     //    }
     //    printf("\n");
     //}
     //fclose(stdout); 