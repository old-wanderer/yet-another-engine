//
// Created by Андрей on 31.10.17.
//

#include <png.h>
#include <cstdio>

#include "Texture.h"

Texture::Texture(std::string && path): path(path) { }

void Texture::load()
{
    if (this->_isLoaded) return;

    FILE *fd = fopen(path.c_str(), "rb");
    if (!fd)
        throw std::out_of_range("file not found");

    png_structp png  = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop   info = png_create_info_struct(png);

    png_init_io(png, fd);
    png_read_info(png, info);

    uint64_t width      = png_get_image_width(png, info);
    uint64_t height     = png_get_image_height(png, info);
    uint8_t  color_type = png_get_color_type(png, info);
    uint8_t  bit_depth  = png_get_bit_depth(png, info);

    int32_t number_of_passes = png_set_interlace_handling(png);
    png_read_update_info(png, info);


    auto row_data = new uint8_t*[height];
    for (int i = 0; i < height; i++)
        row_data[i] = new uint8_t[width * 4];

    png_read_image(png, row_data);

    fclose(fd);

    glGenTextures(1, &this->_guid);
    glBindTexture(GL_TEXTURE_2D, this->_guid);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, row_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    for (int i = 0; i < height; i++)
        delete[] row_data[i];
    delete[] row_data;

    glBindTexture(GL_TEXTURE_2D, 0);

    this->_isLoaded = true;
}

void Texture::unload()
{
    this->_isLoaded = false;
    glDeleteTextures(1, &this->_guid);
}
