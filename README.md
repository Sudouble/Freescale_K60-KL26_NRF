# Freescale_K60-KL26_NRF
K60和KL26下，NRF接收发送版本，与[SmartCarPlatform](https://github.com/potterhere/SmartCarPlatform) 配套使用

使用NRF2401进行数据的收发

相比对蓝牙、无线串口，价格便宜，能基本上符合日常使用要求。



相关的下位机实现函数见：[NRF_SmartCar.h](https://github.com/potterhere/Freescale_K60-KL26_NRF/blob/master/GPIO_NRF_K60/Board/inc/NRF_SmartCar.h)/[NRF_SmartCar.cpp](https://github.com/potterhere/Freescale_K60-KL26_NRF/blob/master/GPIO_NRF_K60/Board/src/NRF_SmartCar.c)

使用示例见：[示例 main.cpp](https://github.com/potterhere/Freescale_K60-KL26_NRF/blob/master/GPIO_NRF_K60/App/main.c)



ToDo:

- [x] NRF收发数据
- [ ] 蓝牙收发数据