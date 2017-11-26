//
// Created by Андрей on 22.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_UTILS_H
#define YET_ANOTHER_ENGINE_UTILS_H

#include <cassert>

void dump(const void* memory, uint64_t n, uint32_t columns = 15)
{
    auto p = reinterpret_cast<unsigned const char *>(memory);
    for (uint64_t i = 0; i < n; i++) {
        printf("%02x ", unsigned(p[i]));
        if ((i + 1) % columns == 0)
            printf("\n");
    }
    printf("\n");
}

void* drop_unnecessary_data(const void* data_start,
                            uint64_t block_count,
                            size_t block_offset,
                            size_t offset_size,
                            size_t block_size)
{
    size_t new_data_size = block_count * (block_size - offset_size);
    auto new_data = std::malloc(new_data_size);
    void* temp = new_data;


    const size_t block_tail = block_size - (block_offset + offset_size);
    size_t current_offset = 0;
    for (uint64_t i = 0; i < block_count; i++)
    {
        assert(current_offset <= new_data_size);
        std::memcpy(new_data, data_start, block_offset);
        new_data   = static_cast<char*>(new_data) + block_offset;
        data_start = static_cast<const char*>(data_start) + block_offset + offset_size;
        current_offset += block_offset;

        std::memcpy(new_data, data_start, block_tail);
        new_data   = static_cast<char*>(new_data) + block_tail;
        data_start = static_cast<const char*>(data_start) + block_tail;

        current_offset += block_tail;
    }
    return temp;
}

#endif //YET_ANOTHER_ENGINE_UTILS_H
