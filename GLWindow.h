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
	void InitGL();	//����Opengl�ĳ�ʼ��
	void RenderGL();//OpenGL��Ⱦ���
	void ResizeGL(int width, int height); //���ڴ�С�ı�ʱ
	void ReleaseGL();	//�ͷ���Դ
	void onClose(void);
private:
	QOpenGLContext * m_pContext;

private:
	GLuint g_vertexShader;
	GLuint g_FragmentShader;
	GLuint g_Program;
	GLuint g_VertexArray;

public:
	//���ļ���ȡshader
	QByteArray getShaderDataFromFile(const QString& fileName);
	//shader�ļ��� 
	std::string _strVertexFileName;		//������ɫ��
	std::string _strFragFileName;		//ƬԪ��ɫ��

	
};

#endif // GLWINDOW_H
