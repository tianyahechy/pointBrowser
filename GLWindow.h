#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QtGui/qopenglfunctions_4_3_core.h>
#include <Qt3DRender\QWindow>

class GLWindow : public QWindow, protected QOpenGLFunctions_4_3_Core
{
	Q_OBJECT

public:
	GLWindow(QWindow *parent = Q_NULLPTR);
	~GLWindow();
protected:
	void exposeEvent(QExposeEvent * pEvent);
	void InitGL();	//额外Opengl的初始化
	void RenderGL();//OpenGL渲染相关
	void ResizeGL(int width, int height); //窗口大小改变时

private:
	QOpenGLContext * m_pContext;
	
};

#endif // GLWINDOW_H
