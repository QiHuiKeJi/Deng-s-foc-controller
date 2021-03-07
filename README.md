# 灯哥开源FOC双路无刷电机控制器

​     灯哥开源 FOC 控制器是一个由灯哥开源的，基于Apache 2.0 开源协议和ESP32主控芯片的低成本无刷电机双路FOC驱动控制板。双路总功率 240W，单路最大功率 120W，支持绝大部分的云台电机。编码器方面，支持常见IIC和ABI制式编码器。是一个好用又便宜的双路无刷FOC驱动器，点击查看 [效果视频](https://www.bilibili.com/video/BV1Hz4y127FL/)。

​     灯哥开源无刷FOC目前的发展受到灯哥开源团队的深度支持，目前已经针对这块控制板开发出了[灯哥开源无刷四足机器人](https://github.com/ToanTech/py-apple-bldc-quadruped-robot)，DIY视频和效果见：[B站](https://www.bilibili.com/video/BV1kV411i76z/)，例如平衡车，倒立摆等等，敬请关注。

* 目前该主控板已经上架淘宝，售价60RMB，是焊接好调试好的成品，出售即包括 ESP32 ；直接到手可用。每一块我都要给我的小伙伴补贴的，只希望大家能畅快玩起来，有需要大家可以猛击[淘宝链接](https://item.taobao.com/item.htm?spm=a230r.1.14.9.34c9688aRXg2O6&id=638363654504&ns=1&abbucket=20#detail)

* 开源工作不易，希望大家多点 Star ,视频多一键三联！！！
* 板子的使用、配置教程，请访问：[灯哥开源 FOC 讨论论坛](http://leggedrobot.cn/forum.php?mod=forumdisplay&fid=52)

![image1](https://github.com/ToanTech/Deng-s-foc-controller/blob/main/pic/PAFOC_front.jpg)

1. 特性

   * 支持双电机
   * 即插即用，原生支持EPS32模块，并预留3*2路PWM输入接口
   * 电压输入12-24V，单路最大功率120W
   * 集成编码器/霍尔传感器接口
   * 集成I2C，TXD接口

2. 规格

   | 说明         | 参数                                     |
   | ------------ | ---------------------------------------- |
   | 尺寸         | 56*39 mm                                 |
   | 输入电压类型 | 直流DC                                   |
   | 输入电压     | 12-24V                                   |
   | 最大功率     | 单路120W 双路共240W                      |
   | 支持电机数   | 2                                        |
   | 主控         | 底面可搭载ESP32开发板 lolin32 lite       |
   | 编码器支持   | IIC方式以及ABI方式编码器(AS5600、AS5047) |
   | 拓展接口     | 串口（可以通过串口对FOC板子进行控制）    |
   
3. 接口说明  
   本项目所使用的ESP32开发板，型号为lolin32 lite。板子接口引脚简图如下，更多请参照B站和论坛教程：
   ![image1](https://github.com/ToanTech/Deng-s-foc-controller/blob/main/pic/pafoc_interface.jpg)
   
4. 项目文件说明

   * Dengs FOC V1.0 DIY资料：BOM、原理图、PCB、Gerber
   * Dengs FOC V1.0 测试例程：8个灯哥开源FOC开环、闭环、应用方面的测试视频
   * 灯哥开源FOC专用 Arduino 编程环境：我整合好的可以直接用于开发此 FOC 的编程环境，详细使用方法请见论坛中的教程