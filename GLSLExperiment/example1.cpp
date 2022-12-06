
#include "Angel.h"
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
const int numPointsOfCube = 36; //số điểm tạo hlp
const int numPointsOfCylinder = 96; //số điểm tạo htru
const int numPointsOfCircle = 192; //số điểm tạo htron
//danh sach cac dinh tam giac
point4 arrVertices[numPointsOfCube + numPointsOfCylinder + numPointsOfCircle];
//danh sach cac color
color4 arrColors[numPointsOfCube+ numPointsOfCylinder+ numPointsOfCircle];
//danh sach cac vector phap tuyen
vec3 arrNormals[numPointsOfCube+ numPointsOfCylinder+ numPointsOfCircle];
//danh sach cac dinh cua hinh lap phuong
point4 verticesOfCube[8];
//danh sach cac color hlp
color4 colorsOfCube[8];
//danh sach cac dinh cua hinh tru
point4 verticesOfCylinder[18];
//danh sach cac color hlp
color4 colorsOfCylinder[10];
//danh sach cac dinh cua hinh tron
point4 verticesOfCircle[5][8];
//danh sach cac color hinh tron
color4 colorsOfCircle[10];
//cac bien anh sang mau
point4 light_position(0, 2, 0, 0.0);
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

/*color4 material_ambient(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
color4 material_specular(1.0, 0.8, 0.0, 1.0);*/
float material_shininess = 150;
color4 ambient_product;
color4 diffuse_product;
color4 specular_product;
// Model-view and projection matrices uniform location
GLuint view_loc,model_loc, projection_loc,program;
mat4 view,model,table_pos,keTV_pos,tuCao_pos,tuTreo_pos,tuQuanAo_pos;
GLfloat value[] = { 0,0,0,0 };
GLfloat theta[] = { 0,0,0,0 };
GLfloat cameraRotate[] = { 90,0,0 };
GLfloat cameraMove[] = {0,0,0};
//Lookat function
GLfloat l = -0.5, r = 0.5, bottom = -0.5, top = 0.5, zNear = 0.5, zFar = 10;
//camera controller 
GLfloat eyePos[3] = { 0,1.7,5 };
vec3 eye = vec3(0,2,5);
vec3 at = vec3(0,0,0);
vec3 up = vec3(0, 1, 0);
GLfloat t = 0.05;
//vec3 direction = normalize(vec3(cosf(DegreesToRadians*cameraRotate[0]) * abs(sinf(DegreesToRadians*cameraRotate[1])),
//	cosf(DegreesToRadians*cameraRotate[1]),
//	cosf(DegreesToRadians*cameraRotate[2]) * abs(sinf(DegreesToRadians*cameraRotate[1]))));
//
//vec3 cameraRight = normalize(cross(direction, up));
//vec4 cameraUp = normalize(cross(cameraRight, direction));
//----------------------------------------------------------------------
// quad generates two triangles for each face and assigns colors
// to the vertices
int Index = 0;
void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	verticesOfCube[0] = point4(-0.5, -0.5, 0.5, 1.0);
	verticesOfCube[1] = point4(-0.5, 0.5, 0.5, 1.0);
	verticesOfCube[2] = point4(0.5, 0.5, 0.5, 1.0);
	verticesOfCube[3] = point4(0.5, -0.5, 0.5, 1.0);
	verticesOfCube[4] = point4(-0.5, -0.5, -0.5, 1.0);
	verticesOfCube[5] = point4(-0.5, 0.5, -0.5, 1.0);
	verticesOfCube[6] = point4(0.5, 0.5, -0.5, 1.0);
	verticesOfCube[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	colorsOfCube[0] = color4(0.0, 0.0, 0.0, 1.0); // đen
	colorsOfCube[1] = color4(1.0, 0.0, 0.0, 1.0); // đỏ
	colorsOfCube[2] = color4(1.0, 1.0, 0.0, 1.0); // vàng
	colorsOfCube[3] = color4(0.0, 1.0, 0.0, 1.0); // xanh lá
	colorsOfCube[4] = color4(0.0, 0.0, 1.0, 1.0); // xanh lam
	colorsOfCube[5] = color4(1.0, 0.0, 1.0, 1.0); // tím
	colorsOfCube[6] = color4(1.0, 0.5, 0.0, 1.0); // cam
	colorsOfCube[7] = color4(0.0, 1.0, 1.0, 1.0); // xanh lơ
}
//----------------------------------------------------------------------
void quadOfCube(int a, int b, int c, int d)
{
	vec4 u = verticesOfCube[b] - verticesOfCube[a];
	vec4 v = verticesOfCube[c] - verticesOfCube[b];
	vec3 normal = normalize(cross(u, v));

	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[b]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[c]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[c]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCube[a]; arrVertices[Index] = verticesOfCube[d]; Index++;
}
void generateCube()  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/
{
	quadOfCube(1, 0, 3, 2);
	quadOfCube(2, 3, 7, 6);
	quadOfCube(3, 0, 4, 7);
	quadOfCube(6, 5, 1, 2);
	quadOfCube(4, 5, 6, 7);
	quadOfCube(5, 4, 0, 1);
}
void initCylinder()
{
	float top_heart = 0.5;
	float bottom_heart = -0.5;
	// Tâm mặt trên
	verticesOfCylinder[0] = point4(0, top_heart, 0, 1);

	// Mặt bên
	for (int i = 1; i <= 8; i++)
	{
		float radius = 0.5;
		float angle = (i - 1) * 45.0 / 360 * 2 * M_PI;
		float x = radius * cosf(angle);
		float z = radius * sinf(angle);
		verticesOfCylinder[i * 2 - 1] = point4(x, top_heart, z, 1);
		verticesOfCylinder[i * 2] = point4(x, bottom_heart, z, 1);
	}

	// Tâm mặt dưới 
	verticesOfCylinder[17] = point4(0, bottom_heart, 0, 1);

	colorsOfCylinder[0] = color4(1.0, 0.0, 0.0, 1.0); // đỏ
	colorsOfCylinder[1] = color4(1.0, 1.0, 0.0, 1.0); // vàng
	colorsOfCylinder[2] = color4(0.0, 1.0, 0.0, 1.0); // xanh lá
	colorsOfCylinder[3] = color4(0.0, 0.0, 1.0, 1.0); // xanh lam
	colorsOfCylinder[4] = color4(1.0, 0.0, 1.0, 1.0); // tím
	colorsOfCylinder[5] = color4(1.0, 0.0, 0.0, 1.0); // đỏ
	colorsOfCylinder[6] = color4(1.0, 1.0, 0.0, 1.0); // vàng
	colorsOfCylinder[7] = color4(0.0, 1.0, 0.0, 1.0); // xanh lá
	colorsOfCylinder[8] = color4(0.0, 0.0, 1.0, 1.0); // xanh lam
	colorsOfCylinder[9] = color4(1.0, 0.0, 1.0, 1.0); // tím
}
void sideOfCylinder(int a, int b, int c, int d, int color)
{
	vec4 u = verticesOfCylinder[b] - verticesOfCylinder[a];
	vec4 v = verticesOfCylinder[c] - verticesOfCylinder[b];
	vec3 normal = normalize(cross(u, v));

	// a -> b -> c -> a -> c -> d
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[b]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[c]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[c]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[d]; Index++;
}

void faceOfCylinder(int a, int b, int c, int color)
{
	vec4 u = verticesOfCylinder[b] - verticesOfCylinder[a];
	vec4 v = verticesOfCylinder[c] - verticesOfCylinder[b];
	vec3 normal = normalize(cross(u, v));

	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[b]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[c]; Index++;
}

void generateCylinder()
{
	// 6x8
	sideOfCylinder(2, 1, 3, 4, 0);
	sideOfCylinder(4, 3, 5, 6, 1);
	sideOfCylinder(6, 5, 7, 8, 2);
	sideOfCylinder(8, 7, 9, 10, 3);
	sideOfCylinder(10, 9, 11, 12, 4);
	sideOfCylinder(12, 11, 13, 14, 5);
	sideOfCylinder(14, 13, 15, 16, 6);
	sideOfCylinder(16, 15, 1, 2, 7);
	/*for (int i = 0; i < 7; i++) {
		sideOfCylinder(2*(i+1), 2*(i + 1)-1, 2 * (i + 1) +1, 2*i + 4, i);
	}
	sideOfCylinder(16, 15, 1, 2, 7);*/

	// 3x8
	
	faceOfCylinder(2, 17, 16, 9);
	faceOfCylinder(16, 17, 14, 9);
	faceOfCylinder(14, 17, 12, 9);
	faceOfCylinder(12, 17, 10, 9);
	faceOfCylinder(10, 17, 8, 9);
	faceOfCylinder(8, 17, 6, 9);
	faceOfCylinder(6, 17, 4, 9);
	faceOfCylinder(4, 17, 2, 9);
	/*faceOfCylinder(2, 17, 16, 8);

	for (int i = 6; i >=0; i--) {
		faceOfCylinder(2 * i+4, 17, 2 * i + 2, 8);
	}
	for (int i = 0; i <= 6; i++) {
		faceOfCylinder(2 * (i + 1) - 1, 0, 2 * (i + 1) + 1, 9);
	}
	faceOfCylinder(15, 0, 1, 9);*/

	// 3x8
	faceOfCylinder(1, 0, 3, 8);
	faceOfCylinder(3, 0, 5, 8);
	faceOfCylinder(5, 0, 7, 8);
	faceOfCylinder(7, 0, 9, 8);
	faceOfCylinder(9, 0, 11, 8);
	faceOfCylinder(11, 0, 13, 8);
	faceOfCylinder(13, 0, 15, 8);
	faceOfCylinder(15, 0, 1, 8);

	
}




void initGPUBuffer(void)
{
	//hinh lap phuong
	initCube();
	generateCube();
	//hinh tru
	initCylinder();
	generateCylinder();
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices) + sizeof(arrColors)+sizeof(arrNormals), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrVertices), arrVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(arrVertices), sizeof(arrColors), arrColors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(arrVertices) + sizeof(arrColors), sizeof(arrNormals), arrNormals);


}
void processLight(color4 material_ambient, color4 material_diffuse, color4 material_specular) {
	
	 ambient_product = light_ambient * material_ambient;
	 diffuse_product = light_diffuse * material_diffuse;
	 specular_product = light_specular * material_specular;
}

void shaderSetup() {
	// Load shaders and use the resulting shader program
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_vPosition);
	glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrVertices)));

	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrVertices) + sizeof(arrColors)));
	// Initialize shader lighting parameters
	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
	// Retrieve transformation uniform variable locations
	view_loc = glGetUniformLocation(program, "View");
	model_loc = glGetUniformLocation(program, "Model");
	projection_loc = glGetUniformLocation(program, "Projection");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void drawCube(float x, float y, float z,mat4 model_pos)
{
	mat4 instance = Scale(x, y, z);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void drawCylinder(float x,float y,float z,mat4 model_pos)
{
	mat4 instance = Scale(x, y, z);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}

//----------------------------------------------------------------------

//bàn gồm 4 chân
void ban4chan() {
	//mặt bàn 1m2 x 60 x 2
	mat4 matban = Scale(1.2, 0.02, 0.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* table_pos * matban);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//4 chân 80 x 6 x 6
	mat4 chan1 = Translate(-.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * chan1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);


	mat4 chan2 = Translate(-.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * chan2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);


	mat4 chan3 = Translate(.57, -.41, -.27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * chan3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);


	mat4 chan4 = Translate(.57, -.41, .27) * Scale(.06, .8, .06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * chan4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
//ngăn kéo bàn học
void nganKeo() {
	//54 x 2 x 60
	// hộp tủ ngăn kéo bên trái
	mat4 tuNganKeo = Translate(-.55, -.06, 0) * Scale(.02, .1, .48);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * tuNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//ngăn kéo chính
	mat4 nganKeo = Translate(-.27, -.1, 0) * Translate(0, 0, value[0]) * Scale(.54, .02, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * nganKeo);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//cửa ngăn kéo phía trước
	mat4 cuaNganKeo = Translate(-.27, -.075, .28) * Translate(0, 0, value[0]) * Scale(.54, .15, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * cuaNganKeo);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void hopTu() {
	//hộp bàn sau
	mat4 tuBanSau = Translate(0, -.36, -.29) * Scale(1.08, .7, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * tuBanSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ bên phải
	mat4 hopTuPhai = Translate(.55, -.36, 0) * Scale(.02, .7, .48);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ bên trái
	mat4 hopTuTrai = Translate(0, -.36, 0) * Scale(.02, .7, .56);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ phía dưới 
	mat4 hopTuDay = Translate(.27, -.7, 0) * Scale(.55, .02, .56);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuDay);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//cửa tủ có thể mở góc 90
	mat4 cuaTu = Translate(.53, -.36, .29) * RotateY(value[1]) * Translate(-.27, 0, 0) * Scale(.55, .7, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void keSach() {
	//xương cạnh trái kệ sách
	mat4 xuongDoc1 = Translate(-.59,.51,-.20) * Scale(.02, 1, .2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * xuongDoc1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//xương cạnh phải
	mat4 xuongDoc2 = Translate(.59, .51, -.20) * Scale(.02, 1, .2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * xuongDoc2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tấm chắn sau kệ
	//xương ngang trên cùng
	mat4 xuongNgang1 = Translate(0, .91, -.20) * Scale(1.16,.02,.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * xuongNgang1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//xương ngang thứ 2
	mat4 xuongNgang2 = Translate(0, .66, -.20) * Scale(1.16, .02, .2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * xuongNgang2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//xương ngang thứ 3
	mat4 xuongNgang3 = Translate(0, .41, -.2) * Scale(1.16, .02, .2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * xuongNgang3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tấm nối xương 1 - 2 
	mat4 tamNoi1_2 = Translate(0, .785, -.2) * Scale(.02,.23,.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * tamNoi1_2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tủ mini
	//hộp tủ sau
	mat4 hopTuSau = Translate(0, .535, -.29) * Scale(.31, .23, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ trái
	mat4 hopTuTrai = Translate(-.15, .535, -.2) * Scale(.01, .23, .19);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ phai
	mat4 hopTuPhai = Translate(.15, .535, -.2) * Scale(.01, .23, .19);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//cua tu
	mat4 cuaTu = Translate(.155, .535, -.1)*RotateY(value[1])*Translate(-.165,0,0) * Scale(.31, .23, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * table_pos * cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}

void table() {
	table_pos = Translate(-2.2, 0.81, 2.5)* RotateY(90);

	ban4chan();
	nganKeo();
	hopTu();
	keSach();
}

void keTu() {
	//phần kệ dưới
	//mặt trên kệ
	mat4 mattop_heart = Scale(2, .02, .6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model*keTV_pos * mattop_heart);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	// hộp tủ sau
	mat4 hopTuSau = Translate(0,-.24,-.29) * Scale(1.96,.46,.02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//hộp tủ trái
	mat4 hopTuTrai = Translate(-.99,-.24,0) * Scale(.02,.46,.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//hộp tủ phải
	mat4 hopTuPhai = Translate(.99, -.24, 0) * Scale(.02, .46, .6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//mặt đáy kệ
	mat4 matDay = Translate(0,-.47,0) * Scale(2,.02,.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * matDay);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm giữa ngang
	mat4 tamGiuaNgang = Translate(0, -.24, 0) * Scale(2, .02, .6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamGiuaNgang);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm dọc 1
	mat4 tamDoc1 = Translate(-.40,-.12,.02) * Scale(.02,.22,.58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamDoc1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm dọc 2
	mat4 tamDoc2 = Translate(.40, -.12, .02) * Scale(.02, .22, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamDoc2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm dọc 3
	mat4 tamDoc3 = Translate(-.5, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamDoc3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm dọc 4
	mat4 tamDoc4 = Translate(0, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamDoc4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tấm dọc 5
	mat4 tamDoc5 = Translate(.5, -.36, .02) * Scale(.02, .21, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamDoc5);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	
}
void keTV_ngan_keo() {
	//ngan keo 
	mat4 nganKeo1 = Translate(-.75, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * nganKeo1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 nganKeo2 = Translate(-.25, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * nganKeo2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 nganKeo3 = Translate(.25, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * nganKeo3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 nganKeo4 = Translate(.75, -.45, 0) * Translate(0, 0, value[0]) * Scale(.47, .02, .58);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * nganKeo4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//cua keo
	mat4 cuaKeo1 = Translate(-.75, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * cuaKeo1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 cuaKeo2 = Translate(-.25, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * cuaKeo2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 cuaKeo3 = Translate(.25, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * cuaKeo3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 cuaKeo4 = Translate(.75, -.36, .29) * Translate(0, 0, value[0]) * Scale(.49, .25, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * cuaKeo4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuKinh() {
	//xuong doc 1
	mat4 xuongDoc1 = Translate(-.99,.61,-.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//xuong doc 2
	mat4 xuongDoc2 = Translate(-.63, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//xuong doc 3
	mat4 xuongDoc3 = Translate(.63, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//xuong doc 4
	mat4 xuongDoc4 = Translate(.99, .61, -.15) * Scale(.02, 1.2, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//xuong doc sau trai
	mat4 xuongDoc5 = Translate(-.81,.61,-.29) * Scale(.34, 1.2, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc5);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//xuong doc sau phai
	mat4 xuongDoc6 = Translate(.81, .61, -.29) * Scale(.34, 1.2, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * xuongDoc6);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	
	//tam ngang 1
	mat4 tamNgang1 = Translate(-.81,1.22,-.15) * Scale(.38, .02, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tam ngang 2
	mat4 tamNgang2 = Translate(.81, 1.22, -.15) * Scale(.38, .02, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 3
	mat4 tamNgang3 = Translate(-.81, .92, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 4
	mat4 tamNgang4 = Translate(.81, .92, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 5
	mat4 tamNgang5 = Translate(-.81, .62, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang5);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 6
	mat4 tamNgang6 = Translate(.81, .62, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang6);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 7
	mat4 tamNgang7 = Translate(-.81, .32, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang7);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang 8
	mat4 tamNgang8 = Translate(.81, .32, -.15) * Scale(.34, .01, .28);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgang8);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//tam ngang giua
	mat4 tamNgangGiua = Translate(0,1.1,-.15) * Scale(1.28, .02, .2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * keTV_pos * tamNgangGiua);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}

void keTV() {
	keTV_pos = Translate(0, .5, -2);//*RotateY(90);
	keTu();
	keTV_ngan_keo();
	tuKinh();
}
void tuCao_phanTinh() {
	//hộp tủ sau
	mat4 tuCao_hopTuSau = Translate(0,0,-.175) * Scale(0.4, 2, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model *tuCao_pos * tuCao_hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ trái
	mat4 tuCao_hopTuTrai = Translate(-.19, 0, 0) * Scale(.02, 2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp tủ phải
	mat4 tuCao_hopTuPhai = Translate(.19, 0, 0) * Scale(.02, 2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//mặt trên
	mat4 tuCao_hoptop_heart = Translate(0, .99, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hoptop_heart);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//mặt đáy
	mat4 tuCao_hopDay = Translate(0, -.99, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopDay);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tấm ngang
	mat4 tuCao_tamNgang1 = Translate(0, -.3, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tấm ngang
	mat4 tuCao_tamNgang2 = Translate(0, -.65, 0) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuCao_phanDong() {
	//ngăn kéo
	mat4 tuCao_nganKeo1 = Translate(0, -.63, 0)*Translate(0,0,value[0]) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_nganKeo1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuCao_nganKeo2 = Translate(0, -.97, 0) * Translate(0, 0, value[0]) * Scale(.36, .02, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_nganKeo2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//cửa kéo
	mat4 tuCao_cuaKeo1 = Translate(0, -.48, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_cuaKeo1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuCao_cuaKeo2 = Translate(0, -.82, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_cuaKeo2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//hộp ngăn kéo
	//trên
	mat4 tuCao_hopKeo1 = Translate(-.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopKeo1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuCao_hopKeo2 = Translate(.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopKeo2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//dưới
	mat4 tuCao_hopKeo3 = Translate(-.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopKeo3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuCao_hopKeo4 = Translate(.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_hopKeo4);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//cửa tủ
	mat4 tuCao_cuaTu = Translate(.2, .35, .18) * RotateY(value[1])*Translate(-.2, 0, 0) * Scale(.4, 1.3, .02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuCao_pos * tuCao_cuaTu);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuCaoDon() {
	tuCao_pos = Translate(0, 1, 0);//*RotateY(90);
	tuCao_phanTinh();
	tuCao_phanDong();
}
void tuTreo_phanTinh()
{
	mat4 tuTreo_hopTuTrai = Translate(-.35,.4,0) * Scale(.01, .8, .4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model *tuTreo_pos* tuTreo_hopTuTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_hopTuPhai = Translate(.35, .4, 0) * Scale(.01, .8, .4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_hopTuPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_hopDay = Scale(.7, .01, .4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_hopDay);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_hopTuSau = Translate(0, .4, -.2) * Scale(.7, .8, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_hopTuSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_hopTutop_heart = Translate(0, .8,0) * Scale(.7, .01, .4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_hopTutop_heart);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_tamNoiNgang = Translate(0, .5, 0) * Scale(.69, .01, .39);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_tamNoiNgang);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_tamNoiDoc = Translate(0, .25, -.045) * Scale(.01, .5, .3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_tamNoiDoc);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuTreo_phanDong() {
	mat4 tuTreo_cuaTrai = Translate(-.35, .25, 0.2)*RotateY(-value[1])*Translate(.17,0,0) * Scale(.35, .5, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_cuaTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuTreo_cuaPhai = Translate(.35, .25, 0.2) * RotateY(value[1]) * Translate(-.17,0,0) * Scale(.35, .5, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_cuaPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//cửa lật lên trên
	mat4 tuTreo_cuaLat = Translate(0, .8, 0.2) * RotateX(-value[1])*Translate(0,-.15,0) * Scale(.69, .3, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuTreo_pos * tuTreo_cuaLat);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuTreo() {
	// cao 80 rộng 70 sâu 40
	tuTreo_pos = Translate(1, 1, -3);
	tuTreo_phanTinh();
	tuTreo_phanDong();
}
void tuQuanAo_phanTinh() {
	mat4 tuQuanAo_hopTrai = Translate(-.595, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_hopTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_hopPhai = Translate(.595, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_hopPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_tamGiua = Translate(-.2, 1.025, 0) * Scale(.01, 1.94, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_tamGiua);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_dayTu = Translate(0, .03, 0) * Scale(1.2, .05, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_dayTu);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_nocTu = Translate(0, 1.99, 0) * Scale(1.2, .01, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_nocTu);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_matSau = Translate(0, 1.025, -.25) * Scale(1.18, 1.94, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_matSau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tấm ngang nóc dài
	mat4 tuQuanAo_tamNgang = Translate(0,1.65, 0) * Scale(1.18, .01, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_tamNgang);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//các tấm ngang hộp tủ trái
	mat4 tuQuanAo_tamNgang1 = Translate(-.4, .43, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_tamNgang1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_tamNgang2 = Translate(-.4, .83, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_tamNgang2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_tamNgang3 = Translate(-.4, 1.23, 0) * Scale(.4, .01, .5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_tamNgang3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//đòn treo quần áo
	mat4 tuQuanAo_macTreo = Translate(.2, 1.6, 0) * Scale(.8, .01, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_macTreo);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuQuanAo_phanDong() {
	//cánh cửa hộp tủ trái
	mat4 tuQuanAo_cuaHopTrai = Translate(-.6, 1.025, .25)*RotateY(-value[1])*Translate(.2,0,0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_cuaHopTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//2 cánh tủ chính
	mat4 tuQuanAo_cuaTrai = Translate(-.2, 1.025, .25) * RotateY(-value[1]) * Translate(.2, 0, 0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_cuaTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 tuQuanAo_cuaPhai = Translate(.595, 1.025, .25) * RotateY(value[1]) * Translate(-.2, 0, 0) * Scale(.39, 1.94, .01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * tuQuanAo_pos * tuQuanAo_cuaPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void tuQuanAo() {
	tuQuanAo_pos = Translate(1, 0, 2.5);// * RotateY(180);
	tuQuanAo_phanTinh();
	tuQuanAo_phanDong();
}

//bối cảnh
void phong(float width,float height,float depth,float wallWidth) {
	mat4 ground = Scale(width, .01, depth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * ground);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tường trái
	mat4 wall1 =Translate(-width/2,height/2,0)* Scale(wallWidth, height, depth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * wall1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	
	//tường phải
	mat4 wall2 = Translate(width/2, height/2, 0) * Scale(wallWidth, height, depth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * wall2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//tường sau
	mat4 wall3 = Translate(0, height/2, -depth/2) * Scale(width, height, wallWidth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * wall3);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	//phía trước
	mat4 frontWall1 = Translate(-((width/2)-0.5), height/2, depth/2) * Scale(1, height, wallWidth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * frontWall1);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 frontWall2 = Translate((width / 2) - 0.5, height/2, depth/2) * Scale(1, height, wallWidth);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * frontWall2);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	at = vec3(cosf(DegreesToRadians *cameraRotate[0]),0,cosf(DegreesToRadians*cameraRotate[2])) + eye;
	//at = direction + eye;
	view = RotateY(cameraRotate[1]) * LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view );

	mat4 p = Frustum(l, r, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE,p);

	
	//draw model
	/*
	phong(5,3.5,7,0.05); //bối cảnh cửa hàng rộng 5m, cao 3.5m, sâu 7m, tường dày 5cm
	table();	//bàn học
	keTV();		//kệ tivi
	tuCaoDon(); //tủ cao 
	tuTreo();	//tủ treo
	tuQuanAo();  //tủ quần áo
	*/
	glutSwapBuffers();

}
//----------------------------------------------------------------------


void keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
		
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	/*case 'x':
		theta[0] += 2;
		glutPostRedisplay();
		break;
	case 'X':
		theta[0] -= 2;
		glutPostRedisplay();
		break;*/
	
	case 'y':
		cameraRotate[1] += 5;
		glutPostRedisplay();
		break;
	case 'Y':
		cameraRotate[1] -=5;
		glutPostRedisplay();
		break;
	
	/*case 'd':
		eye += cameraRight * 0.1;
		glutPostRedisplay();
		break;
	case 'a': 
		eye += -cameraRight * 0.1;
		glutPostRedisplay();
		break;
	case 'w': 
		eye += direction * 0.1;
		glutPostRedisplay();
		break;
	case 's': 
		eye += -direction * 0.1;
		glutPostRedisplay();
		break;*/
	case 'a':
		eye += vec3(t, 0, 0);
		glutPostRedisplay();
		break;
	case 'd':
		eye += vec3(-t, 0, 0);
		glutPostRedisplay();
		break;
	case 'w':
		eye += vec3(0, 0, t);

		glutPostRedisplay();
		break;
	case 's':
		eye += vec3(0, 0, -t);

		glutPostRedisplay();
		break;
	//control door 
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
		//reset view volumn
	case ' ':
		 eye = vec3(0, 1.7, 6);
		 at = vec3(0, 1.5, 0);
		 up = vec3(0, 1, 0);
		theta[0] = 0;
		theta[1] = 0;
		theta[2] = 0;
		cameraRotate[0] = 90;
		glutPostRedisplay();
		break;
		
	}
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	
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
	initGPUBuffer();
	shaderSetup();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	
	glutMainLoop();

	return 0;
}