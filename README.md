# stm32_elecpet
 An elecpet project based on stm32f103r6

文件结构
+ Drivers：系统固件驱动
+ Inc：用户头文件
    + main.h：主函数头文件
    + lcd12864.h：lcd12864显示屏驱动函数头文件
    + word_lib.h：字库头文件
    + graphic.h：图形库头文件
+ MDK-ARM：keil5工程文件夹
+ Src：用户源文件
    + main.c：主函数以及系统配置函数
    + lcd12864.c：lcd12864显示屏驱动函数库
    + stm32f1xx_it.c：异常中断处理函数
