
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <qrencode.h>
 
using std::string;
using namespace std;

#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif

 
 
class QRGenerator
{
public:
	QRGenerator(void);
	~QRGenerator(void);
 
	static void generate(string& text, string& bmpSavedPath,int OUT_FILE_PIXEL_PRESCALER,int VERSION,QRecLevel LEVEL);
};
 

 
#define PIXEL_COLOR_R				0											// Color of bmp pixels
#define PIXEL_COLOR_G				0
#define PIXEL_COLOR_B				0
 
//BMP defines
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef signed long		LONG;
 
#define BI_RGB			0L
 
#pragma pack(push, 2) //2字节对齐，不然会出问题
typedef struct
{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;
 
typedef struct
{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;
 
#pragma pack(pop)
 
QRGenerator::QRGenerator(void)
{
 
}
 
QRGenerator::~QRGenerator(void)
{
 
}
 
void QRGenerator::generate(string& text, string& bmpSavedPath,int OUT_FILE_PIXEL_PRESCALER,int VERSION,QRecLevel LEVEL)
{
	const char*		szSourceSring   = text.c_str();
	const char*		szSavePathSring = bmpSavedPath.c_str();
	unsigned int	unWidth, x, y, l, n, unWidthAdjusted, unDataBytes;
	unsigned char*	pRGBData, *pSourceData, *pDestData;
	QRcode*			pQRC;
	FILE*			f;
 
	if (pQRC = QRcode_encodeString(szSourceSring, VERSION, LEVEL, QR_MODE_8, 1))
	{
		unWidth = pQRC->width; //矩阵的维数
		unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3; //每一个维度占的像素的个数（8），每个像素3个字节
		if (unWidthAdjusted % 4)
			unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
		unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;
 
		// Allocate pixels buffer
		if (!(pRGBData = (unsigned char*)malloc(unDataBytes)))
		{
	
		}
 
		// Preset to white
		memset(pRGBData, 0xff, unDataBytes);
 
 
		// Prepare bmp headers
		BITMAPFILEHEADER kFileHeader;
		kFileHeader.bfType = 0x4d42;  // "BM"
		kFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + unDataBytes;
		kFileHeader.bfReserved1 = 0;
		kFileHeader.bfReserved2 = 0;
		kFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
 
		BITMAPINFOHEADER kInfoHeader;
		kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		kInfoHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;
		kInfoHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER); //负数可以控制图像上下颠倒
		kInfoHeader.biPlanes = 1;
		kInfoHeader.biBitCount = 24;
		kInfoHeader.biCompression = BI_RGB;
		kInfoHeader.biSizeImage = 0;
		kInfoHeader.biXPelsPerMeter = 0;
		kInfoHeader.biYPelsPerMeter = 0;
		kInfoHeader.biClrUsed = 0;
		kInfoHeader.biClrImportant = 0;
 
 
		// Convert QrCode bits to bmp pixels
		pSourceData = pQRC->data;
		for (y = 0; y < unWidth; y++)
		{
			pDestData = pRGBData + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
			for (x = 0; x < unWidth; x++)
			{
				if (*pSourceData & 1)
				{
					for (l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
					{
						for (n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
						{
							*(pDestData + n * 3 + unWidthAdjusted * l)     = PIXEL_COLOR_B;
							*(pDestData + 1 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_G;
							*(pDestData + 2 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_R;
						}
					}
				}
				pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
				pSourceData++;
			}
		}
 
 
		// Output the bmp file
		if (!(fopen_s(&f, szSavePathSring, "wb")))
		{
			fwrite(&kFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
			fwrite(&kInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
			fwrite(pRGBData, sizeof(unsigned char), unDataBytes, f);
			fclose(f);
		}
		
		// Free data
		free(pRGBData);
		QRcode_free(pQRC);
	}
}
 

 
int main()
{
    int PRESCALER = 8;//放大倍数，默认为8
    int ver = 0;//信息量
    QRecLevel level = QR_ECLEVEL_H;//容错率
	string info = "二维码、、qrcode生成666";
	string savePath ="info.bmp";
	QRGenerator::generate(info, savePath,PRESCALER,ver,level);
 
	return 0;
}