//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
///normal
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

///Azul
static const char* vShaderA = "shaders/shaderAzul.vert";
static const char* fShaderA = "shaders/shaderAzul.frag";
///Rojo
static const char* vShaderR = "shaders/shaderRojo.vert";
static const char* fShaderR = "shaders/shaderRojo.frag";
///Verde
static const char* vShaderV = "shaders/shaderVerde.vert";
static const char* fShaderV = "shaders/shaderVerde.frag";
///VerdeFuerte
static const char* vShaderVF = "shaders/shaderVerdeFuerte.vert";
static const char* fShaderVF = "shaders/shaderVerdeFuerte.frag";
///Cafe
static const char* vShaderC = "shaders/shaderCafe.vert";
static const char* fShaderC = "shaders/shaderCafe.frag";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-1.0f, -1.0f,0.0f,	//0
		1.0f,-1.0f,0.0f,	//1
		0.0f,1.0f, -0.5f,	//2
		0.0f,-1.0f,-1.0f,	//3

		/*		
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3 */
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3,
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);//indices,triangulos
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//GLfloat vertices_letras[] = {
		
		//X			Y			Z			R		G		B
		/*-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/
		
		/*
		//inicio D
		-0.92f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.92f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.73f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.92f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.73f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.73f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.55f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.55f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.40f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,0.82f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.55f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.40f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.55f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.40f,0.54f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.55f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.40f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,-0.30f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.55f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.40f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,-0.30f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.40f,-0.20f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,-0.30f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.64f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.74f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.64f,-0.30f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.74f,-0.30f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.74f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.73f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.92f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.74f,-0.40f,0.0f,	1.0f,	0.71f,	0.75f,

		-0.73f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.92f,0.63f,0.0f,	1.0f,	0.71f,	0.75f,
		-0.92f,-0.40f,0.0f, 1.0f,	0.71f,	0.75f,//13	

		//Inicio S
		-0.30f,0.53f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.15f,0.53f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.30f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,

		-0.30f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.15f,0.53f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.15f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,

		//parte abajo de la S
		-0.30f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.15f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,-0.10f,0.0f, 0.49f,	1.0f,	0.83f,

		0.22f,-0.10f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.15f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,0.09f,0.0f, 0.49f,	1.0f,	0.83f,

		-0.30f,0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,-0.10f,0.0f, 0.49f,	1.0f,	0.83f,
		-0.30f,0.10f,0.0f, 0.49f,	1.0f,	0.83f,

		0.10f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,0.00f,0.0f, 0.49f,	1.0f,	0.83f,
		0.10f,-0.03f,0.0f, 0.49f,	1.0f,	0.83f,

		0.10f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,0.00f,0.0f, 0.49f,	1.0f,	0.83f,
		0.22f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,

		0.10f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.07f,-0.40f,0.0f, 0.49f,	1.0f,	0.83f,//21
		0.22f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,

		0.10f,-0.20f,0.0f, 0.49f,	1.0f,	0.83f,
		0.07f,-0.40f,0.0f, 0.49f,	1.0f,	0.83f,//22
		0.07f,-0.30f,0.0f, 0.49f,	1.0f,	0.83f,

		-0.10f,-0.40f,0.0f, 0.49f,	1.0f,	0.83f,
		0.07f,-0.40f,0.0f, 0.49f, 1.0f, 0.83f,//23
		0.07f,-0.30f,0.0f, 0.49f, 1.0f, 0.83f,

		-0.10f,-0.40f,0.0f, 0.49f, 1.0f, 0.83f,
		-0.10f,-0.30f,0.0f, 0.49f, 1.0f, 0.83f,//24
		0.07f,-0.30f,0.0f, 0.49f, 1.0f, 0.83f,

		-0.10f,-0.40f,0.0f, 0.49f, 1.0f, 0.83f,
		-0.10f,-0.30f,0.0f, 0.49f, 1.0f, 0.83f,//25
		-0.20f,-0.20f,0.0f, 0.49f, 1.0f, 0.83f,

		-0.10f, -0.40f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.30f, -0.20f, 0.0f, 0.49f, 1.0f, 0.83f,//26
		-0.20f, -0.20f, 0.0f, 0.49f, 1.0f, 0.83f,

		-0.20f, -0.15f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.30f, -0.20f, 0.0f, 0.49f, 1.0f, 0.83f,//27
		-0.20f, -0.20f, 0.0f, 0.49f, 1.0f, 0.83f,

		-0.30f, -0.15f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.30f, -0.20f, 0.0f, 0.49f, 1.0f, 0.83f,//28
		-0.20f, -0.15f, 0.0f, 0.49f, 1.0f, 0.83f,

		//parte arriba de la S
		-0.30f, 0.53f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.10f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,//29
		-0.15f, 0.53f, 0.0f, 0.49f, 1.0f, 0.83f,

		-0.15f, 0.53f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.10f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,//30
		-0.10f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		 0.09f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,
		-0.10f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,//31
		-0.10f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		 0.09f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,
		0.09f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,//32
		-0.10f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		0.09f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,
		0.09f, 0.82f, 0.0f, 0.49f, 1.0f, 0.83f,//33
		0.22f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		0.09f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,
		0.14f, 0.60f, 0.0f, 0.49f, 1.0f, 0.83f,//34
		0.22f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		0.14f, 0.50f, 0.0f, 0.49f, 1.0f, 0.83f,
		0.14f, 0.60f, 0.0f, 0.49f, 1.0f, 0.83f,//35
		0.22f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		0.14f, 0.50f, 0.0f, 0.49f, 1.0f, 0.83f,
		0.22f, 0.50f, 0.0f, 0.49f, 1.0f, 0.83f,//36
		0.22f, 0.65f, 0.0f, 0.49f, 1.0f, 0.83f,

		//Inicio C
		0.45f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.32f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,//37
		0.32f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.45f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.32f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,//38
		0.45f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.45f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.45f, 0.68f, 0.0f, 0.98f, 0.62f, 0.88f,//39
		0.80f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.80f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.45f, 0.68f, 0.0f, 0.98f, 0.62f, 0.88f,//40
		0.80f, 0.68f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.92f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.92f, 0.50f, 0.0f, 0.98f, 0.62f, 0.88f,//41
		0.80f, 0.50f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.92f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.80f, 0.82f, 0.0f, 0.98f, 0.62f, 0.88f,//42
		0.80f, 0.50f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.92f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.80f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,//43
		0.80f, -0.08f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.45f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.45f, -0.26f, 0.0f, 0.98f, 0.62f, 0.88f,//44
		0.80f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.80f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.45f, -0.26f, 0.0f, 0.98f, 0.62f, 0.88f,//45
		0.80f, -0.26f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.92f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.92f, -0.08f, 0.0f, 0.98f, 0.62f, 0.88f,//46
		0.80f, -0.08f, 0.0f, 0.98f, 0.62f, 0.88f,

		0.92f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,
		0.80f, -0.40f, 0.0f, 0.98f, 0.62f, 0.88f,//47
		0.80f, -0.08f, 0.0f, 0.98f, 0.62f, 0.88f,
	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 846);
	meshColorList.push_back(letras);
	*/

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};
	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			 0.47, 0.255, 0.067,
		0.5f,	-0.5f,		0.5f,			 0.478, 0.255, 0.067,
		0.5f,	0.5f,		0.5f,			 0.478, 0.255, 0.067,
		-0.5f,	-0.5f,		0.5f,			 0.478, 0.255, 0.067,
		0.5f,	0.5f,		0.5f,			 0.478, 0.255, 0.067,
		-0.5f,	0.5f,		0.5f,			 0.478, 0.255, 0.067,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);

}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shaderRojo = new Shader(); //ROJO shader para usar índices: objetos: cubo y  pirámide
	shaderRojo->CreateFromFiles(vShaderR, fShaderR);
	shaderList.push_back(*shaderRojo);

	Shader* shaderAzul = new Shader(); //AZUL shader para usar índices: objetos: cubo y  pirámide
	shaderAzul->CreateFromFiles(vShaderA, fShaderA);
	shaderList.push_back(*shaderAzul);

	Shader* shaderVerde = new Shader(); //VERDE shader para usar índices: objetos: cubo y  pirámide
	shaderVerde->CreateFromFiles(vShaderV, fShaderV);
	shaderList.push_back(*shaderVerde);

	Shader* shaderVerdeFuerte = new Shader(); //VERDE FUERTE shader para usar índices: objetos: cubo y  pirámide
	shaderVerdeFuerte->CreateFromFiles(vShaderVF, fShaderVF);
	shaderList.push_back(*shaderVerdeFuerte);

	Shader* shaderCafe = new Shader(); //CAFE shader para usar índices: objetos: cubo y  pirámide
	shaderCafe->CreateFromFiles(vShaderC, fShaderC);
	shaderList.push_back(*shaderCafe);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);//left,right,bottom,near,far el valor derecho mayor a izquierdo, y top mayor a bottom
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		
		
		/* USAR PARA EL EJERCICIO 1 PRACTICA 02
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.85f, 1.3f, 1.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();//letras
		*/

		//ROJO
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -4.0f));
		model = glm::scale(model, glm::vec3(0.85f, 1.3f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO ROJO

		//AZUL
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.65f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//TRIANGULO AZUL

		//CUADRADO VERDE
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, 0.025f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO VERDE IZQUIERDA

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, 0.025f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO VERDE DERECHA

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.699f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO VERDE ABAJO

		//CUADRADO CAFE
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.75f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO CAFE IZQUIERDA

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.75f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();//CUADRADO CAFE DERECHA

		//CUADRADO VERDE FUERTE
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.25f, -4.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//CUADRADO VERDE FUERTE IZQUIERDA

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.25f, -4.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//CUADRADO VERDE FUERTE DERECHA

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
/////////////////TRASLACION
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/