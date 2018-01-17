# INA226
<img src="https://github.com/LJWEB-GIT/INA226/blob/master/Images/INA226.jpg" width="175" align="right"/>INA226 High-Side/Low-Side Bi-Directional I2C Current and Power Monitor library for the _Arduino_.  Texas Instruments produces this family of power monitors and the series is described at on their product page at [INA226](http://www.ti.com/product/INA226).
## INA219 vs INA226
Several breakout boards, tutorials and libraries exist for the INA219, which is the "little brother" to this INA226 chip. While the pin 
layout is similar, with the INA219 having 8 pins and the INA226 having 2 more pins, the internal configuration settings and registers are 
different and require the functions and methods in this library to access.
## Hardware layout
The [datasheet](http://www.ti.com/lit/ds/symlink/ina226.pdf) has examples of how to hook up INA226. The package is a small VSSOP and I used a blank breakout board, some solder paste, a frying pan, desoldering braid, a magnifying glass and quite a bit of time to set up the first breadboard example. I've since seen breakout boards available on the web but since only a few external components are necessary apart from connecting the 10 pins of the INA226 I'll remain with self-build.
## Library description
This library was fork from[SV-Zanshin](https://github.com/SV-Zanshin/INA226).I rewrite the function about auto device detection, which may cause another iic devices cant work. You need use "INA226.begin(IIC_ADDRESS,1,mROhm)" to set IIC address, or the code cannot work.

##support Board##
arduino mini pro 
uno 
leonardo
STM32GENERIC F030x by [huaweiwx](https://github.com/huaweiwx/STM32GENERIC)
