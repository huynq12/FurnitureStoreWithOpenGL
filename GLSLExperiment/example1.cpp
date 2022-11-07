// Display a rotating cube with lighting
//
// Light and material properties are sent to the shader as uniform
// variables. Vertex positions and normals are sent after each
// rotation.
#include "Angel.h"
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
const int NumPoints = 36; //(6 faces)(2 triangles/face)
point4 points[NumPoints];
vec3 normals[NumPoints];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
						point4(-0.5, -0.5, 0.5, 1.0),
						point4(-0.5, 0.5, 0.5, 1.0),
						point4(0.5, 0.5, 0.5, 1.0),
						point4(0.5, -0.5, 0.5, 1.0),
						point4(-0.5, -0.5, -0.5, 1.0),
						point4(-0.5, 0.5, -0.5, 1.0),
						point4(0.5, 0.5, -0.5, 1.0),
						point4(0.5, -0.5, -0.5, 1.0)
};
// Array of rotation angles (in degrees) for each coordinate axis

GLfloat Theta[3] = { 0,0,0 };
GLfloat eyeDistance = 3;
GLfloat cameraMove[3] = { 0,0,eyeDistance };
// Model-view and projection matrices uniform location
GLuint modelViewLoc, projectionLoc;
mat4 model_view;
GLfloat value[] = { 0,0,0,0 };
//----------------------------------------------------------------------
// quad generates two triangles for each face and assigns colors
// to the vertices
int Index = 0;
void quad(int a, int b, int c, int d)
{
	// Initialize temporary vectors along the quad’s edge to
	// compute its face normal
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];
	vec3 normal = normalize(cross(u, v));
	normals[Index] = normal; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; points[Index] = vertices[b]; Index++;
	normals[Index] = normal; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; points[Index] = vertices[d]; Index++;
}
//----------------------------------------------------------------------
 //generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);	
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
//----------------------------------------------------------------------
// OpenGL initialization
void init(void)
{
	colorcube();
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals),NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points),sizeof(normals), normals);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
	// Initialize shader lighting parameters
	point4 light_position(0, 0, -1, 0.0);
	color4 light_ambient(0.2, 0.2, 0.2, 1.0);
	color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
	color4 light_specular(1.0, 1.0, 1.0, 1.0);
	color4 material_ambient(1.0, 0.0, 1.0, 1.0);
	color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
	color4 material_specular(1.0, 0.8, 0.0, 1.0);
	float material_shininess = 80;
	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;
	glUniform4fv(glGetUniformLocation(program, "ambientObject"),
		1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "diffuseObject"),
		1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "specularObject"),
		1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"),
		1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"),
		material_shininess);
	// Retrieve transformation uniform variable locations
	modelViewLoc = glGetUniformLocation(program, "ModelView");
	projectionLoc = glGetUniformLocation(program, "Projection");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
//----------------------------------------------------------------------
void matban() {
	mat4 matban = Scale(1.2, 0.02, 0.6);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * matban);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chan1() {
	mat4 chan1 = Translate(-.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * chan1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chan2() {
	mat4 chan2 = Translate(-.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * chan2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chan3() {
	mat4 chan3 = Translate(.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * chan3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chan4() {
	mat4 chan4 = Translate(.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * chan4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nganKeo() {
	//tu ngan keo
	mat4 tuNganKeo = Translate(-.55, -.06, 0) * Scale(.02, .1, .48);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * tuNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//ngăn kéo
	mat4 nganKeo = Translate(-.27, -.1, 0) * Translate(0, 0, value[0]) * Scale(.54, .02, .58);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * nganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//cua ngan keo
	mat4 cuaNganKeo = Translate(-.27, -.075, .28) * Translate(0, 0, value[0]) * Scale(.54, .15, .02);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * cuaNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void hopTu() {
	//tu ban sau
	mat4 tuBanSau = Translate(0, -.36, -.29) * Scale(1.08, .7, .02);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * tuBanSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hop tu phai
	mat4 hopTuPhai = Translate(.55, -.36, 0) * Scale(.02, .7, .48);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hop tu trai
	mat4 hopTuTrai = Translate(0, -.36, 0) * Scale(.02, .7, .56);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hop tu day
	mat4 hopTuDay = Translate(.27, -.7, 0) * Scale(.55, .02, .56);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * hopTuDay);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cua tu
	mat4 cuaTu = Translate(.53, -.36, .29) * RotateY(value[1]) * Translate(-.27, 0, 0) * Scale(.55, .7, .02);
	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, model_view * cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void table() {
	matban();
	chan1();
	chan2();
	chan3();
	chan4();
	nganKeo();
	hopTu();
}
void cameraController() {
	const vec3 cameraPos(cameraMove[0], cameraMove[1], cameraMove[2]);
	model_view = (Translate(-cameraPos) *
		RotateX(Theta[0]) *
		RotateY(Theta[1]) *
		RotateZ(Theta[2]));
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// camera controller
	cameraController();

	//draw model
	table();

	glutSwapBuffers();
}
//----------------------------------------------------------------------


void keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'p':
		Theta[0] += 5;
		if (Theta[0] > 360) Theta[0] -= 360;
		glutPostRedisplay();
		break;
	case 'P':
		Theta[0] -= 5;
		if (Theta[0] > 360) Theta[0] -= 360;
		glutPostRedisplay();
		break;
	case 'y':
		Theta[1] -= 5;
		if (Theta[1] > 360) Theta[1] -= 360;
		glutPostRedisplay();
		break;
	case 'Y':
		Theta[1] += 5;
		if (Theta[1] > 360) Theta[1] -= 360;
		glutPostRedisplay();
		break;
	case 'r':
		Theta[2] -= 5;
		if (Theta[2] > 360) Theta[2] -= 360;
		glutPostRedisplay();
		break;
	case 'R':
		Theta[2] += 5;
		if (Theta[2] > 360) Theta[2] -= 360;
		glutPostRedisplay();
		break;
	case 'd': cameraMove[0] += 0.2;
		if (cameraMove[0] > 2) cameraMove[0] = 2;
		glutPostRedisplay();
		break;
	case 'a': cameraMove[0] -= 0.2;
		if (cameraMove[0] < -2) cameraMove[0] = -2;
		glutPostRedisplay();
		break;
	case 'w': cameraMove[2] -= 0.2;
		if (cameraMove[2] > eyeDistance +1) cameraMove[2] = eyeDistance + 1;
		glutPostRedisplay();
		break;
	case 's': cameraMove[2] += 0.2;
		if (cameraMove[2] < -(eyeDistance+1)) cameraMove[2] = -(eyeDistance + 1);
		glutPostRedisplay();
		break;
	case 'k':
		value[0] += .05;
		if (value[0] > .54) value[0] = .54;
		glutPostRedisplay();
		break;
	case 'K':
		value[0] -= .05;
		if (value[0] < 0) value[0] = 0;
		glutPostRedisplay();
		break;
	case 'c':
		value[1] += 5;
		if (value[1] > 90) value[1] = 90;
		glutPostRedisplay();
		break;
	case 'C':
		value[1] -= 5;
		if (value[1] < 0) value[1] = 0;
		glutPostRedisplay();
		break;
	}
}
//----------------------------------------------------------------------
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	GLfloat aspect = GLfloat(width) / height;
	mat4 projection = Perspective(45, aspect, 0.5, 3.0);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
}
//----------------------------------------------------------------------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(350, 100);
	glutCreateWindow("Draw an object");

	glewInit();
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	
	glutMainLoop();

	
	return 0;
}