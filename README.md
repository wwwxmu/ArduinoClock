![小闹钟项目](http://o9k8cdbt4.bkt.clouddn.com/1.jpg)

> 在额济纳支教这一年，给孩子们上了很多Arduino开发的课，也带他们完成了几个Arduino综合项目，下面陆续把这些小项目放上来，欢迎围观~~~*非科班出身，C语言学的不好，望各路大神批评指点。*

###功能介绍
本项目主要是实现基本的闹钟功能：
1. LCD屏幕实时显示当前时间（年、月、日、星期、时、分、秒）以及闹钟的开关；
2. 通过4*4键盘可以设置初始时间及闹钟时间；
3. 通过键盘，还可以查看当前设置的闹钟时间；
4. 当闹钟时间到了，蜂鸣器便会响起，同时LED亮起，可以通过键盘关闭闹钟。

---

###准备材料
- Arduino UNO *1
- LCD 1602A *1
- LCD1602液晶屏转接板（PCF8574AT） *1
- 4*4 矩阵键盘 *1
- RTC I2C时钟模块（DS1307）
- 蜂鸣器 *1
- LED灯 *1
- 面包板 *1
- 跳线若干
- 电烙铁、松香、焊锡等

```
就不给出购买链接了，这些材料在某宝上随便一搜就有~
```
---
###模块接线
- ####键盘与Arduino
    R1-C4  ->  2-9
![键盘与Arduino接线示意图](http://o9k8cdbt4.bkt.clouddn.com/3.jpg)
- ####LCD 1602与转接板
如下图把转接板与LCD1602焊接在一起就行了，或者也可以插在面包板上。
  ![LCD 1602与转接板焊接图](http://o9k8cdbt4.bkt.clouddn.com/2.jpg)  
- ####转接板与Arduino

| PCF8574T|  | Arduino|
|:----:|:---:| :---:|
| GND| ->|GND |
| VCC| -> |5V|
|SDA| -> | A4 |
|SCL| -> | A5 |

- ####DS1307时钟模块与Arduino

| DS1307|  | Arduino|
|:----:|:---:| :---:|
| GND| ->|GND |
| VCC| -> |5V|
|SDA| -> | AREF上一个口|
|SCL| -> | AREF上两个口|

![DS1307时钟模块与Arduino接线示意图](http://o9k8cdbt4.bkt.clouddn.com/4.jpg)

- ####蜂鸣器、LED灯与Arduino

| 蜂鸣器、LED灯|  | Arduino|
|:----:|:---:| :---:|
| 负极| ->|GND |
| 正极| -> |10|

###第三方库
```c
#include <LiquidCrystal_I2C.h> 
#include "RTClib.h"
#include <Keypad.h>
#include <SCoop.h>
```
下载地址：
- `SCoop.h`->[http://www.fuckcode.net/wp-content/uploads/2015/04/SCoop.zip](http://www.fuckcode.net/wp-content/uploads/2015/04/SCoop.zip)
- `RTClib.h`->[https://github.com/adafruit/RTClib](https://github.com/adafruit/RTClib)
- `Keypad.h`-> [http://playground.arduino.cc/uploads/Code/keypad.zip](http://playground.arduino.cc/uploads/Code/keypad.zip)
- `LiquidCrystal_I2C.h`->[https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads](https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads)


###演示视频

###写在最后
1. 每个模块不不清楚怎么用的可以参考我之前写的基础教程；
2. LCD的I2C地址要先确定好（见[http://www.jianshu.com/p/eee98fb5e68f](http://www.jianshu.com/p/eee98fb5e68f)）
3. 实在是想不出其他办法了，才在程序里用了goto语句，接受各路大神批评指正！
