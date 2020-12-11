# stm32_elecpet
 An elecpet project based on stm32f103r6

## 工程架构重大更改
引入STM32CubeMX进行代码初始化生成
注意代码只能写在*USER CODE BEGIN*和*USER CODE END*之间，参考下图
![注释](.\README\main.png)

#### 文件结构
+ elecpet.pdsprj：proteus工程
+ /README：readme文件的多媒体资源
+ /keil：keil5工程
    + /Core
        + /Inc：用户头文件
            + main.h：主函数头文件
            + lcd12864.h：lcd12864显示屏驱动函数头文件
            + word_lib.h：字库头文件
            + graphic.h：图形库头文件
            + key_exit.h：按键中断处理函数头文件
            + （以下为系统文件，不用管）
            + stm32f1xx_it.h：异常中断处理函数
            + stm32f1xx_hal_msp.h
            + system_stm32f1xx.h
        + /Src：用户源文件
            + main.c：主函数以及系统配置函数
            + lcd12864.c：lcd12864显示屏驱动函数库
            + key_exit.c：按键中断处理函数
            + （以下为系统文件，不用管）
            + stm32f1xx_it.c：异常中断处理函数
            + stm32f1xx_hal_msp.c
            + system_stm32f1xx.c
    + /Drivers：系统固件驱动文件夹，不要更改
    + /MDK-ARM：keil5工程文件夹
        + /DebugConfig：调试设置文件
        + /Objects：编译输出文件夹
        + /RTE：系统环境配置文件
        + elecpet.uvprojx：keil5工程文件
    + elecpet.ioc：STM32CubeMX工程
