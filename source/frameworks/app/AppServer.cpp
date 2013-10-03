/*
 * AppServer.cpp
 *
 *  Created on: 29.01.2013.
 *      Author: idjukic
 */

#include "AppServer.h"
#include <GL/glfw.h>

#ifdef __cplusplus
extern "C" {
#include "iniParser/iniparser.h"
}
#endif

static AppServer *g_app_server = NULL;

static void cb_key(int key, int press)
{
	if (g_app_server == NULL) return;
	AppClient *client = g_app_server->getClient();
	if (client == NULL) return;

    client->onKeyEvent(key, press);
    g_app_server->setKeyStatus(key, press);

    if (key == GLFW_KEY_ESC)
    {
        glfwCloseWindow();
    }
}

static void cb_mouse_pos(int x, int y)
{
	if (g_app_server == NULL) return;
	AppClient *client = g_app_server->getClient();
	if (client == NULL) return;

    client->onMouseMoveEvent(x, y);
}

static void cb_mouse_button(int button, int press)
{
	if (g_app_server == NULL) return;
	AppClient *client = g_app_server->getClient();
	if (client == NULL) return;

    client->onMouseButtonEvent(button, press);
}

static void cb_mouse_wheel(int wheel)
{
	if (g_app_server == NULL) return;
	AppClient *client = g_app_server->getClient();
	if (client == NULL) return;

    client->onMouseWheelEvent(wheel);
}

static void cb_size(int width, int height)
{
	if (g_app_server == NULL) return;
	AppClient *client = g_app_server->getClient();
	if (client == NULL) return;

    client->onSize(width, height);
}

AppServer *AppServer::init(const char *title, const char *settings_path)
{
	if (g_app_server)
	{
		LOGE("Server already initialized!");
		return NULL;
	}

    if (!glfwInit())
    {
        LOGE("GLWF initialize failed!");
        return NULL;
    }

    g_app_server = new AppServer();
    g_app_server->mClient = NULL;
    g_app_server->mRunning = false;
    g_app_server->mKeyStatus = new bool [GLFW_KEY_LAST + 1];

    dictionary *ini = iniparser_load(settings_path);
    g_app_server->mSettings.width = iniparser_getint(ini, "video:width", 640);
    g_app_server->mSettings.height = iniparser_getint(ini, "video:height", 480);
    g_app_server->mSettings.fullscreen = iniparser_getint(ini, "video:fullscreen", 0);
    g_app_server->mSettings.desktop = iniparser_getint(ini, "video:desktop", 0);
    g_app_server->mSettings.audio = iniparser_getint(ini, "audio:enabled", 0);
    iniparser_freedict(ini);
#ifdef DEBUG
    g_app_server->mSettings.width = 400;
    g_app_server->mSettings.height = 400;
    g_app_server->mSettings.fullscreen = 0;
    g_app_server->mSettings.desktop = 0;
#endif
    if (g_app_server->mSettings.desktop)
    {
        GLFWvidmode dm;
        glfwGetDesktopMode(&dm);
        g_app_server->mSettings.width = dm.Width;
        g_app_server->mSettings.height = dm.Height;
        g_app_server->mSettings.fullscreen = 1;
    }

    //glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if (!glfwOpenWindow(
    		g_app_server->mSettings.width,
    		g_app_server->mSettings.height,
    		8, 8, 8, 8,
    		16,
    		0,
    		g_app_server->mSettings.fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW))
    {
        LOGE("GLFW open window failed!");
        glfwTerminate();
        delete g_app_server;
        return NULL;
    }
    glfwSwapInterval(0);
    glfwSetWindowTitle(title);
    glfwSetKeyCallback(cb_key);
    glfwSetMousePosCallback(cb_mouse_pos);
    glfwSetMouseButtonCallback(cb_mouse_button);
    glfwSetMouseWheelCallback(cb_mouse_wheel);
    glfwSetWindowSizeCallback(cb_size);
    if (g_app_server->mSettings.fullscreen)
    {
        //glfwEnable(GLFW_MOUSE_CURSOR);
    }

    g_app_server->mView = new GLView();
    g_app_server->mView->setup();
    g_app_server->mView->setSize(
    		g_app_server->mSettings.width,
    		g_app_server->mSettings.height);

    return g_app_server;
}

AppServer::~AppServer()
{
	glfwTerminate();
	delete [] mKeyStatus;
	g_app_server = NULL;
}

int AppServer::run(AppClient *client)
{
	mClient = client;

    float ftime = glfwGetTime();

    while (glfwGetWindowParam(GLFW_OPENED))
    {
        //
        //update
        //
        float dt = glfwGetTime() - ftime;
        mClient->onUpdate(dt);
        ftime = glfwGetTime();

        //
        //draw
        //
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        mClient->onDraw(mView);
        glfwSwapBuffers();
    }

    return 0;
}
