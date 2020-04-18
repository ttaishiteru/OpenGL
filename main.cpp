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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//ESC键退出
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, char* argv[]) {

	//初始化GLFW windows
	glfwInit();//初始化glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//提示：使用openGL版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//版本为3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用可编程流水线CORE_PROFILE
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//openGL前向相容性，使用MAC开发需要提示

	//创建window
	GLFWwindow* window = glfwCreateWindow(800, 600, "openGL Triangle", NULL, NULL);//使用指针：宽/高/标题名
	if (window == NULL) {//若创建失败，返回空指针
		std::cout << "Open GLFW Windows Failed!" << std::endl;
		glfwTerminate();//销毁所有数据
		return -1;
	}
	glfwMakeContextCurrent(window);//把这个window和当前上下文绑定

	//初始化GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Init GLEW Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//设置window可以绘制的范围大小
	/*glEnable(GL_CULL_FACE);//剔除面
	glCullFace(GL_BACK);
	逆时针作为三角形的正面
	*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//以线段模式绘制
	glEnable(GL_DEPTH_TEST);//开启深度缓冲

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//可以产生多个VAO
	//unsigned int VAO[10];
	//glGenVertexArrays(10, &VAO);//产生10个VAO
	glBindVertexArray(VAO);//绑定VAO

	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//float vertices[] = {
	//   .5f,-.5f,0.0f,1.0f,0.0f,0.0f,//右下 大红色
	//   -.5f,-.5f,0.0f,0.0f,1.0f,0.0f,//左下 大绿色
	//   0.0f,.5f,0.0f,0.0f,0.0f,1.0f//顶部 大蓝色
	//};
	////顶点/颜色

	//float vertices[] = {
	//	//-----坐标------    ------颜色-----    ----uv-----
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // 右上
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // 右下
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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

	//载入贴图
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//默认进入uniform
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//jpg用GL_RGB
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
		//png用GL_RGBA
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
		GL_STATIC_DRAW:坐标将几乎不会变化
		GL_DYNAMIC_DRAW:坐标将会经常变化
		GL_STREAM_DRAW:坐标将频繁变化
	*/
	UseShader *shaderIn = new UseShader("vertexSource.txt","fragmentSource.txt");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//3组数据，每组数据的类型，需不需要标准化，下一个顶点要间隔多少，第一组顶点数据的偏移量
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 *sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 *sizeof(float)));
    //顶点特征值：每3个数据为一个顶点
	//设置attribute为0号，对应vertex shader，最多15号
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(-0.001f, 0.0f, 0.0f));//移动坐标
	//trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));//旋转
	//trans = glm::scale(trans, glm::vec3(1.5f, 1.5f, 1.5f));//缩放
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	while (!glfwWindowShouldClose(window)) {//渲染循环
		//探测用户是否要关闭window
		processInput(window);

		//trans = glm::translate(trans, glm::vec3(0.001f, 0.0f, 0.0f));动态移动
		glClearColor(0, 0.5f, 0.5f, 1.0f);//RGB,透明值
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清屏避免出现上一帧画面

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
		glUseProgram(shader_program);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);*/
		
		//glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "transform"), 1,GL_FALSE,glm::value_ptr(trans));
		
		//发出10次Draw Call
		
		for (int i = 0;i < 10;i++) {
			glm::mat4 tmpMat = glm::mat4(1.0f);
			tmpMat = glm::translate(tmpMat, cubePositions[i]);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourTexture"), 0);
			glUniform1i(glGetUniformLocation(shaderIn->ID, "ourFace"), 1);

			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(tmpMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shaderIn->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//局部空间->投影空间的变化

			shaderIn->use();

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);//交换颜色缓存区块，buffer包含颜色的信息
		glfwPollEvents();
	}

	glfwTerminate();//退出时删除资源

	return 0;
}

