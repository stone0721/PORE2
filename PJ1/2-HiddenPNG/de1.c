//进行异或解密
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//进行异或解密
void de_magic1(unsigned *file, int size)
{
    for (int i = (uint32_t)(size >> 2) - 1; i > -1; i = i - 1)
    {
        printf("解密前的file[%d]:%x ", i, file[i]);
        if (i > 0)
        {
            file[i] = file[i] ^ file[i - 1];
        }
        printf("异或解密后的file[i]:%x\n", file[i]);
    }
}

int main()
{
    FILE *file = fopen("magic.png.magic", "rb");
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    // 确保文件大小是4的倍数
    long aligned_size = (file_size + 3) & ~3;
    unsigned *buffer = (unsigned *)malloc(aligned_size);
    if (!buffer)
    {
        printf("内存分配失败！\n");
        fclose(file);
        return 1;
    }
    // 初始化buffer
    memset(buffer, 0, aligned_size);
    // 按字节读取文件
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size)
    {
        printf("读取文件失败！预期%ld字节，实际读取%zu字节\n", file_size, bytes_read);
        free(buffer);
        fclose(file);
        return 1;
    }
    fclose(file);
    // 进行解密
    de_magic1(buffer, file_size);
    // 写入输出文件,输出异或解密后的文件
    char outfilename[12] = "magic.png.mag";
    FILE *output = fopen(outfilename, "wb");
    if (!output)
    {
        printf("无法创建输出文件！\n");
        free(buffer);
        return 1;
    }
    // 按字节写入，确保写入原始文件大小
    size_t bytes_written = fwrite(buffer, 1, file_size, output);
    if (bytes_written != file_size)
    {
        printf("写入文件失败！预期%ld字节，实际写入%zu字节\n", file_size, bytes_written);
    }
    fclose(output);
    free(buffer);
    printf("处理完成，输出文件：%s\n", outfilename);
    return 0;
}