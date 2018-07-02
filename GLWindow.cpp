#include "GLWindow.h"

GLWindow::GLWindow(QWindow *parent)
	: QWindow(parent)
{
	this->setSurfaceType(OpenGLSurface);
	this->resize(640, 360);
}

GLWindow::~GLWindow()
{

}

void GLWindow::exposeEvent(QExposeEvent * pEvent)
{
	Q_UNUSED(pEvent);
	if ( m_pContext == Q_NULLPTR )
	{
		QSurfaceFormat format;
		format.setVersion(4, 3);//需要opengl4.3版本
		format.setSamples(4);	//4倍采样

		m_pContext = new QOpenGLContext(this);
		m_pContext->setFormat(format);
		m_pContext->create();
		m_pContext->makeCurrent(this);
		this->initializeOpenGLFunctions();
		this->InitGL();
	}
	this->resize(this->width(), this->height());
	this->RenderGL();
	m_pContext->swapBuffers(this);
}


void GLWindow::InitGL()
{

}

void GLWindow::ResizeGL(int width, int height)
{
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void GLWindow::RenderGL()
{
	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);
}