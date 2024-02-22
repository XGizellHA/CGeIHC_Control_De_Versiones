//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
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
#include"Mesh.h" //Declaracion de la clase
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;

//Listas mesh, meshcolor y shader, nos permite crear mas de uno
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

/*Shaders nuevos*/
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* fShaderRojo = "shaders/shaderRojo.frag";

static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* fShaderAzul = "shaders/shaderAzul.frag";

static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* fShaderCafe = "shaders/shaderCafe.frag";

static const char* vShaderVerdeClaro = "shaders/shaderVerdeClaro.vert";
static const char* fShaderVerdeClaro = "shaders/shaderVerdeClaro.frag";

static const char* vShaderVerdeOscuro = "shaders/shaderVerdeOscuro.vert";
static const char* fShaderVerdeOscuro = "shaders/shaderVerdeOscuro.frag";
//shaders nuevos se crearían acá

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
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};

	//Mesh con los datos de vertices e indices y los guarda en la lista
	Mesh *obj1 = new Mesh();
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
		6, 7, 3
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
Mesh *cubo = new Mesh();
//											vertices, indices
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			/*-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/
		//Se pegaran el codigo de las letras de la practica 01 y se les agregara un color 
		//Letra X
		-0.875f, 0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, 0.5f, 0.f,		0.195f, 0.156f, 0.86f,
		-0.875f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7916f, 0.5f, 0.f,		0.195f, 0.156f, 0.86f,
		-0.875f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.875f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7916f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.75f, 0.125f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7082f, 0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, 0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7082f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.625f, 0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7082f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7082f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7082f, 0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.75f, 0.125f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.75f, 0.125f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.75f, -0.125f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.75f, -0.125f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.75f, -0.125f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7082f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.8125f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.875f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.6875f, 0.0f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7082f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.875f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.875f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7916f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.875f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7916f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7082f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.7082f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,

		-0.7082f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, -0.25f, 0.0f,		0.195f, 0.156f, 0.86f,
		-0.625f, -0.5f, 0.0f,		0.195f, 0.156f, 0.86f,

		//Letra G
		-0.375f, 0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.125f, 0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2916f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, 0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2916f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2082f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, 0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2082f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.125f, 0.125f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, 0.125f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2082f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2082f, 0.125f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.375f, 0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2916f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.375F, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.2916f, 0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.375F, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.2916f, -0.375f, 0.0f,	0.543f, 0.156f, 0.86f,

		-0.2916f, -0.375f, 0.0f,	0.543f, 0.156f, 0.86f,
		-0.375F, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.125f, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.2916f, -0.375f, 0.0f,	0.543f, 0.156f, 0.86f,
		-0.125f, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.16f, -0.375f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, -0.5f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.16f, -0.375f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.125f, 0.0f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.16f, -0.375f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.125f, 0.0f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.16f, -0.25f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, 0.0f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.16f, -0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.25f, -0.25f, 0.0f,		0.543f, 0.156f, 0.86f,

		-0.125f, 0.0f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.25f, -0.25f, 0.0f,		0.543f, 0.156f, 0.86f,
		-0.25f, 0.0f, 0.0f,			0.543f, 0.156f, 0.86f,

		//Letra H
		0.125f, 0.5f, 0.0f,			0.86f,0.156f, 0.652f,
		0.2082f, 0.5f, 0.0f,		0.86f,0.156f, 0.652f,
		0.125f, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,

		0.2082f, 0.5f, 0.0f,		0.86f,0.156f, 0.652f,
		0.125f, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,
		0.2082f, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,

		0.2082f, 0.125f, 0.0f,		0.86f,0.156f, 0.652f,
		0.2914f, 0.125f, 0.0f,		0.86f,0.156f, 0.652f,
		0.2082f, -0.125f, 0.0f,		0.86f,0.156f, 0.652f,

		0.2914f, 0.125f, 0.0f,		0.86f,0.156f, 0.652f,
		0.2082f, -0.125f, 0.0f,		0.86f,0.156f, 0.652f,
		0.2914f, -0.125f, 0.0f,		0.86f,0.156f, 0.652f,

		0.2914f, 0.5f, 0.0f,		0.86f,0.156f, 0.652f,
		0.375f, 0.5f, 0.0f,			0.86f,0.156f, 0.652f,
		0.2914F, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,

		0.375f, 0.5f, 0.0f,			0.86f,0.156f, 0.652f,
		0.2914f, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,
		0.375f, -0.5f, 0.0f,		0.86f,0.156f, 0.652f,

		//Letra A
		0.7082f, 0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.625f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7082f, 0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, 0.5f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7082f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, 0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7914f, 0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.875f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.625f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.625f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7082f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.625f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7082f, 0.0f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, 0.0f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, -0.25f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7914f, 0.0f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7082f, -0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, -0.25f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.7914f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.875f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,

		0.875f, 0.25f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.7914f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
		0.875f, -0.5f, 0.0f,		0.86f, 0.156f, 0.29f,
			
	};
	MeshColor *letras = new MeshColor();
	//										3*6
	letras->CreateMeshColor(vertices_letras, 828);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo); // Mesh 1

	//Codigo ejercicio 01
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul); //mesh 2

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f, 0.5f, 0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f, 0.5f, 0.0f,
		0.0f,	1.0f,		0.5f,			0.0f, 0.5f, 0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde); //mesh3
	
	//Cuadrados ejercicio 01
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
	meshColorList.push_back(cuadradoverde); //Mesh 4
	
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo); //Mesh 5

	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe); //Mesh 6

}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderRojo, fShaderRojo); //Shader Rojo
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderAzul, fShaderAzul); //Shader Azul
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderCafe, fShaderCafe); //Shader Cafe
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vShaderVerdeClaro, fShaderVerdeClaro); //Shader Verde Claro
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(vShaderVerdeOscuro, fShaderVerdeOscuro); //Shader Verde Oscuro
	shaderList.push_back(*shader7);

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
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad, sire para persivir o leer informacionen el eje z
		
													
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.0f));
		//

		//Dibuja las letras
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//meshColorList[0]->RenderMeshColor(); //Triangulo azul default

		//Triangulos ejercicio 01
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[1]->RenderMeshColor(); //Triangulo rojo ejercicio

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[2]->RenderMeshColor(); //Triangulo azul ejercicio

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[3]->RenderMeshColor(); //Triangulo verde

		//Cuadrados ejercicio 01
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[4]->RenderMeshColor(); //Cuadrado verde

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[5]->RenderMeshColor(); //Cuadrado rojo

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshColorList[6]->RenderMeshColor(); //Cuadrado cafe

		/*Ejecicio 02
		//Cuadrado rojo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[5]->RenderMeshColor(); 

		//Triangulo azul
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -20.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.5f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[2]->RenderMeshColor(); 

		//Cuadrados cafes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.90f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[6]->RenderMeshColor(); //Cuadrado cafe

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.90f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[6]->RenderMeshColor(); //Cuadrado cafe

		//Triangulos verdes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[3]->RenderMeshColor(); //Triangulo verde

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[3]->RenderMeshColor(); //Triangulo verde

		//Cuadrados verdes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, -5.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[4]->RenderMeshColor(); //Cuadrado verde

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.25f, -5.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[4]->RenderMeshColor(); //Cuadrado verde

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.25f, -5.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, -20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[4]->RenderMeshColor(); //Cuadrado verde
		*/


		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[3].useShader(); 
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.1;

		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas

		/*		Ejercicio 02		*/
		//Piramide azul
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();//Piramide azul

		//Cubo rojo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); 

		//Cubos verdes
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.7f, -1.6f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); 

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, -0.2f, -1.6f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, -0.2f, -1.6f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();


		//Cubos cafes
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.85f, -0.85f, -1.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.85f, -0.85f, -1.65f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		//Piramides verdes oscuros
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.85f, -0.42f, -1.6f));
		model = glm::scale(model, glm::vec3(0.5f, 0.8f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.85f, -0.42f, -1.6f));
		model = glm::scale(model, glm::vec3(0.5f, 0.8f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
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