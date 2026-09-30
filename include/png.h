#include <cstring>
#include <string>
#include <libpng/png.h>

typedef unsigned char Byte;

struct image {
	int width;
	int height;
	int channel;
	png_bytep* data;

	image(int width = 0, int height = 0) {
		this->width = width, this->height = height;
		this->data = new png_bytep[height];
		for (int i = 0; i < height; i++) this->data[i] = reinterpret_cast<png_bytep>(new Byte[width * 4]);
	}

	image(const image &a) {
		width = a.width;
		height = a.height;
		channel = a.channel;
		this->data = new png_bytep[height];
		for (int i = 0; i < height; i++) this->data[i] = reinterpret_cast<png_bytep>(new Byte[width * 4]);
		for (int i = 0; i < height; i++) memcpy(this->data[i], a.data[i], width * 4);
	}

	image& operator = (const image &a) {
		for (int i = 0; i < height; i++) delete[] this->data[i];
		delete[] this->data;
		width = a.width;
		height = a.height;
		channel = a.channel;
		this->data = new png_bytep[height];
		for (int i = 0; i < height; i++) this->data[i] = reinterpret_cast<png_bytep>(new Byte[width * 4]);
		for (int i = 0; i < height; i++) memcpy(this->data[i], a.data[i], width * 4);
		return *this;
	}
	
	~image() {
		for (int i = 0; i < height; i++) delete[] this->data[i];
		delete[] this->data;
	}
};

image readImage(std::string path) {
	FILE *fp = fopen(path.c_str(), "rb");
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, fp);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

	image img;
	img.width = png_get_image_width(png_ptr, info_ptr);
	img.height = png_get_image_height(png_ptr, info_ptr);
	img.data = png_get_rows(png_ptr, info_ptr);
	img.channel = png_get_channels(png_ptr, info_ptr);
	return img;
}

void writeImage(std::string path, image img) {
	FILE *fp = fopen(path.c_str(), "wb");
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, img.width, img.height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, img.data);
	png_write_end(png_ptr, NULL);
	fclose(fp);
}

#ifdef ASTC_H
image Texture2DDecodeImage(Json::Value Texture2DBase, string dir) {
	string path = Texture2DBase["m_StreamData"]["path"].asString();
	path = path.substr(path.rfind("/") + 1);
	string data = readFile(dir + "/" + path);
	uint8_t *data2 = (uint8_t*)data.c_str() + Texture2DBase["m_StreamData"]["offset"].asInt();
	int w = Texture2DBase["m_Width"].asInt(), h = Texture2DBase["m_Height"].asInt();
	uint32_t *imgBuffer = new uint32_t[w * h];
	assert(Texture2DDecode(Texture2DBase, data2, imgBuffer));
	image img(w, h);
	for (int i = 0; i < w * h; i++) {
		img.data[h - i / w - 1][i % w * 4] = (imgBuffer[i] >> 16) & 0xff;
		img.data[h - i / w - 1][i % w * 4 + 1] = (imgBuffer[i] >> 8) & 0xff;
		img.data[h - i / w - 1][i % w * 4 + 2] = imgBuffer[i] & 0xff;
		img.data[h - i / w - 1][i % w * 4 + 3] = (imgBuffer[i] >> 24) & 0xff;
	}
	delete[] imgBuffer;
	return img;
}
#endif

#include <GL/glew.h>
struct glTexture {
    int width, height;
    GLuint textureId;
};
glTexture createTextureFromImage(image img) {
    GLubyte* rgba = new GLubyte[img.width * img.height * 4];
    int pos = 0;
    for (int i = img.height - 1; i >= 0; i--)
        for (int j = 0; j < img.width * 4; j++)
            rgba[pos++] = img.data[i][j];

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexture result;
    result.width = img.width;
    result.height = img.height;
    result.textureId = image_texture;
	delete[] rgba;
    return result;
}