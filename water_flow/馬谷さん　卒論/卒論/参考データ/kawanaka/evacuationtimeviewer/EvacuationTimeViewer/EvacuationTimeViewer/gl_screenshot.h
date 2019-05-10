/*
���̃\�[�X�́uAkita National College of Technology Yamamoto's Laboratory�v�ɂČ��J����Ă��܂��B
�Q�l�Fhttp://akita-nct.jp/yamamoto/comp/OpenGL/OpenGL.html
*/
// ��ʂ̓��e���r�b�g�}�b�v�t�@�C���ɏo��
//   filename: �o�̓t�@�C����
//   bpp: �s�N�Z��������̃r�b�g���i24, 32�j

#ifndef GL_SCREENSHOT_H_INCLUDED
#define GL_SCREENSHOT_H_INCLUDED

#include <stdlib.h> 
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>

// �r�b�g�}�b�v�̃w�b�_
struct BITMAPFILEHEADER_ {
	//char bfType1;
	//char bfType2;
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfOffBits;
};

struct BITMAPINFOHEADER_ {
	unsigned long  biSize;
	long           biWidth;
	long           biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long           biXPixPerMeter;
	long           biYPixPerMeter;
	unsigned long  biClrUsed;
	unsigned long  biClrImporant;
};

class gl_screenshot {
public:
	gl_screenshot(){};
	~gl_screenshot(){};
	bool screenshot(const char* filename, int bpp = 32)
	{
		const int width = glutGet(GLUT_WINDOW_WIDTH);   // �摜�̑傫��
		const int height = glutGet(GLUT_WINDOW_HEIGHT);
		// �s�N�Z���f�[�^�S�̂̃T�C�Y
		const int datasize = height*((((width*bpp / 8) + 3) >> 2) << 2);
		// �t�@�C���T�C�Y
		const int filesize = 2 + sizeof(BITMAPFILEHEADER_)+sizeof(BITMAPINFOHEADER_)+datasize;

		// �r�b�g�}�b�v�̃w�b�_
		BITMAPFILEHEADER_ bmfh = { filesize, 0, 0, 54, };
		BITMAPINFOHEADER_ bmih = { 40, width, height, 1, bpp, 0, 0, 0, 0, 0, 0, };

		// �f�[�^�̃t�H�[�}�b�g
		int format;
		if (bpp == 24) {
			format = GL_RGB;
		}
		else if (bpp == 32) {
			format = GL_RGBA;
		}
		else {
			std::cerr << "invalid parameter 'bpp'" << std::endl;
			return false;
		}

		// �f�[�^�����炤
		std::vector<GLubyte> buf(datasize);
		//glPixelStorei(GL_PACK_ALIGNMENT, 1);
		//glReadBuffer(GL_FRONT);
		glReadPixels(0, 0, width, height, format, GL_UNSIGNED_BYTE, &buf[0]);

		// RGB �� BGR
		for (int i = 0; i<datasize; i += bpp / 8) {
			std::swap(buf[i], buf[i + 2]);
		}

		// �o��
		std::ofstream fs(filename, std::ios::out | std::ios::trunc | std::ios::binary);
		if (!fs) {
			std::cerr << "fstream::open() failed." << std::endl;
			return false;
		}

		fs.write("BM", 2);
		fs.write(reinterpret_cast<const char*>(&bmfh), sizeof(BITMAPFILEHEADER_));
		fs.write(reinterpret_cast<const char*>(&bmih), sizeof(BITMAPINFOHEADER_));
		fs.write(reinterpret_cast<const char*>(&buf[0]), datasize);
		fs.close();

		return true;
	}
};
#endif
