//#include "UseShader.h"
//#include<iostream>
//#include<fstream>
//#include<sstream>
//#define GLFW_STATIC
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//using namespace std;
//
//UseShader::Shader(const char* vertexPath,const char* fragmentPath) {
//	std::ifstream vertexFile;
//	std::ifstream fragmentFile;
//	stringstream vertexStream;
//	stringstream fragmentStream;
//
//	vertexFile.open(vertexPath);
//	fragmentFile.open(fragmentPath);
//	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
//	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
//	try
//	{
//		if (!vertexFile.is_open() || !fragmentFile.is_open()) {//��û�з����ڴ���
//			throw std::exception("open file error");
//		}
//		vertexStream << vertexFile.rdbuf();
//		fragmentStream << fragmentFile.rdbuf();
//		vertexString = vertexStream.str();
//		fragmentString = fragmentStream.str();
//
//		vectexSource = vertexString.c_str();
//		fragmentSource = fragmentString.c_str();
//		//printf(vectexSource);
//		//printf(fragmentSource);
//		unsigned int vertex, fragment;
//		vertex = glCreateShader(GL_VERTEX_SHADER);//����
//		glShaderSource(vertex, 1, &vectexSource, NULL);//����
//		glCompileShader(vertex);//����
//
//		//�ж��Ƿ����ɹ�
//		checkComplieError(vertex, "VERTEX");
//
//		fragment = glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fragment, 1, &fragmentSource, NULL);
//		glCompileShader(fragment);
//		
//		checkComplieError(fragment, "FRAGMENT");
//
//		ID = glCreateProgram();
//		glAttachShader(ID, vertex);
//		glAttachShader(ID, fragment);
//		glLinkProgram(ID);
//
//		checkComplieError(ID, "PROGRAM");
//
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//	}
//	catch (const std::exception& ex)
//	{
//		printf(ex.what());
//	}
//}
//
//void UseShader::use() {
//	glUseProgram(ID);
//}
//
//void UseShader::checkComplieError(unsigned int ID, string type) {
//	char infoLog[512];
//	int success;
//	if (type != "PROGRAM") {
//		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
//		if (!success) {
//			glGetShaderInfoLog(ID, 512, NULL, infoLog);
//			cout << "Shader Complie Error:" << infoLog << endl;
//		}
//	}
//	else
//	{
//		glGetProgramiv(ID, GL_LINK_STATUS, &success);
//		if (!success) {
//			glGetProgramInfoLog(ID, 512, NULL, infoLog);
//			cout << "Program Linking ERROR:" << infoLog << endl;
//		}
//	}
//}
//
////Shader::~Shader()
////{
////}