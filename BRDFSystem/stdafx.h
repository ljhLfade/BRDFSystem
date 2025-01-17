//预编译 stdafx.h : 标准系统包含文件，或是经常使用但不常更改的特定于项目的包含文件
#pragma once
#include <iostream>
#include <windows.h>
#include <direct.h>

//#define _CRT_SECURE_NO_WARNINGS  //屏蔽CRT警告
#define WIN32_LEAN_AND_MEAN   //排除不太常用的API，减小Win32头文件大小，加速生成过程
//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  //某些 CString 构造函数将是显式的

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN  //从Windows头文件中排除极少使用的资料
#endif

// 以下宏定义要求的最低平台。要求的最低平台是具有运行应用程序所需功能的 Windows、Internet Explorer 等产品的
// 最早版本。通过在指定版本及更低版本的平台上启用所有可用的功能，宏可以正常工作。
// 如果必须要针对低于以下指定版本的平台，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef WINVER                          // 指定要求的最低平台是 Windows Vista。
#define WINVER 0x0600           // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINDOWS          // 指定要求的最低平台是 Windows 98。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以适用于 Windows Me 或更高版本。
#endif

#ifndef _WIN32_IE                       // 指定要求的最低平台是 Internet Explorer 7.0。
#define _WIN32_IE 0x0700        // 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif
