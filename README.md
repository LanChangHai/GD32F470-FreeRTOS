# GD32F470-FreeRTOS

#### 介绍
基于梁山派GD32F470ZG，使用Makefile构建的FreeRTOS工程，使用openocd调试烧录，ARMGCC交叉编译
建议IDE Clion/Vscode+各种插件

目前已支持FreeRTOS,FATFS(管理SD卡),另外修改了一点点启动流程，在进入main函数之前会先初始化梁山派的SDRAM，并且交由FreeRTOS的heap5统一管理，其他开发板食用请注意屏蔽掉相关的代码

#### 软件架构
基于GD官方BSP，结合(CV)STM32F429的codemx生成makefile工程

吐槽一下GD官方好歹算是国产32龙头了，咋能不提供GCC相关的支持呢，启动文件链接文件都是从429嫖来修修补补的
#### 安装教程

1.  安装好armgcc后直接make

#### 使用说明

1. 推荐使用Clion开发体验简直不要太好好嘛？如果Clion出现无法构建项目先点一下makefile文件加载makefile工程后再继续
2. Clion原生支持openocd调试，可添加调试选项

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

欢迎clone共同开发

#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
