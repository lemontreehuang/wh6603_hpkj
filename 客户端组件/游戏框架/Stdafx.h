#pragma once

//////////////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//////////////////////////////////////////////////////////////////////////////////
// add by hxh 20160801
#define POINTER_64 __ptr64

typedef void *PVOID;
typedef void * POINTER_64 PVOID64;


//MFC �ļ�
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>

//////////////////////////////////////////////////////////////////////////////////
//���Ӵ���

//��ý���
#pragma comment (lib,"Winmm.lib")

//���Ӵ���
#ifndef _DEBUG
#ifndef _UNICODE
	#pragma comment (lib,"../../���ӿ�/Ansi/WHImage.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/GameEngine.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCore.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/SkinControl.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/ShareControl.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/PlatformData.lib")
	//#pragma comment (lib,"../../���ӿ�/Ansi/GameProperty.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/AvatarControl.lib")
	//#pragma comment (lib,"../../���ӿ�/Ansi/VideoService.lib")
#else
	#pragma comment (lib,"../../���ӿ�/Unicode/WHImage.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/GameEngine.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCore.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/SkinControl.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/ShareControl.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/PlatformData.lib")
	//#pragma comment (lib,"../../���ӿ�/Unicode/GameProperty.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/AvatarControl.lib")
	//#pragma comment (lib,"../../���ӿ�/Unicode/VideoService.lib")
#endif
#else
#ifndef _UNICODE
	#pragma comment (lib,"../../���ӿ�/Ansi/WHImageD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/GameEngineD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCoreD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/SkinControlD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/ShareControlD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/PlatformDataD.lib")
	//#pragma comment (lib,"../../���ӿ�/Ansi/GamePropertyD.lib")
	#pragma comment (lib,"../../���ӿ�/Ansi/AvatarControlD.lib")
	//#pragma comment (lib,"../../���ӿ�/Ansi/VideoServiceD.lib")
#else
	#pragma comment (lib,"../../���ӿ�/Unicode/WHImageD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/GameEngineD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCoreD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/SkinControlD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/ShareControlD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/PlatformDataD.lib")
	//#pragma comment (lib,"../../���ӿ�/Unicode/GamePropertyD.lib")
	#pragma comment (lib,"../../���ӿ�/Unicode/AvatarControlD.lib")
	//#pragma comment (lib,"../../���ӿ�/Unicode/VideoServiceD.lib")
#endif
#endif

//////////////////////////////////////////////////////////////////////////////////
