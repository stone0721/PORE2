
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

unsigned secret;
unsigned enc_seed;

int orange_rand()
{
    uint64_t uVar1 = ((uint64_t)(secret ^ 0x3b800001) + 0x125e591) * 0x12f81ac;
    secret = (int)(uVar1) + (int)(uVar1 / 0x3b9aca07) * -0x3b9aca07;
    return secret;
}

unsigned op0(unsigned x) { return x ^ 0x12345678; }
unsigned op1(unsigned x) { return (x & 0xff00ff) << 8 | (x & 0xff00ff00) >> 8; }
unsigned op2(unsigned x) { return x + 0x87654321; }
unsigned op3(unsigned x) { return x << 0x10 | x >> 0x10; }
unsigned op4(unsigned x) { return (x & 0xf0f0f0f0) >> 4 | (x & 0x0f0f0f0f) << 4; }
unsigned op5(unsigned x) { return x + 0xedcba988; }
unsigned op6(unsigned x) { return x ^ 0x67616c66; }
unsigned op7(unsigned x) { return x + 0xe9; }

unsigned r_op0(unsigned x) { return x ^ 0x12345678; }
unsigned r_op1(unsigned x) { return (x & 0xff00ff) << 8 | (x & 0xff00ff00) >> 8; }
unsigned r_op2(unsigned x) { return x - 0x87654321; }
unsigned r_op3(unsigned x) { return x << 0x10 | x >> 0x10; }
unsigned r_op4(unsigned x) { return (x & 0xf0f0f0f0) >> 4 | (x & 0x0f0f0f0f) << 4; }
unsigned r_op5(unsigned x) { return x - 0xedcba988; }
unsigned r_op6(unsigned x) { return x ^ 0x67616c66; }
unsigned r_op7(unsigned x) { return x - 0xe9; }

unsigned (*ops[])(unsigned) = {op0, op1, op2, op3, op4, op5, op6, op7};
unsigned (*r_ops[])(unsigned) = {r_op0, r_op1, r_op2, r_op3, r_op4, r_op5, r_op6, r_op7};

typedef unsigned (*func_ptr)(unsigned);
// 记录前八个函数的槽位索引
unsigned func_ord[8];
// 预定义的8个函数地址
func_ptr func_addr_by_number[8] = {op0, op1, op2, op3, op4, op5, op6, op7};
func_ptr r_func_addr_by_number[8] = {r_op0, r_op1, r_op2, r_op3, r_op4, r_op5, r_op6, r_op7};

int init_ops(void)
{
    enc_seed = secret; // 种子////////////////////////////////////////////////////////////////////////////
    // 初始化
    for (int i = 0; i < 8; i++)
    {
        orange_rand();
    }
    return 0;
}

int de_magic2(unsigned *file, int size)
{
    for (int i = 0; i < (uint32_t)(size >> 2); i++)
    {
        orange_rand();
        int temp = r_ops[secret & 7](file[i]);
        if (i == 0 && temp != 0x474e5089)
        {
            return 0;
        }
        if(i == 1 && temp != 0x0a1a0a0d)
        {
            return 0;
        }
        if (i == 2 && temp != 0x0d000000)
        {
            return 0;
        }
        if (i == 3 && temp != 0x52444849)
        {
            return 0;
        }
        file[i] = temp;
        printf("ops解密后的file[%d]:%x \n", i, file[i]);
    }
    return 1;
}

int main()
{
    for (int k = 0; k < 255; k++)
    {
        secret = k;
        init_ops();
        FILE *file = fopen("magic.png.ma", "rb");
        if (file == NULL)
        {
            printf("无法打开文件！\n");
            return 1;
        }
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
        if (de_magic2(buffer, file_size))
        {
            // 写入输出文件
            char outfilename[12] = "kkkmagic.png";
            int num = k;
            outfilename[2] = num % 10 + 0x30;
            num -= num % 10;
            outfilename[1] = (num % 100) / 10 + 0x30;
            num -= (num % 100);
            outfilename[0] = num / 100 + 0x30;
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
        }
        else free(buffer);
    }
    return 0;
}
