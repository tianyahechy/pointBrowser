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
	void ReleaseGL();	//释放资源
	void onClose(void);
private:
	QOpenGLContext * m_pContext;

private:
	GLuint g_vertexShader;
	GLuint g_FragmentShader;
	GLuint g_Program;
	GLuint g_VertexArray;

public:
	//从文件获取shader
	QByteArray getShaderDataFromFile(const QString& fileName);
	//shader文件名 
	std::string _strVertexFileName;		//顶点着色器
	std::string _strFragFileName;		//片元着色器

	
};

#endif // GLWINDOW_H
