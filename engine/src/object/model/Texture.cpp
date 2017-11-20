//
// Created by Андрей on 31.10.17.
//

#include <png.h>
#include <cstdio>
#include <iostream>

#include "engine/Texture.h"

Texture::Texture(std::string && path): path(path) { }

void Texture::load()
{
    if (this->_isLoaded) return;

    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp)
    {
        throw std::out_of_range("file not found: " + path);
    }

    uint8_t header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        fclose(fp);
        throw std::out_of_range("file (" + path + ") is not a PNG");
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_infop end_info = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    uint64_t width  = png_get_image_width(png_ptr, info_ptr);
    uint64_t height = png_get_image_height(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    row_bytes += 3 - ((row_bytes-1) % 4); // выравнивание по 4 байта. требует openGl

    auto image_data = new uint8_t[row_bytes * height];
    auto row_pointers = new uint8_t* [height];

    for (int i = 0; i < height; i++)
    {
        row_pointers[height - 1 - i] = image_data + i * row_bytes;
    }

    png_read_image(png_ptr, row_pointers);

    glGenTextures(1, &_guid);
    glBindTexture(GL_TEXTURE_2D, _guid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint)width, (GLint)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);

    this->_isLoaded = true;
    std::cout << "textured(" << this->_guid << "): " << path << " was loaded" << std::endl;
}

void Texture::unload()
{
    this->_isLoaded = false;
    glDeleteTextures(1, &this->_guid);
    std::cout << "textured(" << this->_guid << ") was unloaded" << std::endl;
}
