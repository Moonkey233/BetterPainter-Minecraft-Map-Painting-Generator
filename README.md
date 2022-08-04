# Minecraft-Map-Painting-Generator
Minecraft Map Painting Generator designed by Moonkey_
2022
未经授权禁止盗用、商用等行为

色差公式理论上Lab Plus为最佳，也是当今最专业运用最广泛的算法，但速度较慢
RGB Plus算法综合效果较好，当图片较大时我们更推荐它
其他公式为对应颜色空间的欧氏距离算法，相对不符合人眼视觉会有较大色差，不建议使用

色阶中彩色为使用MC中能用上的六十几种地图基色
灰阶是只使用R、G、B相同的地图基色
黑白只使用黑白羊毛

抖动算法是一个效果很棒的像素画优化算法，在大分辨率图片上效果更为明显
但它是分辨率换色阶的效果，因此图片分辨率超过256*256像素时，我们强烈建议启用抖动
而低于此分辨率时，可自行对比预览图决定是否启用抖动

背景颜色是png等图片带有alpha透明通道时对半透明底色的叠加算法，默认为黑色

游戏生成区间在-60~319（基于超平坦世界），若是1.17之前版本，请设置为5~255，或根据地图自身需求调整

选定地图起始点坐标，一般X与Z加64后均为128倍数

Java版、以前的游戏版本方块、语言切换和schematic格式文件以及界面美化功能优化等功能工程量较大，仍在开发中，暂不可用


导出的预览图即为functions导入游戏后在地图上看到的样子
functions怎么用？当前版本请自行使用行为包模板打包导入游戏，每次需要更改uuid（不了解行为包B站有很多教程）
clear文件为清除建筑使用的，将覆盖每一个方块为空气
使用/function命令导入文件，请加载目标范围的区块，受限于/function命令一次只能执行10000条，若不止一个文件，请按序号全部导入


感谢使用本软件  作者：Moonkey  开发测试版

Minecraft-Map-Painting-Generator  2022

欢迎您反馈宝贵的建议与意见！
