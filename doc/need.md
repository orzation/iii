# 需求文档

## 模块

### Camera.c

#### 功能

控制 <b>游戏中</b> 的画面显示内容

- 输出角色与地图等等，负责呈现画面。
- 与字符颜色输出相关。

#### Include

- 使用 Map 来显示画面
- 使用 Color 来获取需要输出的颜色

#### 设计

单例模式：lazy

暂不考虑创建时的并发安全，只有一个控制权

<b>函数:</b>

- `getCamera()` 获取相机实例
- `cleanCamera(Camera)` 清除相机
- `updateCamera(Camera, x, y, Map)` 更新相机坐标并显示画面

### Color.c

#### 功能

记录画面坐标的颜色值，提供 Camera 渲染使用

- 设置画面字符颜色值
- 获取画面字符颜色值

#### Include

无

#### 设计

单例模式：lazy

暂不考虑创建时的并发安全，只有一个控制权

<b>函数:</b>

- `getColorPoint()` 获取优先输出的颜色点信息
- `cleanColor()` 清除所有颜色
- `addColorPoint()` 更新相机坐标并显示画面

暂定用小根堆来维护颜色点信息

### Map.c

#### 功能

地图相关功能，是角色活动的舞台(角色符号是需要加入地图中的)

- 生成地图
- 修改地图
- 角色在地图中
- 获取游戏画面字符二维数组

#### Include

- Role
- Utils(可能)

### Role.c

#### 功能

角色相关

#### Include

#### 设计

### Client.c

联网相关

#### 功能

#### Include

#### 设计

### Menu.c

游戏菜单

#### 功能

#### Include

#### 设计

### iii.c

主函数

#### 功能

#### Include

#### 设计

### Ctrl.c

控制相关

#### 功能

#### Include

#### 设计

## 三方库

由于需要跨 linux 与 windows 平台, 需要使用支撑这些平台的库。

1. `ptread.h`

## 测试相关

测试功能直接以 `xxxxTest.c` 命名即可
