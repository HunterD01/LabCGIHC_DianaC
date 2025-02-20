#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
///modificado
#include <cstdlib>  // biblioteca de propósito general de C
#include <chrono>
#include <thread>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,1.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		//inicio D
		-0.92f,0.82f,0.0f,
		-0.92f,0.63f,0.0f,
		-0.73f,0.63f,0.0f,

		-0.92f,0.82f,0.0f,
		-0.73f,0.63f,0.0f,
		-0.64f,0.82f,0.0f,

		-0.64f,0.63f,0.0f,
		-0.73f,0.63f,0.0f,
		-0.64f,0.82f,0.0f,

		-0.64f,0.63f,0.0f,
		-0.55f,0.54f,0.0f,
		-0.64f,0.82f,0.0f,

		-0.55f,0.54f,0.0f,
		-0.40f,0.54f,0.0f,
		-0.64f,0.82f,0.0f,

		-0.55f,0.54f,0.0f,
		-0.40f,0.54f,0.0f,
		-0.55f,-0.20f,0.0f,

		-0.40f,0.54f,0.0f,
		-0.55f,-0.20f,0.0f,
		-0.40f,-0.20f,0.0f,

		-0.64f,-0.30f,0.0f,
		-0.55f,-0.20f,0.0f,
		-0.40f,-0.20f,0.0f,

		-0.64f,-0.30f,0.0f,
		-0.64f,-0.40f,0.0f,
		-0.40f,-0.20f,0.0f,

		-0.64f,-0.30f,0.0f,
		-0.64f,-0.40f,0.0f,
		-0.74f,-0.40f,0.0f,

		-0.64f,-0.30f,0.0f,
		-0.74f,-0.30f,0.0f,
		-0.74f,-0.40f,0.0f,

		-0.73f,0.63f,0.0f,
		-0.92f,-0.40f,0.0f,
		-0.74f,-0.40f,0.0f,

		-0.73f,0.63f,0.0f,
		-0.92f,0.63f,0.0f,
		-0.92f,-0.40f,0.0f,//13

		//Inicio S
		-0.30f,0.53f,0.0f,
		-0.15f,0.53f,0.0f,
		-0.30f,0.20f,0.0f,

		-0.30f,0.20f,0.0f,
		-0.15f,0.53f,0.0f,
		-0.15f,0.20f,0.0f,

		//parte abajo de la S
		-0.30f,0.20f,0.0f,
		-0.15f,0.20f,0.0f,//
		0.22f,-0.10f,0.0f,

		0.22f,-0.10f,0.0f,
		-0.15f,0.20f,0.0f,//
		0.22f,0.09f,0.0f,

		-0.30f,0.20f,0.0f,
		0.22f,-0.10f,0.0f,
		-0.30f,0.10f,0.0f,

		0.10f,-0.20f,0.0f,
		0.22f,0.00f,0.0f,
		0.10f,-0.03f,0.0f,

		0.10f,-0.20f,0.0f,
		0.22f,0.00f,0.0f,
		0.22f,-0.20f,0.0f,

		0.10f,-0.20f,0.0f,
		0.07f,-0.40f,0.0f,//21
		0.22f,-0.20f,0.0f,

		0.10f,-0.20f,0.0f,
		0.07f,-0.40f,0.0f,//22
		0.07f,-0.30f,0.0f,

		-0.10f,-0.40f,0.0f,
		0.07f,-0.40f,0.0f,//23
		0.07f,-0.30f,0.0f,

		-0.10f,-0.40f,0.0f,
		-0.10f,-0.30f,0.0f,//24
		0.07f,-0.30f,0.0f,

		-0.10f,-0.40f,0.0f,
		-0.10f,-0.30f,0.0f,//25
		-0.20f,-0.20f,0.0f,

		-0.10f, -0.40f, 0.0f,
		-0.30f, -0.20f, 0.0f,//26
		-0.20f, -0.20f, 0.0f,

		-0.20f, -0.15f, 0.0f,
		-0.30f, -0.20f, 0.0f,//27
		-0.20f, -0.20f, 0.0f,

		-0.30f, -0.15f, 0.0f,
		-0.30f, -0.20f, 0.0f,//28
		-0.20f, -0.15f, 0.0f,

		//parte arriba de la S
		-0.30f, 0.53f, 0.0f,
		-0.10f, 0.82f, 0.0f,//29
		-0.15f, 0.53f, 0.0f,

		-0.15f, 0.53f, 0.0f,
		-0.10f, 0.82f, 0.0f,//30
		-0.10f, 0.65f, 0.0f,

		 0.09f, 0.82f, 0.0f,
		-0.10f, 0.82f, 0.0f,//31
		-0.10f, 0.65f, 0.0f,

		 0.09f, 0.65f, 0.0f,
		0.09f, 0.82f, 0.0f,//32
		-0.10f, 0.65f, 0.0f,

		0.09f, 0.65f, 0.0f,
		0.09f, 0.82f, 0.0f,//33
		0.22f, 0.65f, 0.0f,

		0.09f, 0.65f, 0.0f,
		0.14f, 0.60f, 0.0f,//34
		0.22f, 0.65f, 0.0f,

		0.14f, 0.50f, 0.0f,
		0.14f, 0.60f, 0.0f,//35
		0.22f, 0.65f, 0.0f,

		0.14f, 0.50f, 0.0f,
		0.22f, 0.50f, 0.0f,//36
		0.22f, 0.65f, 0.0f,

		//Inicio C
		0.45f, -0.40f, 0.0f,
		0.32f, 0.82f, 0.0f,//37
		0.32f, -0.40f, 0.0f,

		0.45f, 0.82f, 0.0f,
		0.32f, 0.82f, 0.0f,//38
		0.45f, -0.40f, 0.0f,

		0.45f, 0.82f, 0.0f,
		0.45f, 0.68f, 0.0f,//39
		0.80f, 0.82f, 0.0f,

		0.80f, 0.82f, 0.0f,
		0.45f, 0.68f, 0.0f,//40
		0.80f, 0.68f, 0.0f,

		0.92f, 0.82f, 0.0f,
		0.92f, 0.50f, 0.0f,//41
		0.80f, 0.50f, 0.0f,

		0.92f, 0.82f, 0.0f,
		0.80f, 0.82f, 0.0f,//42
		0.80f, 0.50f, 0.0f,

		0.92f, -0.40f, 0.0f,
		0.80f, -0.40f, 0.0f,//43
		0.80f, -0.08f, 0.0f,

		0.45f, -0.40f, 0.0f,
		0.45f, -0.26f, 0.0f,//44
		0.80f, -0.40f, 0.0f,

		0.80f, -0.40f, 0.0f,
		0.45f, -0.26f, 0.0f,//45
		0.80f, -0.26f, 0.0f,

		0.92f, -0.40f, 0.0f,
		0.92f, -0.08f, 0.0f,//46
		0.80f, -0.08f, 0.0f,

		0.92f, -0.40f, 0.0f,
		0.80f, -0.40f, 0.0f,//47
		0.80f, -0.08f, 0.0f,
	};	
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 01", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(2000));//para que la pantalla aparezca cada 2s

		std::srand(std::time(nullptr));  // generamos una semilla para el random

		double num1 = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
		double num2 = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;
		double num3 = (double)rand() / (RAND_MAX + 1) * (1 - 0) + 0;

		glClearColor(num1, num2, num3, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,141);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}