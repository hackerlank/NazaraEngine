#version 140

/********************Entrant********************/
in vec3 VertexPosition;

/********************Uniformes********************/
uniform mat4 WorldViewProjMatrix;

/********************Fonctions********************/
void main()
{
	gl_Position = WorldViewProjMatrix * vec4(VertexPosition, 1.0);
}
