#include "pch.h"
#include "binary_th.h"
#include "stdio.h"
#define INF 0x7f7f7f
#define NSMAX 1000010
#define DM 500
#define W 255
#define B 0

double gradXY[HMAX][WMAX];
double theta[HMAX][WMAX];
double LMV_dst[HMAX][WMAX];

int vis[1300][1300];
int q[NSMAX], qhd = 0, qtl = -1;
int qp[NSMAX][2], pl = 0;
int qg[DM][2], gcnt = 0;
int qy[DM][2], ycnt = 0;

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

void img_inv(MVImage* In_img)
{
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* p = NULL;
    p = (unsigned char*)In_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (*p == 0)
                *p = 255;
            else
                *p = 0;
            p++;
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
                *po = B;
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

//Function of single-Corrode
void corrode(MVImage* In_img, MVImage* Out_img, int mode)
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
            //if (i < 3 || i >= h - 3 || j < 3 || j >= w - 3)
            if (i < 1 || i >= h - 1 || j < 1 || j >=  w - 1)
            {
                *po = W;
                pi++;
                po++;
                continue;
            }
            if (*pi == W)
                *po = W;
           /* else if (*(pi - 1) == W && *(pi + 1) == W &&
                *(pi - w - 1) == W && *(pi - w) == W && *(pi - w + 1) == W &&
                *(pi + w - 1) == W && *(pi + w) == W && *(pi + w + 1) == W)
            {
                if (mode) *po = B;
                else *po = W;
            }/**/
            else if (*(pi - 1) == W || *(pi + 1) == W ||
                *(pi - w - 1) == W || *(pi - w) == W || *(pi - w + 1) == W ||
                *(pi + w - 1) == W || *(pi + w) == W || *(pi + w + 1) == W /*||
                (pi - w - 2) == W || *(pi - w + 2) == W ||
                *(pi + w - 2) == W || *(pi + w + 2) == W ||
                *(pi - w - w) == W || *(pi - w - w - 1) == W || *(pi - w - w + 1) == W ||
                *(pi + w + w) == W || *(pi + w + w - 1) == W || *(pi + w + w + 1) == W ||
                *(pi - 2) == W || *(pi + 2) == W ||
                * (pi - w - w - w) == W || *(pi + w + w + w) == W ||
                *(pi - 3) == W || *(pi + 3) == W*/)
                *po = W;
            else *po = B;
            pi++;
            po++;
        }
    }
}

//Function of expand
void expand(MVImage* In_img, MVImage* Out_img)
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
            //if (i < 3 || i >= h - 3 || j < 3 || j >= w - 3)
            if (i < 1 || i >= h - 1 || j < 1 || j >= w - 1)
            {
                *po = W;
                pi++;
                po++;
                continue;
            }
            if (*pi == B)
                *po = B;
            /* else if (*(pi - 1) == W && *(pi + 1) == W &&
                 *(pi - w - 1) == W && *(pi - w) == W && *(pi - w + 1) == W &&
                 *(pi + w - 1) == W && *(pi + w) == W && *(pi + w + 1) == W)
             {
                 if (mode) *po = B;
                 else *po = W;
             }/**/
            else if (*(pi - 1) == B || *(pi + 1) == B ||
                *(pi - w - 1) == B || *(pi - w) == B || *(pi - w + 1) == B ||
                *(pi + w - 1) == B || *(pi + w) == B || *(pi + w + 1) == B /*||
                (pi - w - 2) == W || *(pi - w + 2) == W ||
                *(pi + w - 2) == W || *(pi + w + 2) == W ||
                *(pi - w - w) == W || *(pi - w - w - 1) == W || *(pi - w - w + 1) == W ||
                *(pi + w + w) == W || *(pi + w + w - 1) == W || *(pi + w + w + 1) == W ||
                *(pi - 2) == W || *(pi + 2) == W ||
                * (pi - w - w - w) == W || *(pi + w + w + w) == W ||
                *(pi - 3) == W || *(pi + 3) == W*/)
                *po = B;
            else *po = W;
            pi++;
            po++;
        }
    }
}

//Function of Subtraction
void Subtraction(MVImage* In_img1, MVImage* In_img2, MVImage* Out_img)
{
    int w, h;
    w = In_img1->GetWidth();
    h = In_img1->GetHeight();

    unsigned char* p1 = NULL;
    unsigned char* p2 = NULL;
    unsigned char* po = NULL;
    p1 = (unsigned char*)In_img1->GetBits();
    p2 = (unsigned char*)In_img2->GetBits();
    po = (unsigned char*)Out_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (((*p1) + (*p2)) > 255)
            {
                *po = 255;
            }
            else
            {
                *po = (*p1) + (*p2);
            }
            p1++;
            p2++;
            po++;
        }
    }

}

//Function of counting number and getting the center
// type: 0 green, 1 yellow;
int count_num(MVImage* In_img, MVImage* cp_img, int type)
{
    if (type == 0)
        gcnt = 0;
    else
        ycnt = 0;
    
    int ret = 0;
    int dir[4][2] = { {-1,0},{0,-1},{0,1},{1,0} };

    img_copy(In_img, cp_img);

    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* p = NULL;
    unsigned char* pc = NULL;
    p = (unsigned char*)In_img->GetBits();
    pc = (unsigned char*)cp_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if ((*pc) == B)
            {
                ret++;
                memset(vis, 0, sizeof(vis));

                int bs = i * w + j;
                q[++qtl] = bs;
                vis[i][j] = 1;

                pl = 0;

                while (qhd <= qtl)
                {
                    int ps = q[qhd];
                    int x = ps / w, y = ps % w;
                    qhd++;

                    qp[pl][0] = x;
                    qp[pl][1] = y;
                    pl++;

                    for (int k = 0; k < 4; k++)
                    {
                        int nx = x + dir[k][0], ny = y + dir[k][1];
                        int ns = nx * w + ny;
                        if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                            continue;
                        if (*(pc - bs + ns) == W)
                            continue;
                        *(pc - bs + ns) = W;
                        q[++qtl] = ns;
                        vis[nx][ny] = 1;
                    }

                }
                if (type == 0)
                {
                    double sumx = 0;
                    double sumy = 0;
                    for (int i = 0; i < pl; i++)
                    {
                        sumx += qp[i][0];
                        sumy += qp[i][1];
                    }
                    sumx /= pl;
                    sumy /= pl;
                    qg[gcnt][0] = sumx;
                    qg[gcnt][1] = sumy;
                    gcnt++;
                }
                else
                {
                    double sumx = 0;
                    double sumy = 0;
                    for (int i = 0; i < pl; i++)
                    {
                        sumx += qp[i][0];
                        sumy += qp[i][1];
                    }
                    sumx /= pl;
                    sumy /= pl;
                    qy[ycnt][0] = sumx;
                    qy[ycnt][1] = sumy;
                    ycnt++;
                }

            }
            p++;
            pc++;
        }
    }
    /*if (type == 0)
    {
        FILE* stream1;
        freopen_s(&stream1, "test1.out", "w", stdout);
        printf("%d\n", gcnt);
        for (int i = 0; i < gcnt; i++)
            printf("%d %d\n", qg[i][0],qg[i][1]);
        fclose(stdout);
    }
    if (type == 1)
    {
        FILE* stream2;
        freopen_s(&stream2, "test2.out", "w", stdout);
        printf("%d\n", ycnt);
        for (int i = 0; i < ycnt; i++)
            printf("%d %d\n", qy[i][0], qy[i][1]);
        fclose(stdout);
        
    }*/
    return ret;
}

//Function of Subtraction
void get_final(MVImage* In_img)
{
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* p = NULL;
    p = (unsigned char*)In_img->GetBits();

    for (int i = 0; i < gcnt; i++)
    {
        int px = qg[i][0], py = qg[i][1];
        int ps = px * w + py;

        for (int j = 0; j < 10; j++)
        {
            for (int r = 0; r < 10; r++)
            {
                int s1 = (j - 5) * w + r - 5;
                *(p + ps + s1) = W;
            }
        }

    }
    for (int i = 0; i < ycnt; i++)
    {
        int px = qy[i][0], py = qy[i][1];
        int ps = px * w + py;
        for (int j = 0; j < 3; j++)
        {
            for (int r = 0; r <= 30; r++)
            {
                int s1 = (j - 1) * w + r - 15;
                //int s2 = (r - 15) * w + (j - 1);
                *(p + ps + s1) = W;
                //*(p + ps + s2) = W;
            }
        }
    }

}

//Function of 
/*int count_num(MVImage* In_img, MVImage* cp_img)
{
    int ret = 0;
    int dir[4][2] = { {-1,0},{0,-1},{0,1},{1,0} };

    img_copy(In_img, cp_img);
    
    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    unsigned char* p = NULL;
    unsigned char* pc = NULL;
    p = (unsigned char*)In_img->GetBits();
    pc = (unsigned char*)cp_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if ((*pc) == B)
            {
                ret++;
                memset(vis, 0, sizeof(vis));

                int bs = i * w + j;
                q[++qtl]=bs;
                vis[i][j] = 1;
                
                while (qhd<=qtl)
                {
                    int ps = q[qhd];
                    int x = ps / w, y = ps % w;
                    qhd++;
                    for (int k = 0; k < 4; k++)
                    {
                        int nx = x + dir[k][0], ny = y + dir[k][1];
                        int ns = nx * w + ny;
                        if (nx < 0 || nx >= h || ny < 0 || ny >= w)
                            continue;
                        if (*(pc - bs + ns) == W)
                            continue;
                        *(pc - bs + ns) = W;
                        q[++qtl] = ns;
                        vis[nx][ny] = 1;
                    }

                }

            }
            p++;
            pc++;
        }
    }
    return ret;

}*/

//Function of Subtraction
/*void Subtraction(MVImage* In_img1, MVImage* In_img2, MVImage* Out_img)
{
    int w, h;
    w = In_img1->GetWidth();
    h = In_img1->GetHeight();

    unsigned char* p1 = NULL;
    unsigned char* p2 = NULL;
    unsigned char* po = NULL;
    p1 = (unsigned char*)In_img1->GetBits();
    p2 = (unsigned char*)In_img2->GetBits();
    po = (unsigned char*)Out_img->GetBits();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (((*p1) + (*p2)) > 255)
            {
                *po = 255;
            }
            else
            {
                *po = (*p1) + (*p2);
            }
            p1++;
            p2++;
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

double Distance(int x1, int y1, int x2, int y2, int type)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
void distance_trans(MVImage* In_img, MVImage* Ou_img, int disty)
{
    int op, distance;

    int w, h;
    w = In_img->GetWidth();
    h = In_img->GetHeight();

    img_copy(In_img, Ou_img);

    unsigned char* pi = NULL;
    unsigned char* po = NULL;
    pi = (unsigned char*)In_img->GetBits();
    po = (unsigned char*)Ou_img->GetBits();
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || j == 0 || i == h - 1)
            {
                pi++;
                po++;
                continue;
            }
            distance = Distance(i, j, i - 1, j - 1, disty);
            op = min(*pi, distance + *(po - w - 1));
            distance = Distance(i, j, i - 1, j, disty);
            op = min(op, distance + *(po - w));
            distance = Distance(i, j, i, j - 1, disty);
            op = min(op, distance + *(po - 1));
            distance = Distance(i, j, i + 1, j - 1, disty);
            op = min(op, distance + *(po + w - 1));
            *po = op;
            pi++;
            po++;
        }
    }

    pi--;
    po--;
    for (int i = h - 1; i >= 0; i--)
    {
        for (int j = w - 1; j >= 0; j--)
        {
            if (i == h - 1 || j == w - 1 || i == 0)
            {
                pi--;
                po--;
                continue;
            }
            distance = Distance(i, j, i + 1, j, disty);
            op = min(*pi, distance + *(po + w ));
            distance = Distance(i, j, i + 1, j + 1, disty);
            op = min(op, distance + *(po + w + 1));
            distance = Distance(i, j, i, j + 1, disty);
            op = min(op, distance + *(po + 1));
            distance = Distance(i, j, i - 1, j + 1, disty);
            op = min(op, distance + *(po - w + 1));
            *po = min(*po, op);
            pi--;
            po--;
        }
    }
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