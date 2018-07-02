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
		format.setVersion(4, 3);//��Ҫopengl4.3�汾
		format.setSamples(4);	//4������

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
	//��ʼ��������ɫ��
	QByteArray vsData = this->getShaderDataFromFile(_strVertexFileName.c_str());
	const char * vsPointer = vsData.constData();
	g_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(g_vertexShader,	//��ɫ����ʶ
		1,				//��ɫ���ı���Ŀ
		&vsPointer,		//��ɫ���ַ���ָ��
		Q_NULLPTR		//�ַ�������	
		);
	glCompileShader(g_vertexShader);

	//��ʼ��ƬԪ��ɫ��
	QByteArray fsData = this->getShaderDataFromFile(_strFragFileName.c_str());
	const char * fsPointer = fsData.constData();
	g_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(g_FragmentShader,	//��ɫ����ʶ
		1,				//��ɫ���ı���Ŀ
		&fsPointer,		//��ɫ���ַ���ָ��
		Q_NULLPTR		//�ַ�������	
		);
	glCompileShader(g_FragmentShader);

	//��ʼ����ɫ������
	g_Program = glCreateProgram();
	glAttachShader(g_Program, g_vertexShader);
	glAttachShader(g_Program, g_FragmentShader);
	glLinkProgram(g_Program);

	//ɾ����ɫ��
	glDeleteShader(g_vertexShader);
	glDeleteShader(g_FragmentShader);

	//��ʼ�������������
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