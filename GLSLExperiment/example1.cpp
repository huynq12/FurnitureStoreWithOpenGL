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
color4 colors[NumPoints];
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

// Model-view and projection matrices uniform location
GLuint viewLoc,modelLoc, projectionLoc;
mat4 model,table_view,keTV_view,tuCao_view,tuTreo_view,tuQuanAo_view;
GLfloat value[] = { 0,0,0,0 };
//Lookat function
GLfloat l = -1, r = 1, bottom = -1, top = 1, zNear = 3, zFar = 10;
//camera controller 
vec3 eye = vec3(0,1,3);
vec3 at = vec3(0,0,0);
vec3 up = vec3(0, 1, 0);
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
	point4 light_position(0 ,2, 0, 0.0);
	color4 light_ambient(0.2, 0.2, 0.2, 1.0);
	color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
	color4 light_specular(1.0, 1.0, 1.0, 1.0);
	color4 material_ambient(1.0, 0.0, 1.0, 1.0);
	color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
	color4 material_specular(1.0, 0.8, 0.0, 1.0);
	float material_shininess = 150;
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
	viewLoc = glGetUniformLocation(program, "View");
	modelLoc = glGetUniformLocation(program, "Model");
	projectionLoc = glGetUniformLocation(program, "Projection");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
//----------------------------------------------------------------------
//bàn gồm 4 chân
void ban4chan() {
	//mặt bàn 1m2 x 60 x 2
	mat4 matban = Scale(1.2, 0.02, 0.6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model* table_view * matban);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//4 chân 80 x 6 x 6
	mat4 chan1 = Translate(-.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * chan1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);


	mat4 chan2 = Translate(-.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * chan2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);


	mat4 chan3 = Translate(.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * chan3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);


	mat4 chan4 = Translate(.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * chan4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
//ngăn kéo bàn học
void nganKeo() {
	//54 x 2 x 60
	// hộp tủ ngăn kéo bên trái
	mat4 tuNganKeo = Translate(-.55, -.06, 0) * Scale(.02, .1, .48);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * tuNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//ngăn kéo chính
	mat4 nganKeo = Translate(-.27, -.1, 0) * Translate(0, 0, value[0]) * Scale(.54, .02, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * nganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//cửa ngăn kéo phía trước
	mat4 cuaNganKeo = Translate(-.27, -.075, .28) * Translate(0, 0, value[0]) * Scale(.54, .15, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * cuaNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void hopTu() {
	//hộp bàn sau
	mat4 tuBanSau = Translate(0, -.36, -.29) * Scale(1.08, .7, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * tuBanSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ bên phải
	mat4 hopTuPhai = Translate(.55, -.36, 0) * Scale(.02, .7, .48);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ bên trái
	mat4 hopTuTrai = Translate(0, -.36, 0) * Scale(.02, .7, .56);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ phía dưới 
	mat4 hopTuDay = Translate(.27, -.7, 0) * Scale(.55, .02, .56);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuDay);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cửa tủ có thể mở góc 90
	mat4 cuaTu = Translate(.53, -.36, .29) * RotateY(value[1]) * Translate(-.27, 0, 0) * Scale(.55, .7, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void keSach() {
	//xương cạnh trái kệ sách
	mat4 xuongDoc1 = Translate(-.59,.51,-.20) * Scale(.02, 1, .2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * xuongDoc1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//xương cạnh phải
	mat4 xuongDoc2 = Translate(.59, .51, -.20) * Scale(.02, 1, .2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * xuongDoc2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tấm chắn sau kệ
	//xương ngang trên cùng
	mat4 xuongNgang1 = Translate(0, .91, -.20) * Scale(1.16,.02,.2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * xuongNgang1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//xương ngang thứ 2
	mat4 xuongNgang2 = Translate(0, .66, -.20) * Scale(1.16, .02, .2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * xuongNgang2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//xương ngang thứ 3
	mat4 xuongNgang3 = Translate(0, .41, -.2) * Scale(1.16, .02, .2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * xuongNgang3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tấm nối xương 1 - 2 
	mat4 tamNoi1_2 = Translate(0, .785, -.2) * Scale(.02,.23,.2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * tamNoi1_2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tủ mini
	//hộp tủ sau
	mat4 hopTuSau = Translate(0, .535, -.29) * Scale(.31, .23, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ trái
	mat4 hopTuTrai = Translate(-.15, .535, -.2) * Scale(.01, .23, .19);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ phai
	mat4 hopTuPhai = Translate(.15, .535, -.2) * Scale(.01, .23, .19);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cua tu
	mat4 cuaTu = Translate(.155, .535, -.1)*RotateY(value[1])*Translate(-.165,0,0) * Scale(.31, .23, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * table_view * cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void table() {
	table_view = Translate(0, 0.81, 1.5) * RotateY(90);

	ban4chan();
	nganKeo();
	hopTu();
	keSach();
}

void keTu() {
	//phần kệ dưới
	//mặt trên kệ
	mat4 matTren = Scale(2, .02, .6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model*keTV_view * matTren);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	// hộp tủ sau
	mat4 hopTuSau = Translate(0,-.24,-.29) * Scale(1.96,.46,.02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//hộp tủ trái
	mat4 hopTuTrai = Translate(-.99,-.24,0) * Scale(.02,.46,.6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//hộp tủ phải
	mat4 hopTuPhai = Translate(.99, -.24, 0) * Scale(.02, .46, .6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//mặt đáy kệ
	mat4 matDay = Translate(0,-.47,0) * Scale(2,.02,.6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * matDay);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm giữa ngang
	mat4 tamGiuaNgang = Translate(0, -.24, 0) * Scale(2, .02, .6);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamGiuaNgang);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm dọc 1
	mat4 tamDoc1 = Translate(-.40,-.12,.02) * Scale(.02,.22,.58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamDoc1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm dọc 2
	mat4 tamDoc2 = Translate(.40, -.12, .02) * Scale(.02, .22, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamDoc2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm dọc 3
	mat4 tamDoc3 = Translate(-.5, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamDoc3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm dọc 4
	mat4 tamDoc4 = Translate(0, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamDoc4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tấm dọc 5
	mat4 tamDoc5 = Translate(.5, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamDoc5);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	
}
void keTV_ngan_keo() {
	//ngan keo 
	mat4 nganKeo1 = Translate(-.75, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * nganKeo1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 nganKeo2 = Translate(-.25, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * nganKeo2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 nganKeo3 = Translate(.25, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * nganKeo3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 nganKeo4 = Translate(.75, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * nganKeo4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//cua keo
	mat4 cuaKeo1 = Translate(-.75, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * cuaKeo1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 cuaKeo2 = Translate(-.25, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * cuaKeo2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 cuaKeo3 = Translate(.25, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * cuaKeo3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 cuaKeo4 = Translate(.75, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * cuaKeo4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuKinh() {
	//xuong doc 1
	mat4 xuongDoc1 = Translate(-.99,.61,-.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//xuong doc 2
	mat4 xuongDoc2 = Translate(-.63, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//xuong doc 3
	mat4 xuongDoc3 = Translate(.63, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//xuong doc 4
	mat4 xuongDoc4 = Translate(.99, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//xuong doc sau trai
	mat4 xuongDoc5 = Translate(-.81,.61,-.29) * Scale(.34, 1.2, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc5);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//xuong doc sau phai
	mat4 xuongDoc6 = Translate(.81, .61, -.29) * Scale(.34, 1.2, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * xuongDoc6);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	
	//tam ngang 1
	mat4 tamNgang1 = Translate(-.81,1.22,-.15) * Scale(.38, .02, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tam ngang 2
	mat4 tamNgang2 = Translate(.81, 1.22, -.15) * Scale(.38, .02, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 3
	mat4 tamNgang3 = Translate(-.81, .92, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 4
	mat4 tamNgang4 = Translate(.81, .92, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 5
	mat4 tamNgang5 = Translate(-.81, .62, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang5);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 6
	mat4 tamNgang6 = Translate(.81, .62, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang6);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 7
	mat4 tamNgang7 = Translate(-.81, .32, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang7);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang 8
	mat4 tamNgang8 = Translate(.81, .32, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgang8);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//tam ngang giua
	mat4 tamNgangGiua = Translate(0,1.1,-.15) * Scale(1.28, .02, .2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * keTV_view * tamNgangGiua);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void keTV() {
	keTV_view = Translate(0, .5, -2)*RotateY(90);
	keTu();
	keTV_ngan_keo();
	tuKinh();
}
void tuCao_phanTinh() {
	//hộp tủ sau
	mat4 tuCao_hopTuSau = Translate(0,0,-.175) * Scale(0.4, 2, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model *tuCao_view * tuCao_hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ trái
	mat4 tuCao_hopTuTrai = Translate(-.19, 0, 0) * Scale(.02, 2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp tủ phải
	mat4 tuCao_hopTuPhai = Translate(.19, 0, 0) * Scale(.02, 2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//mặt trên
	mat4 tuCao_hopTren = Translate(0, .99, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopTren);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//mặt đáy
	mat4 tuCao_hopDay = Translate(0, -.99, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopDay);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tấm ngang
	mat4 tuCao_tamNgang1 = Translate(0, -.3, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tấm ngang
	mat4 tuCao_tamNgang2 = Translate(0, -.65, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuCao_phanDong() {
	//ngăn kéo
	mat4 tuCao_nganKeo1 = Translate(0, -.63, 0)*Translate(0,0,value[0]) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_nganKeo1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuCao_nganKeo2 = Translate(0, -.97, 0) * Translate(0, 0, value[0]) * Scale(.36, .02, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_nganKeo2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cửa kéo
	mat4 tuCao_cuaKeo1 = Translate(0, -.48, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_cuaKeo1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuCao_cuaKeo2 = Translate(0, -.82, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_cuaKeo2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//hộp ngăn kéo
	//trên
	mat4 tuCao_hopKeo1 = Translate(-.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopKeo1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuCao_hopKeo2 = Translate(.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopKeo2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//dưới
	mat4 tuCao_hopKeo3 = Translate(-.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopKeo3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuCao_hopKeo4 = Translate(.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_hopKeo4);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cửa tủ
	mat4 tuCao_cuaTu = Translate(.2, .35, .18) * RotateY(value[1])*Translate(-.2, 0, 0) * Scale(.4, 1.3, .02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuCao_view * tuCao_cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuCaoDon() {
	tuCao_view = Translate(0, 1, 0)*RotateY(90);
	tuCao_phanTinh();
	tuCao_phanDong();
}
void tuTreo_phanTinh()
{
	mat4 tuTreo_hopTuTrai = Translate(-.35,.4,0) * Scale(.01, .8, .4);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model *tuTreo_view* tuTreo_hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_hopTuPhai = Translate(.35, .4, 0) * Scale(.01, .8, .4);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_hopDay = Scale(.7, .01, .4);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_hopDay);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_hopTuSau = Translate(0, .4, -.2) * Scale(.7, .8, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_hopTuTren = Translate(0, .8,0) * Scale(.7, .01, .4);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_hopTuTren);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_tamNoiNgang = Translate(0, .5, 0) * Scale(.69, .01, .39);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_tamNoiNgang);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_tamNoiDoc = Translate(0, .25, -.045) * Scale(.01, .5, .3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_tamNoiDoc);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuTreo_phanDong() {
	mat4 tuTreo_cuaTrai = Translate(-.35, .25, 0.2)*RotateY(-value[1])*Translate(.17,0,0) * Scale(.35, .5, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_cuaTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuTreo_cuaPhai = Translate(.35, .25, 0.2) * RotateY(value[1]) * Translate(-.17,0,0) * Scale(.35, .5, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_cuaPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//cửa lật lên trên
	mat4 tuTreo_cuaLat = Translate(0, .8, 0.2) * RotateX(-value[1])*Translate(0,-.15,0) * Scale(.69, .3, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuTreo_view * tuTreo_cuaLat);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuTreo() {
	// cao 80 rộng 70 sâu 40
	tuTreo_view = Translate(1, 1, -3);
	tuTreo_phanTinh();
	tuTreo_phanDong();
}
void tuQuanAo_phanTinh() {
	mat4 tuQuanAo_hopTrai = Translate(-.595, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_hopTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_hopPhai = Translate(.595, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_hopPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_tamGiua = Translate(-.2, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_tamGiua);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_dayTu = Translate(0, .03, 0) * Scale(1.2, .05, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_dayTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_nocTu = Translate(0, 1.99, 0) * Scale(1.2, .01, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_nocTu);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_matSau = Translate(0, 1.025, -.25) * Scale(1.18, 1.94, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_matSau);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//tấm ngang nóc dài
	mat4 tuQuanAo_tamNgang = Translate(0,1.65, 0) * Scale(1.18, .01, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_tamNgang);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//các tấm ngang hộp tủ trái
	mat4 tuQuanAo_tamNgang1 = Translate(-.4, .43, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_tamNgang2 = Translate(-.4, .83, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_tamNgang3 = Translate(-.4, 1.23, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_tamNgang3);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	//đòn treo quần áo
	mat4 tuQuanAo_macTreo = Translate(.2, 1.6, 0) * Scale(.8, .01, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_macTreo);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuQuanAo_phanDong() {
	//cánh cửa hộp tủ trái
	mat4 tuQuanAo_cuaHopTrai = Translate(-.6, 1.025, .25)*RotateY(-value[1])*Translate(.2,0,0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_cuaHopTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	//2 cánh tủ chính
	mat4 tuQuanAo_cuaTrai = Translate(-.2, 1.025, .25) * RotateY(-value[1]) * Translate(.2, 0, 0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_cuaTrai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	mat4 tuQuanAo_cuaPhai = Translate(.595, 1.025, .25) * RotateY(value[1]) * Translate(-.2, 0, 0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * tuQuanAo_view * tuQuanAo_cuaPhai);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tuQuanAo() {
	// cao 2m rộng 1m2, sâu 50
	tuQuanAo_view = Translate(1, 0, 2.5) * RotateY(180);
	tuQuanAo_phanTinh();
	tuQuanAo_phanDong();
}
// sàn nhà
void ground() {
	
	mat4 ground =Scale(3, .01, 10);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * ground);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//draw model
	//ground(); //sàn
	table();	//bàn học
	//keTV();		//kệ tivi
	//tuCaoDon(); //tủ cao 
	//tuTreo();	//tủ treo
	//tuQuanAo();  //tủ quần áo
	glutSwapBuffers();
}
//----------------------------------------------------------------------


void keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
	/*case 'q': case 'Q':
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
		break;*/
	case 'u':
		eye += vec3(0, 0.05, 0);
		at += vec3(0, 0.05, 0);
		glutPostRedisplay();
		break;
	case 'U':
		eye += vec3(0, -0.05, 0);
		at += vec3(0, -0.05, 0);
		glutPostRedisplay();
		break;
	//move camera
	case 'd':
		eye += vec3(0.05,0,0);
		at += vec3(0.05, 0, 0);
		glutPostRedisplay();
		break;
	case 'a': 
		eye += vec3(-0.05, 0, 0);
		at += vec3(-0.05, 0, 0);
		glutPostRedisplay();
		break;
	case 'w': 
		eye += vec3(0, 0, -0.05);
		at += vec3(0, 0, -0.05);
		glutPostRedisplay();
		break;
	case 's': 
		eye += vec3(0, 0, 0.05);
		at += vec3(0, 0, 0.05);
		glutPostRedisplay();
		break;
	case 'k':
		value[0] += .05;
		if (value[0] > .3) value[0] = .3;
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
	case ' ':
		
		glutPostRedisplay();
		break;

	}
}
//----------------------------------------------------------------------
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, mv);


	mat4 projection = Perspective(100, GLfloat(width) / height, zNear, zFar);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, projection);
}
//----------------------------------------------------------------------
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("The Furniture Store");

	glewInit();
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	
	glutMainLoop();

	
	return 0;
}