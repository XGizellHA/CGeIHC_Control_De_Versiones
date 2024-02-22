#include <stdio.h>
#include <stdlib.h> //Se añaio para poder usar rand()
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;

float rojo, verde, azul;
float colorT;


//float colorT = 0.0;

GLuint VAO, VBO, shader;

//Vertex Shader GLSL
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader, procesa la inf de color, iluminacion y sombreado, color a partir de texturas
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.0f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	/*Importa el acomodo*/
	GLfloat vertices[] = {
		// X,  Y,  Z
		//-1.0f, -1.0f,0.0f,	//V0
		//1.0f,-1.0f, 0.0f,	//V1
		//0.0f,1.0f,0.0f,		//V3

		//-1.0f, -1.0f,0.0f,
		//0.0f,1.0f,0.0f,
		//-1.0f,1.0f,0.0f

		/*
		//Cuadrado
		-0.75f, 0.25f, 0.0f,
		-0.25f, 0.25f, 0.0f,
		-0.25f, -0.25f, 0.0f,

		-0.75f, 0.25f, 0.0f,
		-0.25f, -0.25f, 0.0f,
		-0.75f, -0.25f, 0.0f,

		//Rombo
		0.5f, 0.75f, 0.0f,
		0.25f, 0.0f, 0.0f,
		0.5f, -0.75f, 0.0f,

		0.5f, 0.75f, 0.0f,
		0.75f, 0.0f, 0.0f,
		0.5f, -0.75f, 0.0f
		*/

		//Letra X
		-0.875f, 0.5f, 0.0f,
		-0.7916f, 0.5f, 0.f,
		-0.875f, 0.25f, 0.0f,

		-0.7916f, 0.5f, 0.f,
		-0.875f, 0.25f, 0.0f,
		-0.7916f, 0.25f, 0.0f,

		-0.875f, 0.25f, 0.0f,
		-0.7916f, 0.25f, 0.0f,
		- 0.8125f, 0.0f, 0.0f,

		-0.7916f, 0.25f, 0.0f,
		-0.8125f, 0.0f, 0.0f,
		-0.75f, 0.125f, 0.0f,

		-0.7082f, 0.5f, 0.0f,
		-0.625f, 0.5f, 0.0f,
		-0.7082f, 0.25f, 0.0f,

		-0.625f, 0.5f, 0.0f,
		-0.7082f, 0.25f, 0.0f,
		- 0.625f, 0.25f, 0.0f,

		-0.7082f, 0.25f, 0.0f,
		-0.625f, 0.25f, 0.0f,
		-0.6875f, 0.0f, 0.0f,

		-0.7082f, 0.25f, 0.0f,
		-0.6875f, 0.0f, 0.0f,
		-0.75f, 0.125f, 0.0f,

		-0.75f, 0.125f, 0.0f,
		-0.8125f, 0.0f, 0.0f,
		-0.6875f, 0.0f, 0.0f,

		-0.8125f, 0.0f, 0.0f,
		-0.6875f, 0.0f, 0.0f,
		-0.75f, -0.125f, 0.0f,

		-0.8125f, 0.0f, 0.0f,
		-0.75f, -0.125f, 0.0f,
		-0.7916f, -0.25f, 0.0f,

		- 0.6875f, 0.0f, 0.0f,
		-0.75f, -0.125f, 0.0f,
		-0.7082f, -0.25f, 0.0f,

		-0.8125f, 0.0f, 0.0f,
		-0.7916f, -0.25f, 0.0f,
		-0.875f, -0.25f, 0.0f,

		-0.6875f, 0.0f, 0.0f,
		-0.7082f, -0.25f, 0.0f,
		-0.625f, -0.25f, 0.0f,

		-0.875f, -0.25f, 0.0f,
		-0.7916f, -0.25f, 0.0f,
		-0.875f, -0.5f, 0.0f,

		-0.7916f, -0.25f, 0.0f,
		-0.875f, -0.5f, 0.0f,
		-0.7916f, -0.5f, 0.0f,

		-0.7082f, -0.25f, 0.0f,
		-0.625f, -0.25f, 0.0f,
		-0.7082f, -0.5f, 0.0f,

		-0.7082f, -0.5f, 0.0f,
		-0.625f, -0.25f, 0.0f,
		-0.625f, -0.5f, 0.0f,

		//Letra G
		-0.375f, 0.5f, 0.0f, //E
		-0.125f, 0.5f, 0.0f, //F
		- 0.2916f, 0.25f, 0.0f, //U1

		-0.125f, 0.5f, 0.0f, //F
		-0.2916f, 0.25f, 0.0f, //U1
		-0.2082f, 0.25f, 0.0f, //T1

		-0.125f, 0.5f, 0.0f, //F
		-0.2082f, 0.25f, 0.0f, //T1
		-0.125f, 0.125f, 0.0f, //R1

		-0.125f, 0.125f, 0.0f, //R1
		-0.2082f, 0.25f, 0.0f, //T1
		-0.2082f, 0.125f, 0.0f, //S1

		-0.375f, 0.5f, 0.0f, //E
		-0.2916f, 0.25f, 0.0f, //U1
		-0.375F, -0.5f, 0.0f, //G

		-0.2916f, 0.25f, 0.0f, //U1
		-0.375F, -0.5f, 0.0f, //G
		-0.2916f, -0.375f, 0.0f, //V1


		-0.2916f, -0.375f, 0.0f, //V1
		-0.375F, -0.5f, 0.0f, //G
		-0.125f, -0.5f, 0.0f, //H

		-0.2916f, -0.375f, 0.0f, //V1
		-0.125f, -0.5f, 0.0f, //H
		-0.16f, -0.375f, 0.0f, //W1

		-0.125f, -0.5f, 0.0f, //H
		-0.16f, -0.375f, 0.0f, //W1
		-0.125f, 0.0f, 0.0f, //B2

		-0.16f, -0.375f, 0.0f, //W1
		-0.125f, 0.0f, 0.0f, //B2
		-0.16f, -0.25f, 0.0f, //Z1

		- 0.125f, 0.0f, 0.0f, //B2
		-0.16f, -0.25f, 0.0f, //Z1
		- 0.25f, -0.25f, 0.0f, //A2

		- 0.125f, 0.0f, 0.0f, //B2
		-0.25f, -0.25f, 0.0f, //A2
		-0.25f, 0.0f, 0.0f, //Q1

		//Letra H
		0.125f, 0.5f, 0.0f, //I
		0.2082f, 0.5f, 0.0f, //A1
		0.125f, -0.5f, 0.0f, //K

		0.2082f, 0.5f, 0.0f, //A1
		0.125f, -0.5f, 0.0f, //K
		0.2082f, -0.5f, 0.0f, //C1

		0.2082f, 0.125f, 0.0f, //C2
		0.2914f, 0.125f, 0.0f, //F2
		0.2082f, -0.125f, 0.0f, //D2

		0.2914f, 0.125f, 0.0f, //F2
		0.2082f, -0.125f, 0.0f, //D2
		0.2914f, -0.125f, 0.0f, //E2

		0.2914f, 0.5f, 0.0f, //B1
		0.375f, 0.5f, 0.0f, //J
		0.2914F, -0.5f, 0.0f, // D1

		0.375f, 0.5f, 0.0f, //J
		0.2914f, -0.5f, 0.0f, // D1
		0.375f, -0.5f, 0.0f, //L

		//Letra A
		0.7082f, 0.5f, 0.0f, //G1
		0.625f, 0.25f, 0.0f, //E1
		0.7082f, 0.25f, 0.0f, //G2

		0.7082f, 0.5f, 0.0f, //G1
		0.7082f, 0.25f, 0.0f, //G2
		0.7914f, 0.5f, 0.0f, //H1

		0.7082f, 0.25f, 0.0f, //G2
		0.7914f, 0.5f, 0.0f, //H1
		0.7914f, 0.25f, 0.0f, //J2

		0.7914f, 0.5f, 0.0f, //H1
		0.7914f, 0.25f, 0.0f, //J2
		0.875f, 0.25f, 0.0f, //F1

		0.625f, 0.25f, 0.0f, //E1
		0.7082f, 0.25f, 0.0f, //G2
		0.625f, -0.5f, 0.0f, //O

		0.7082f, 0.25f, 0.0f, //G2
		0.625f, -0.5f, 0.0f, //O
		0.7082f, -0.5f, 0.0f, //M

		0.7082f, 0.0f, 0.0f, //H2
		0.7914f, 0.0f, 0.0f,  //K2
		0.7082f, -0.25f, 0.0f, //I2

		0.7914f, 0.0f, 0.0f,  //K2
		0.7082f, -0.25f, 0.0f, //I2
		0.7914f, -0.25f, 0.0f, //L2

		0.7914f, 0.25f, 0.0f, //J2
		0.875f, 0.25f, 0.0f, //F1
		0.7914f, -0.5f, 0.0f, //N

		0.875f, 0.25f, 0.0f, //F1
		0.7914f, -0.5f, 0.0f, //N
		0.875f, -0.5f, 0.0f //P

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		//Inicia en el vertice 0, lee de 3 en tre dato, tipo float,  , numero de columnas por renglon, 1 si hay una columan mas, stride cuanto datos ignora, en este caso no se necesita pues se tienen 3 columnas
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}

//Siempre tener y nunca cambiar
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

//Siempre tener y nunca cambiar
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 01 Hola Triangulo", NULL, NULL);

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

		//Ayuda a almacenar el tiempo
		colorT = glfwGetTime();

		//Establecemos el tiempo de 2 segundos
		if (colorT >= 2.0) {
			//Ayuda a medir el tiempo transcurrido
			glfwSetTime(0.0);

			//Para que los valores del RGB cambien se uso rand()
			rojo = (float)rand() / RAND_MAX;
			verde = (float)rand() / RAND_MAX;
			azul = (float)rand() / RAND_MAX;
		}

		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Limpiar la ventana
		
		//glClearColor(1.0, 0.0, 0.0, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//Comentar para ver mejor el ejercicio 2
		/*
		if (colorT < 10.0f)
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

		if (colorT >= 10.0f && colorT < 30.0f)
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

		if (colorT >= 30.0f && colorT < 50.0f)
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

		if (colorT >= 50.0f)
			colorT = 0.0f;

		colorT += 0.01f;
		*/
		//Comentar hasta la linea de arriba

		glUseProgram(shader);

		glBindVertexArray(VAO); //Decimos que vamos a usar los datos de VAO
		// Numero de renglones del 0 al 3
		// Descomentar esta linea para que se dibujen las figura del ejercicio 2
		glDrawArrays(GL_TRIANGLES,0,414);
		glBindVertexArray(0); //Limpia despues de dibujarse

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}