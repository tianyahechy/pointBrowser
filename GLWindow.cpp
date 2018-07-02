#include "GLWindow.h"
#include <qfile.h>
#include <qsurfaceformat.h>
#include <qopenglcontext.h>

GLWindow::GLWindow(QWindow *parent)
	: QWindow(parent)
{
	this->setSurfaceType(OpenGLSurface);
	this->resize(640, 360);
	g_vertexShader = 0;
	g_FragmentShader = 0;
	g_Program = 0;
	g_VertexArray = 0;
	_strVertexFileName = "Shader.vert";
	_strFragFileName = "Shader.frag";
	m_pContext = Q_NULLPTR;
}

GLWindow::~GLWindow()
{

}

QByteArray GLWindow::getShaderDataFromFile(const QString& fileName)
{
	QByteArray result;
	QFile shaderFile(fileName);
	if (shaderFile.open(QIODevice::ReadOnly))
	{
		result = shaderFile.readAll();
		shaderFile.close();
	}
	return result;
}

void GLWindow::exposeEvent(QExposeEvent * pEvent)
{
	Q_UNUSED(pEvent);
	if (m_pContext == Q_NULLPTR)
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
	this->ResizeGL(this->width(), this->height());
	this->RenderGL();
	m_pContext->swapBuffers(this);
}

void GLWindow::InitGL()
{
	//初始化顶点着色器
	QByteArray vsData = this->getShaderDataFromFile(_strVertexFileName.c_str());
	const char * vsPointer = vsData.constData();
	g_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(g_vertexShader,	//着色器标识
		1,				//着色器文本数目
		&vsPointer,		//着色器字符串指针
		Q_NULLPTR		//字符串长度	
		);
	glCompileShader(g_vertexShader);

	//初始化片元着色器
	QByteArray fsData = this->getShaderDataFromFile(_strFragFileName.c_str());
	const char * fsPointer = fsData.constData();
	g_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(g_FragmentShader,	//着色器标识
		1,				//着色器文本数目
		&fsPointer,		//着色器字符串指针
		Q_NULLPTR		//字符串长度	
		);
	glCompileShader(g_FragmentShader);

	//初始化着色器程序
	g_Program = glCreateProgram();
	glAttachShader(g_Program, g_vertexShader);
	glAttachShader(g_Program, g_FragmentShader);
	glLinkProgram(g_Program);

	//删除着色器
	glDeleteShader(g_vertexShader);
	glDeleteShader(g_FragmentShader);

	//初始化顶点数组对象
	glGenVertexArrays(1, &g_VertexArray);
	glBindVertexArray(g_VertexArray);
	glPointSize(10.0f);
}

void GLWindow::ResizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLWindow::RenderGL()
{
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glUseProgram(g_Program);
	glDrawArrays(GL_POINTS, 0, 1);
}

void GLWindow::ReleaseGL()
{
	glDeleteVertexArrays(1, &g_VertexArray);
	glDeleteProgram(g_Program);
}