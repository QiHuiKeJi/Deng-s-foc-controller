

# 灯哥开源FOC双路无刷电机控制器



##   灯哥开源 FOC 控制器是一个由灯哥开源的，基于Apache 2.0 开源协议和ESP32主控芯片的低成本无刷电机双路FOC驱动控制板。

![image1](https://github.com/ToanTech/Deng-s-foc-controller/blob/main/pic/PAFOC_front.jpg)

<img src="https://github.com/ToanTech/Deng-s-foc-controller/blob/main/pic/PAFOC_front.jpg" style="zoom:50%;" />

<img src="https://github.com/ToanTech/Deng-s-foc-controller/tree/main/pic/PAFOC_back.jpg?raw=true" style="zoom:50%;" />

1. 特性

   * 支持双电机
   * 即插即用，原生支持EPS32模块，并预留3*2路PWM输入接口
   * 电压输入12-24V，最大电流？A
   * 集成编码器/霍尔传感器接口
   * 集成I2C，TXD接口

2. 规格

   | 说明         | 参数                              |
   | ------------ | --------------------------------- |
   | 尺寸         | 56*39 mm                          |
   | 输入电压类型 | 直流DC                            |
   | 输入电压     | 12-24V                            |
   | 最大输出电流 | ？                                |
   | 最大功率     | ？                                |
   | 支持电机数   | 2                                 |
   | 主控         | 底面可搭载ESP32开发板lolin32 lite |
   | 编码器支持   |                                   |
   | 拓展接口     |                                   |

3. 接口说明  
   仅针对于本项目所使用的ESP32开发板（型号为lolin32 lite,如下图）
   
   <img src="https://github.com/ToanTech/Deng-s-foc-controller/tree/main/pic/lolin32_lite.jpg?raw=true" style="zoom:50%;" />
   接口引脚如下：

   <img src="https://github.com/ToanTech/Deng-s-foc-controller/tree/main/pic/pafoc_interface.jpg?raw=true" style="zoom:50%;" />
   
   | 接口     | 功能  | 端口         |
   | -------- | ----- | ------------ |
   | 电机一   | 使能  | IO22         |
   |          | 输入  | IO32、33、25 |
   | 电机二   | 使能  | IO12         |
   |          | 输入  | IO26.27.14   |
   | 编码器一 | A/SCL | IO5          |
   |          | B/SDA | IO18         |
   |          | I     | IO15         |
   | 编码器二 | A/SCL | IO23         |
   |          | B/SDA | IO19         |
   |          | I     | IO13         |
| 串口     | TXD   | IO17         |
   |          | RXD   | IO16         |

   ​         
   
4. 项目文件说明

   * Schematic：原理图
   * Gerber：gerber文件可以压缩后直接发给厂家直接打样
   * BOM：PCB元件清单
   * Test sample：简单测试例程