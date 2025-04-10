

flagBias = 23
primeBias = 28
list_3 = [] # 仅包含0，1，2的数组
list = [0,2,0,1,2,1,0,2,1,0,1,2,0,2,0,1,2,1,2,0,1,0,2,1,0,2,0,1,2,1,0,2,1,0,1,2,0,2,1,0,2,1,2,0,1,0,1,2,0,2,0,1,2,1,0,2,1,0,1,2,0,2]   # list_3加上对应质数的数组,预期全为0
list_unsflag = [] # 对应unsflag
flag = []
prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29,31, 37, 41, 43, 47, 53, 59, 61, 67, 71,73, 79, 83, 89, 97, 101, 103, 107, 109,113, 127, 131, 137, 139, 149, 151, 157,163, 167, 173, 179, 181, 191, 193,197,199, 211, 223, 227, 229, 233, 239,241, 251, 257, 263, 269, 271,277,281,283, 293]
for i in range(62):
    for j in range(3):
        index = (primeBias + i) % 62
        num = ( j + prime[index]) % 3
        if num == list[i]:
            list_3.append(j)
for i in range(62):
    print (list[i], end = ' ')
print ("\n")

for i in range(62):
    min = (i * 3) % 27
    max = min + 3
    k = 0
    while True:
        candidate = list_3[i] + 3 * k
        if candidate > max:
            candidate = min + list_3[i] % 3
            break
        if candidate >= min:
            break
        k += 1
    list_unsflag.append(candidate)

for i in range(62):
    print (list_unsflag[i], end = ' ')
print ("\n")

for i in range(62):
    val = (list_unsflag[i] - flagBias) % 27
    flag.append(val + 0x40)

for i in range(62):
    print (chr(flag[i]), end = '')
print ("\n")