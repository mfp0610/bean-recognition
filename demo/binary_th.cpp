#include "pch.h"
#include "binary_th.h"

void binary_th(MVImage* In, int th)
{
	int w,h;

	w = In->GetWidth();//�������ͼ��Ŀ��
	h = In->GetHeight();//�������ͼ��ĸ߶�



	char* p = NULL;
	p =(char*) In->GetBits();
	int i=0, j=0;
	for (i=0;i<w;i++)
	{
		for (j = 0; j < h; j++)
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