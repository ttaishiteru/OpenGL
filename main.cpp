#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"UseShader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//ESC���˳�
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[]) {

	//��ʼ��GLFW windows
	glfwInit();//��ʼ��glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//��ʾ��ʹ��openGL�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�汾Ϊ3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//ʹ�ÿɱ����ˮ��CORE_PROFILE
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//openGLǰ�������ԣ�ʹ��MAC������Ҫ��ʾ

	//����window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openGL Triangle", NULL, NULL);//ʹ��ָ�룺��/��/������
	if (window == NULL) {//������ʧ�ܣ����ؿ�ָ��
		std::cout << "Open GLFW Windows Failed!" << std::endl;
		glfwTerminate();//������������
		return -1;
	}
	glfwMakeContextCurrent(window);//�����window�͵�ǰ�����İ�

	//��ʼ��GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Init GLEW Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//����window���Ի��Ƶķ�Χ��С
	/*glEnable(GL_CULL_FACE);//�޳���
	glCullFace(GL_BACK);
	��ʱ����Ϊ�����ε�����
	*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//���߶�ģʽ����
	glEnable(GL_DEPTH_TEST);//������Ȼ���

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//���Բ������VAO
	//unsigned int VAO[10];
	//glGenVertexArrays(10, &VAO);//����10��VAO
	glBindVertexArray(VAO);//��VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//����VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//float vertices[] = {
	//   .5f,-.5f,0.0f,1.0f,0.0f,0.0f,//���� ���ɫ
	//   -.5f,-.5f,0.0f,0.0f,1.0f,0.0f,//���� ����ɫ
	//   0.0f,.5f,0.0f,0.0f,0.0f,1.0f//���� ����ɫ
	//};
	////����/��ɫ

	//float vertices[] = {
	//	//-----����------    ------��ɫ-----    ----uv-----
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // ����
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // ����
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	//};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
	0,1,2,
	2,3,0
	};

	glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//������ͼ
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//Ĭ�Ͻ���uniform
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//jpg��GL_RGB
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//png��GL_RGBA
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed" << endl;
	}
	stbi_image_free(data2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	/*
		GL_STATIC_DRAW:���꽫��������仯
		GL_DYNAMIC_DRAW:���꽫�ᾭ���仯
		GL_STREAM_DRAW:���꽫Ƶ���仯
	*/
	UseShader *shaderIn = new UseShader("vertexSource.txt","fragmentSource.txt");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//3�����ݣ�ÿ�����ݵ����ͣ��費��Ҫ��׼������һ������Ҫ������٣���һ�鶥�����ݵ�ƫ����
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 *sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 *sizeof(float)));
    //��������ֵ��ÿ3������Ϊһ������
	//����attributeΪ0�ţ���Ӧvertex shader�����15��
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(-0.001f, 0.0f, 0.0f));//�ƶ�����
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));//��ת
	//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 1.5f));//����
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	while (!glfwWindowShouldClose(window)) {//��Ⱦѭ��
		//̽���û��Ƿ�Ҫ�ر�window
		processInput(window);

		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));��̬�ƶ�
		glClearColor(0, 0.5f, 0.5f, 1.0f);//RGB,͸��ֵ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������������һ֡����

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
		glUseProgram(shader_program);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);*/
		
		//glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "transform"), 1,GL_FALSE,glm::value_ptr(trans));
		
		//����10��Draw Call
		
		for (int i = 0;i < 10;i++) {
			glm::mat4 tmpMat = glm::mat4(1.0f);
			tmpMat = glm::translate(tmpMat, cubePositions[i]);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourFace"), 1);

			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(tmpMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//�ֲ��ռ�->ͶӰ�ռ�ı仯

			shaderIn->use();

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);//������ɫ�������飬buffer������ɫ����Ϣ
		glfwPollEvents();
	}

	glfwTerminate();//�˳�ʱɾ����Դ

	return 0;
}

