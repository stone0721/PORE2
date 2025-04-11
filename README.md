# PORE
逆向工程原理PJ



以下是本次PJ的逆向题清单及题目描述。



### 题目一：Guess Master

**题目描述**: `guessMaster`是一个32位ARM的ELF可执行程序。该程序的预期行为依次接收两个数字，并进行校验，但是由于*程序编写的逻辑错误*，该程序无法执行到预期逻辑。请你分析程序，并求解出这两个数字，并在报告中详细说明求解过程。

**评分说明**：

* (30分) 得到第一个数字
* (50分) 得到第二个数字
* (20分) 说明解题过程

**运行方法**: 在虚拟机命令行运行`qemu-arm-static ./guessMaster-arm`，会输出`Direct run is blocked. Game over.`，你需要结合静态分析来获得最终答案。



### 题目二：HiddenPNG

**题目描述**:  `magic`是一个aarch64下的ELF可执行程序，它能够通过**魔法**将PNG文件进行加密。我们在Alice和Bob的通讯记录中截获了一个加密过后的PNG文件`magic.png.magic`，你能帮助我们恢复出原始图片中的内容吗？解密图片内容即可获取本题flag。

**评分说明**：

- (30分) 正确描述`magic`对图片的加密逻辑；
- (30分) 找到`magic`的具体加密函数逻辑并写出其对应的解密函数逻辑；
- (20分) 找出`hidden.png`被加密时所使用的`seed`；
- (20分) 获得完整flag。

**运行方法**: 在虚拟机命令行运行`qemu-aarch64-static ./magic [原始图片内容]`，运行后会产生一个加密后的图片，`magic.png.magic`就是这么产生的。



### 题目三：MathGame

**题目描述**: `mathgame`是一个aarch64下的ELF可执行程序。该程序接收一个flag作为输入。若输入正确的flag，程序会输出：`Congratulations! The flag is solved correctly.`

**评分说明**：

- (40分) 能发现这是什么游戏，并给出详细分析过程
- (60分) 找到最终的flag，并给出详细解题过程

**注**：在题目中藏了一个hint，能够帮助大家大幅减少分析难度。

**运行方法**: 在虚拟机命令行运行`qemu-aarch64-static ./mathgame`，运行后程序会提示你输入数字。具体输入什么数字就要通过逆向求解啦。



### 题目四：PoREMon

**题目描述**: 成为PoREMon训练大师吧！本题提供了一个任天堂GBA游戏的ROM`poremon.gba`，请你逆向和游玩游戏，获取两个藏于其中的flag。

**评分说明**：本题有2阶段，每个阶段都有一个flag，格式为flag{xxx...xxx}

* (60分) 第一阶段flag和解题报告
* (40分) 第二阶段flag和解题报告

**运行方法**: 

1. 在电脑上下载[mGBA](https://mgba.io/downloads.html)模拟器
2. 打开mGBA模拟器，选择File ➢ Load Rom ➢ 选择gba文件即可加载运行。

**注**：`poremon.gba`格式特殊，反编译器可能无法正常加载该程序；因此我们提供了`poremon.elf`程序，该程序是arm32位ELF程序，可以用反编译器加载和分析，但不能被正常运行。

**提示**：以下是一些GBA模拟器相关的宏定义。`KEY_A`和`KEY_B`的默认按键分别为`X`和`Z`，`KEY_UP`、`KEY_DOWN`、`KEY_LEFT`、`KEY_RIGHT`的默认按键为键盘方向键上下左右。

```C
#define KEY_A        0x0001 // 默认按键为X
#define KEY_B        0x0002 // 默认按键为Z
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF
#define KEY_CURR *(volatile unsigned short *)0x04000130
```



### 题目五：Puzzle

**题目描述**: `puzzle`程序是一个aarch64的ELF程序。输入你的flag通过程序检查。本题无需对二进制文件进行修改。flag会随学号不同而不同。

**提示**：flag格式为 flag{[stuid]xxx......xxx}，即外面用flag包围，内部开始11位为你的学号。余下的是一些字符。

**评分说明**：

* (50分) 说明本题目的代码逻辑

* (50分) 正确求解出flag并给出解题过程

**运行方法**: 在虚拟机中执行`qemu-aarch64-static ./puzzle`。程序会提示你输入flag: `Please input your flag:`



### 题目六：SeparatedMaze

**题目描述**: `maze`程序是一个aarch64的ELF程序，其中蕴含了一个迷宫游戏，逆向程序找到正确的flag。flag格式为flag{xxx...xxx}

**评分说明**：

* (50分) 说明此迷宫游戏的规则，给出正确的迷宫全貌

* (50分) 给出正确的flag并附带相关解题脚本

**运行方法**: 在虚拟机中执行`qemu-aarch64-static ./maze`。在漫\~长\~的等待后进入游戏。
