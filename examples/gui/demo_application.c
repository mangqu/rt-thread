#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include "demo_view.h"
#include <rtgui/widgets/window.h>


struct rtgui_win *main_win;
static void application_entry(void *parameter)
{
/*	struct rtgui_app *app;
	struct rtgui_rect rect;
	struct rtgui_win* win;

	app = rtgui_app_create("gui_demo");
	if (app == RT_NULL)
	{
		rt_kprintf("rtgui app create error!\n");
	    return;
	}
	else
	{
		rt_kprintf("rtgui app create success!\n");
	}*/
	
	/* set as window manager */
//	rtgui_app_set_as_wm(app);

	/* create a full screen window */
//	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect);

//	main_win = rtgui_win_create(RT_NULL, "demo_win", &rect,
//	                            RTGUI_WIN_STYLE_MAINWIN | RTGUI_WIN_STYLE_CLOSEBOX);
/*	if (main_win == RT_NULL)
	{
		rt_kprintf("Create main window failed!\n");
	    rtgui_app_destroy(app);
	    return;
	}
	else
	{
		rt_kprintf("Create main window success!\n");
	}

	rtgui_win_show(main_win, RT_FALSE);
	rt_kprintf("1\n");*/
	/* create main window of Application Manager */
/*	win = rtgui_mainwin_create(RT_NULL, "AppMgr", RTGUI_WIN_STYLE_MINIBOX);
	RTGUI_WIDGET_BACKGROUND(win) = RTGUI_RGB(0, 0, 0);
	rt_kprintf("2\n");
	rtgui_win_show(win, RT_FALSE);
	rt_kprintf("3\n");*/
	/* set as main window */
/*	rtgui_app_set_main_win(rtgui_app_self(), win);
	rt_kprintf("4\n");*/
	/* 执行工作台事件循环 */
/*	rtgui_app_run(app);
	rt_kprintf("5\n");
	rtgui_app_destroy(app);
	rt_kprintf("6\n");*/
	
	struct rtgui_app* app;
	struct rtgui_win *win;
  	struct rtgui_box *box;

	struct rtgui_rect rect = {10, 50, 200, 250};

	app = rtgui_app_create("gui_demo");
	if (app == RT_NULL)
	{
		rt_kprintf("rtgui app create error!\n");
	    return;
	}
	else
	{
		rt_kprintf("rtgui app create success!\n");
	}
	/* create a full screen window */
//	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect);
	win = rtgui_win_create(RT_NULL, "gui_demo", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if (win == RT_NULL)
	{
		rt_kprintf("Create main window failed!\n");
	    rtgui_app_destroy(app);
	    return;
	}
	
	rtgui_win_show(win, RT_FALSE);
	rtgui_app_run(app);
	rtgui_win_destroy(win);
	rtgui_app_destroy(app);
	
	rt_kprintf("gui_demo quit.\n");
}

void application_init(void)
{
	static rt_bool_t inited = RT_FALSE;

	if (inited == RT_FALSE) /* 避免重复初始化而做的保护 */
	{
		rt_thread_t tid;

		tid = rt_thread_create("wb",
		                       application_entry, RT_NULL,
		                       2048 * 2, 25, 10);

		if (tid != RT_NULL)
		{
			rt_kprintf("wb thread init success!\n");
		    rt_thread_startup(tid);
		}

		inited = RT_TRUE;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void application()
{
    application_init();
}
/* finsh的命令输出，可以直接执行application()函数以执行上面的函数 */
FINSH_FUNCTION_EXPORT(application, application demo)
#endif
