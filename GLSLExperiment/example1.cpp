
#include "Angel.h"
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
const int numPointsOfCube = 36; //số điểm tạo hlp
const int numPointsOfCylinder = 96; //số điểm tạo htru
const int circleNumPoint = 192;

//danh sach cac dinh tam giac
point4 arrVertices[numPointsOfCube + numPointsOfCylinder + circleNumPoint];
//danh sach cac color
color4 arrColors[numPointsOfCube + numPointsOfCylinder + circleNumPoint];
//danh sach cac vector phap tuyen
vec3 arrNormals[numPointsOfCube + numPointsOfCylinder + circleNumPoint];
//danh sach cac dinh cua hinh lap phuong
point4 verticesOfCube[8];
//danh sach cac color hlp
color4 colorsOfCube[8];
//danh sach cac dinh cua hinh tru
point4 verticesOfCylinder[18];
//danh sach cac color hlp
color4 colorsOfCylinder[10];

//cac bien anh sang mau
point4 light_position(0, 2, 0, 0.0);
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);
color4 ambient_product;
color4 diffuse_product;
color4 specular_product;
float material_shininess;
color4 material_ambient(1.0, 0.0, 1.0, 1.0);
color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
color4 material_specular(1.0, 0.8, 0.0, 1.0);
// Model-view and projection matrices uniform location
GLuint viewLoc, modelLoc, projectionLoc, program;
mat4 view, model, tablePos, keTVPos, tuCaoPos, tuTreoPos, tuQuanAoPos, banChuZPos, banTronPos, quayLeTanPos, storePos, robotPos;
GLfloat value[] = { 0,0,0,0 };
//frustum function
GLfloat l = -0.5, r = 0.5, bottom = -0.5, top = 0.5, zNear = 0.5, zFar = 10;
//camera controller 
vec3 eye = vec3(0, 2, 8);
vec3 at = vec3(0, 0, 0);
vec3 up = vec3(0, 1, 0);
GLfloat t = 0.05;
GLfloat cameraRotate[] = { 0,0,0 };
vec3 direction = normalize(vec3(cosf(DegreesToRadians * cameraRotate[0]) * abs(sinf(DegreesToRadians * cameraRotate[1])),
	sinf(DegreesToRadians * cameraRotate[0]),
	cosf(DegreesToRadians * cameraRotate[2]) * abs(cosf(DegreesToRadians * cameraRotate[1]))));
vec3 cameraRight = normalize(cross(direction, up));
//control model
bool batDen = false;
GLfloat door_tx[6] = { 0,0,0,0,0,0 };
//bàn học
float table_x=3,table_y=0.81,table_z=1,table_keo, table_moCuaTu,tableSpin=-90;
//kệ tv
float keTV_x=0.1,keTV_y=0.5, keTV_z=-4.5,keTV_keo=0,keTV_xoay=0;
bool nguoc=false;
//robot
bool robotMode = false;
float robot_x = -2, robot_y = 0, robot_z = 3.5, robot_headSpin,robot_baseSpin, robot_baseHi;
//tủ cao
float tuCao_moCua,tuCao_keo,tuCao_keo2,tuCao_x=3.2,tuCao_y=1,tuCao_z=4,tuCaoSpin=-90;
//quạt trần
bool batQuat,tatQuat;
float quatTranSpin,quatTranSpeed=1;
//tủ quần áo
float tuQuanAo_x = 3, tuQuanAo_y = 0, tuQuanAo_z = 2.5, tuQuanAo_moCua,tuQuanAoSpin=-90;
//----------------------------------------------------------------------
#pragma region Phần kỹ thuật 
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
		float angle = (i - 1) * 45 / 360 * 2 * M_PI;
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

void bottomTriange_Cylinder(int a, int b, int c, int color)
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
	// 3x8
	bottomTriange_Cylinder(2, 17, 16, 9);
	bottomTriange_Cylinder(16, 17, 14, 9);
	bottomTriange_Cylinder(14, 17, 12, 9);
	bottomTriange_Cylinder(12, 17, 10, 9);
	bottomTriange_Cylinder(10, 17, 8, 9);
	bottomTriange_Cylinder(8, 17, 6, 9);
	bottomTriange_Cylinder(6, 17, 4, 9);
	bottomTriange_Cylinder(4, 17, 2, 9);
	// 3x8
	bottomTriange_Cylinder(1, 0, 3, 8);
	bottomTriange_Cylinder(3, 0, 5, 8);
	bottomTriange_Cylinder(5, 0, 7, 8);
	bottomTriange_Cylinder(7, 0, 9, 8);
	bottomTriange_Cylinder(9, 0, 11, 8);
	bottomTriange_Cylinder(11, 0, 13, 8);
	bottomTriange_Cylinder(13, 0, 15, 8);
	bottomTriange_Cylinder(15, 0, 1, 8);
}
void CylinderCalPointsAndColor()
{
	float topHeart = 0.5;
	float botHeart = -0.5;
	// Tâm trên
	verticesOfCylinder[0] = point4(0, topHeart, 0, 1);

	// For để gán cho các đỉnh cạnh bên
	for (int i = 1; i <= 8; i++)
	{
		float banKinh = 0.5;
		float rad = (i - 1) * 45.0 / 180 * M_PI;
		// Tính x va z
		float x = banKinh * cosf(rad);
		float z = banKinh * sinf(rad);
		verticesOfCylinder[i * 2 - 1] = point4(x, topHeart, z, 1);
		verticesOfCylinder[i * 2] = point4(x, botHeart, z, 1);
	}

	// Tâm dưới
	verticesOfCylinder[17] = point4(0, botHeart, 0, 1);

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

// Hình trụ
void DrawCylinderSide(int a, int b, int c, int d, int color)
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

void CreateBottomTriangle(int a, int b, int c, int color)
{
	vec4 u = verticesOfCylinder[b] - verticesOfCylinder[a];
	vec4 v = verticesOfCylinder[c] - verticesOfCylinder[b];
	vec3 normal = normalize(cross(u, v));

	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[a]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[b]; Index++;
	arrNormals[Index] = normal; arrColors[Index] = colorsOfCylinder[color]; arrVertices[Index] = verticesOfCylinder[c]; Index++;
}

void CreateCylinder()
{
	//6x8
	DrawCylinderSide(2, 1, 3, 4, 0);
	DrawCylinderSide(4, 3, 5, 6, 1);
	DrawCylinderSide(6, 5, 7, 8, 2);
	DrawCylinderSide(8, 7, 9, 10, 3);
	DrawCylinderSide(10, 9, 11, 12, 4);
	DrawCylinderSide(12, 11, 13, 14, 5);
	DrawCylinderSide(14, 13, 15, 16, 6);
	DrawCylinderSide(16, 15, 1, 2, 7);


	//3x8
	CreateBottomTriangle(2, 17, 16, 9);
	CreateBottomTriangle(16, 17, 14, 9);
	CreateBottomTriangle(14, 17, 12, 9);
	CreateBottomTriangle(12, 17, 10, 9);
	CreateBottomTriangle(10, 17, 8, 9);
	CreateBottomTriangle(8, 17, 6, 9);
	CreateBottomTriangle(6, 17, 4, 9);
	CreateBottomTriangle(4, 17, 2, 9);

	//3x8
	CreateBottomTriangle(1, 0, 3, 8);
	CreateBottomTriangle(3, 0, 5, 8);
	CreateBottomTriangle(5, 0, 7, 8);
	CreateBottomTriangle(7, 0, 9, 8);
	CreateBottomTriangle(9, 0, 11, 8);
	CreateBottomTriangle(11, 0, 13, 8);
	CreateBottomTriangle(13, 0, 15, 8);
	CreateBottomTriangle(15, 0, 1, 8);


}

void generateModels() {
	//hinh lap phuong
	initCube();
	generateCube();
	//hinh tru
	//initCylinder();
	//generateCylinder();
	CylinderCalPointsAndColor();
	CreateCylinder();
}

void initGPUBuffer(void)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices) + sizeof(arrColors) + sizeof(arrNormals), NULL, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arrVertices) + sizeof(arrNormals), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrVertices), arrVertices);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(arrVertices), sizeof(arrColors), arrColors);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(arrVertices) + sizeof(arrColors), sizeof(arrNormals), arrNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(arrVertices), sizeof(arrNormals), arrNormals);
}
float RGBConvert(float x)
{
	return x / 255;
}
color4 RGBtoColor(int R, int G, int B)
{
	return color4(RGBConvert(R), RGBConvert(G), RGBConvert(B), 1.0);
}
color4 RGBtoColor(int r, int g, int b, int a)
{
	return color4(RGBConvert(r), RGBConvert(g), RGBConvert(b), RGBConvert(a));
}
void processLight() {
	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;
	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
}
color4 materialColor;
color4 reflexColor;
color4 mirrorReflexColor;

void initMaterial(color4 a, color4 b, color4 c, float d) {
	material_ambient = a;
	light_specular = b;
	material_diffuse = c;
	material_shininess = d;
	processLight();
}
void initMaterial(int a, int b, int c, float d) {
	material_ambient = RGBtoColor(a, b, c);
	material_diffuse = RGBtoColor(a, b, c);
	light_specular = RGBtoColor(a, b, c);
	material_shininess = d;
	processLight();

}

void shaderSetup() {
	// Load shaders and use the resulting shader program
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	// set up vertex arrays
	GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_vPosition);
	glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	//GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	//glEnableVertexAttribArray(loc_vColor);
	//glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrVertices)));

	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	//glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrVertices) + sizeof(arrColors)));
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrVertices)));


	// Retrieve transformation uniform variable locations
	viewLoc = glGetUniformLocation(program, "View");
	modelLoc = glGetUniformLocation(program, "Model");
	projectionLoc = glGetUniformLocation(program, "Projection");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

#pragma endregion

void drawCube(mat4 instance, mat4 localPos)
{
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * localPos * instance);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void drawCylinder(mat4 instance, mat4 localPos)
{
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * localPos * instance);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}

//----------------------------------------------------------------------
//-----------------Bàn học------------------------
#pragma region Bàn học
void chanBan(float x, float y, float z) {
	mat4 chan = Translate(x, y, z) * Scale(.06, .8, .06);
	drawCube(chan, tablePos);
}
void table_ban4chan() {
	//mặt bàn 1m2 x 60 x 2
	mat4 matban = Scale(1.2, 0.02, 0.6);
	drawCube(matban, tablePos);

	//4 chân 80 x 6 x 6
	chanBan(-.57, -.41, .27);
	chanBan(-.57, -.41, -.27);
	chanBan(.57, -.41, -.27);
	chanBan(.57, -.41, .27);

	//hộp bàn sau
	mat4 tuBanSau = Translate(0, -.36, -.29) * Scale(1.08, .7, .02);
	drawCube(tuBanSau, tablePos);
}

void table_nganKeo() {
	//-------------------ngăn kéo 54 x 2 x 60--------------------------

	// hộp tủ ngăn kéo bên trái
	mat4 tuNganKeo = Translate(-.55, -.06, 0) * Scale(.02, .1, .48);
	drawCube(tuNganKeo, tablePos);
	//ngăn kéo chính
	mat4 nganKeo = Translate(-.27, -.1, 0) * Translate(0, 0, table_keo) * Scale(.54, .02, .58);
	drawCube(nganKeo, tablePos);
	//cửa ngăn kéo phía trước
	mat4 cuaNganKeo = Translate(-.27, -.075, .28) * Translate(0, 0, table_keo) * Scale(.54, .15, .02);
	drawCube(cuaNganKeo, tablePos);
}
void table_hopTu() {
	//---------------hộp tủ -----------------
	//hộp tủ bên phải
	mat4 hopTuPhai = Translate(.55, -.36, 0) * Scale(.02, .7, .48);
	drawCube(hopTuPhai, tablePos);
	//hộp tủ bên trái
	mat4 hopTuTrai = Translate(0, -.36, 0) * Scale(.02, .7, .56);
	drawCube(hopTuTrai, tablePos);
	//hộp tủ phía dưới 
	mat4 hopTuDay = Translate(.27, -.7, 0) * Scale(.55, .02, .56);
	drawCube(hopTuDay, tablePos);
	//cửa tủ có thể mở góc 90
	mat4 cuaTu = Translate(.53, -.36, .29) * RotateY(table_moCuaTu) * Translate(-.27, 0, 0) * Scale(.55, .7, .02);
	drawCube(cuaTu, tablePos);
}
void table_keSach() {
	//xương cạnh trái kệ sách
	mat4 xuongDoc1 = Translate(-.59, .51, -.20) * Scale(.02, 1, .2);
	drawCube(xuongDoc1, tablePos);
	//xương cạnh phải
	mat4 xuongDoc2 = Translate(.59, .51, -.20) * Scale(.02, 1, .2);
	drawCube(xuongDoc2, tablePos);
	//tấm chắn sau kệ
	//xương ngang trên cùng
	mat4 xuongNgang1 = Translate(0, .91, -.20) * Scale(1.16, .02, .2);
	drawCube(xuongNgang1, tablePos);
	//xương ngang thứ 2
	mat4 xuongNgang2 = Translate(0, .66, -.20) * Scale(1.16, .02, .2);
	drawCube(xuongNgang2, tablePos);
	//xương ngang thứ 3
	mat4 xuongNgang3 = Translate(0, .41, -.2) * Scale(1.16, .02, .2);
	drawCube(xuongNgang3, tablePos);
	//tấm nối xương 1 - 2 
	mat4 tamNoi1_2 = Translate(0, .785, -.2) * Scale(.02, .23, .2);
	drawCube(tamNoi1_2, tablePos);
	//tủ mini
	//hộp tủ sau
	mat4 hopTuMiniSau = Translate(0, .535, -.29) * Scale(.31, .23, .02);
	drawCube(hopTuMiniSau, tablePos);
	//hộp tủ trái
	mat4 hopTuMiniTrai = Translate(-.15, .535, -.2) * Scale(.01, .23, .19);
	drawCube(hopTuMiniTrai, tablePos);
	//hộp tủ phai
	mat4 hopTuMiniPhai = Translate(.15, .535, -.2) * Scale(.01, .23, .19);
	drawCube(hopTuMiniPhai, tablePos);
	//cua tu
	mat4 cuaTuMini = Translate(.155, .535, -.1) * RotateY(value[1]) * Translate(-.165, 0, 0) * Scale(.31, .23, .01);
	drawCube(cuaTuMini, tablePos);
}
#pragma endregion
void table() {
	tablePos = Translate(table_x,table_y,table_z) * RotateY(tableSpin);
	materialColor = RGBtoColor(220, 150, 90);
	reflexColor = RGBtoColor(220, 150, 90);
	mirrorReflexColor = RGBtoColor(220, 150, 90);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	table_ban4chan();
	table_nganKeo();
	table_hopTu();
	table_keSach();
}
//-----------------Bàn học2-------------------------------------------
void table2() {

	color4 materialColor = RGBtoColor(184, 125, 131);
	color4 reflexColor = RGBtoColor(184, 125, 131);
	color4 mirrorReflexColor = RGBtoColor(184, 125, 131);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	tablePos = Translate(3, 0.81, -0.5) * RotateY(-90);

	table_ban4chan();
	table_nganKeo();
	table_keSach();

	table_hopTu();
}
//--------------------kệ tv---------------------------------------------
#pragma region Kệ TV
void keTV_tinh_cube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Scale(a, b, c);
	drawCube(instance, keTVPos);
}
void keTV_dong_cube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Translate(0, 0, keTV_keo) * Scale(a, b, c);
	drawCube(instance, keTVPos);
}
void keTV_keTu() {
	// màu đỏ
	color4 materialColor = RGBtoColor(115, 58, 38);
	color4 reflexColor = RGBtoColor(115, 58, 38);
	color4 mirrorReflexColor = RGBtoColor(115, 58, 38);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//phần kệ dưới
	//mặt trên kệ
	keTV_tinh_cube(0, 0, 0, 2, 0.02, 0.6);
	// hộp tủ sau
	keTV_tinh_cube(0, -0.24, -0.29, 1.96, 0.46, 0.02);
	//hộp tủ trái
	keTV_tinh_cube(-0.99, -0.24, 0, 0.02, 0.46, 0.6);
	//hộp tủ phải
	keTV_tinh_cube(0.99, -0.24, 0, 0.02, 0.46, 0.6);
	//mặt đáy kệ
	keTV_tinh_cube(0, -0.47, 0, 2, 0.02, 0.6);
	//tấm giữa ngang
	keTV_tinh_cube(0, -0.24, 0, 2, 0.02, 0.6);
	// các tấm dọc 
	keTV_tinh_cube(-.40, -.12, .02, .02, .22, .58);
	keTV_tinh_cube(.40, -.12, .02, .02, .22, .58);
	keTV_tinh_cube(-.5, -.36, .02, .02, .22, .58);
	keTV_tinh_cube(0, -.36, .02, .02, .22, .58);
	keTV_tinh_cube(.5, -.36, .02, .02, .22, .58);
}
void keTV_nganKeo() {
	//4 ngăn kéo kệ dưới
	keTV_dong_cube(-.75, -.45, 0, .47, .02, .58);
	keTV_dong_cube(-.25, -.45, 0, .47, .02, .58);
	keTV_dong_cube(.25, -.45, 0, .47, .02, .58);
	keTV_dong_cube(.75, -.45, 0, .47, .02, .58);
	materialColor = RGBtoColor(225, 227, 231);
	reflexColor = RGBtoColor(225, 227, 231);
	mirrorReflexColor = RGBtoColor(225, 227, 231);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//cửa kéo
	keTV_dong_cube(-.75, -.36, .29, .49, .25, .02);
	keTV_dong_cube(-.25, -.36, .29, .49, .25, .02);
	keTV_dong_cube(.25, -.36, .29, .49, .25, .02);
	keTV_dong_cube(.75, -.36, .29, .49, .25, .02);

}
void keTV_tuKinh() {
	color4 materialColor = RGBtoColor(115, 58, 38);
	color4 reflexColor = RGBtoColor(115, 58, 38);
	color4 mirrorReflexColor = RGBtoColor(115, 58, 38);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//xương dọc lớn từ trái sang
	keTV_tinh_cube(-.99, .61, -.15, 0.02, 1.2, 0.3); //1
	keTV_tinh_cube(-.63, .61, -.15, 0.02, 1.2, 0.3); //2
	keTV_tinh_cube(.63, .61, -.15, 0.02, 1.2, 0.3); //3
	keTV_tinh_cube(.99, .61, -.15, 0.02, 1.2, 0.3); //4
	//xương dọc sau tủ trái
	//keTV_tinh_cube(-0.81,0.61,-0.29,0.34,1.2,0.02);
	mat4 xuongDoc5 = Translate(-.81, .61, -.29) * Scale(.34, 1.2, .02);
	drawCube(xuongDoc5, keTVPos);
	//xương dọc sau tủ phải
	mat4 xuongDoc6 = Translate(.81, .61, -.29) * Scale(.34, 1.2, .02);
	drawCube(xuongDoc6, keTVPos);
	//tấm ngang
	keTV_tinh_cube(-.81, 1.22, -.15, .38, 0.02, .3);
	keTV_tinh_cube(.81, 1.22, -.15, .38, 0.02, .3);
	keTV_tinh_cube(-.81, .92, -.15, .38, 0.02, .28);
	keTV_tinh_cube(.81, .92, -.15, .38, 0.02, .28);
	keTV_tinh_cube(-.81, .62, -.15, .38, 0.02, .28);
	keTV_tinh_cube(.81, .62, -.15, .38, 0.02, .28);
	keTV_tinh_cube(-.81, .32, -.15, .38, 0.02, .28);
	keTV_tinh_cube(.81, .32, -.15, .38, 0.02, .28);
	//tam ngang giua
	mat4 tamNgangGiua = Translate(0, 1.1, -.15) * Scale(1.28, .02, .2);
	drawCube(tamNgangGiua, keTVPos);
}
#pragma endregion

void veTV() {
	color4 materialColor = RGBtoColor(125, 125, 125);
	color4 reflexColor = RGBtoColor(125, 125, 125);
	color4 mirrorReflexColor = RGBtoColor(125, 125, 125);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 chande1 = Translate(0, 0.02, 0) * Scale(0.1, 0.01, 0.1);
	drawCube(chande1, keTVPos);

	mat4 chande2 = Translate(0, 0.16, 0) * Scale(0.02, 0.3, 0.02);
	drawCube(chande2, keTVPos);

	materialColor = RGBtoColor(0, 0, 0);
	reflexColor = RGBtoColor(0, 0, 0);
	mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 manHinhPC = Translate(0, 0.35, 0.01) * Scale(0.7, 0.5, 0.02);
	drawCube(manHinhPC, keTVPos);


}
void keTV() {
	keTVPos =Translate(keTV_x,keTV_y,keTV_z)*RotateY(keTV_xoay);

	keTV_keTu();
	keTV_nganKeo();
	keTV_tuKinh();
	veTV();
}
//--------------------tủ cao ---------------------------------------------
#pragma region Tủ cao
void tuCao_phanTinh() {
	color4 materialColor = RGBtoColor(255, 255, 172);
	color4 reflexColor = RGBtoColor(255, 255, 172);
	color4 mirrorReflexColor = RGBtoColor(255, 255, 172);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//hộp tủ sau
	mat4 tuCao_hopTuSau = Translate(0, 0, -.175) * Scale(0.4, 2, .02);
	drawCube(tuCao_hopTuSau, tuCaoPos);
	//hộp tủ trái
	mat4 tuCao_hopTuTrai = Translate(-.19, 0, 0) * Scale(.02, 2, .35);
	drawCube(tuCao_hopTuTrai, tuCaoPos);
	//hộp tủ phải
	mat4 tuCao_hopTuPhai = Translate(.19, 0, 0) * Scale(.02, 2, .35);
	drawCube(tuCao_hopTuPhai, tuCaoPos);
	//mặt trên
	mat4 tuCao_matTren = Translate(0, .99, 0) * Scale(.36, .02, .35);
	drawCube(tuCao_matTren, tuCaoPos);
	//mặt đáy
	mat4 tuCao_matDay = Translate(0, -.99, 0) * Scale(.36, .02, .35);
	drawCube(tuCao_matDay, tuCaoPos);

	materialColor = RGBtoColor(255, 225, 172);
	reflexColor = RGBtoColor(255, 225, 172);
	mirrorReflexColor = RGBtoColor(255, 225, 172);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//tấm ngang
	mat4 tuCao_tamNgang1 = Translate(0, -.3, 0) * Scale(.36, .02, .35);
	drawCube(tuCao_tamNgang1, tuCaoPos);
	//tấm ngang
	mat4 tuCao_tamNgang2 = Translate(0, -.65, 0) * Scale(.36, .02, .35);
	drawCube(tuCao_tamNgang2, tuCaoPos);
}
void tuCao_cubeAct(float x, float y, float z, float a, float b, float c,float t) {
	mat4 instance = Translate(x,y,z) * Translate(0, 0,  t) * Scale(a,b,c);
	drawCube(instance, tuCaoPos);
}
void tuCao_phanDong() {
	//ngăn kéo
	tuCao_cubeAct(0, -0.63, 0, 0.36, 0.02, 0.35,tuCao_keo);
	tuCao_cubeAct(0, -0.97, 0, 0.36, 0.02, 0.35,tuCao_keo2);
	//cửa kéo
	tuCao_cubeAct(0, -.48, .18, .36, .33, .02,tuCao_keo);
	tuCao_cubeAct(0, -.82, .18, .36, .33, .02,tuCao_keo2);
	//hộp ngăn kéo
	//trên
	tuCao_cubeAct(-.18, -.55, 0, .01, .2, .35,tuCao_keo);
	tuCao_cubeAct(.18, -.55, 0, .01, .2, .35,tuCao_keo);
	//dưới
	tuCao_cubeAct(-.18, -.89, 0, .01, .2, .35,tuCao_keo2);
	tuCao_cubeAct(.18, -.89, 0, .01, .2, .35,tuCao_keo2);
	//cửa tủ
	mat4 tuCao_cuaTu = Translate(.2, .35, .18) * RotateY(tuCao_moCua) * Translate(-.2, 0, 0) * Scale(.4, 1.3, .02);
	drawCube(tuCao_cuaTu, tuCaoPos);
}
void tuCaoDon() {
	tuCaoPos = Translate(tuCao_x, tuCao_y, tuCao_z) * RotateY(tuCaoSpin);

	color4 materialColor = RGBtoColor(96, 133, 59);
	color4 reflexColor = RGBtoColor(96, 133, 59);
	color4 mirrorReflexColor = RGBtoColor(96, 133, 59);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	tuCao_phanTinh();

	materialColor = RGBtoColor(35, 92, 121);
	reflexColor = RGBtoColor(35, 92, 121);
	mirrorReflexColor = RGBtoColor(35, 92, 121);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	tuCao_phanDong();
}
//-----------------------tủ cao 2----------------------------------------
void tuCaoDon2() {
	tuCaoPos = Translate(3.2, 1, 3.5) * RotateY(-90);

	color4 materialColor = RGBtoColor(176, 173, 166);
	color4 reflexColor = RGBtoColor(176, 173, 166);
	color4 mirrorReflexColor = RGBtoColor(176, 173, 166);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	tuCao_phanTinh();

	materialColor = RGBtoColor(137, 11, 11);
	reflexColor = RGBtoColor(137, 11, 11);
	mirrorReflexColor = RGBtoColor(137, 11, 11);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	tuCao_phanDong();
}
#pragma endregion


//-----------------------tủ treo------------------------------------
#pragma region Tủ treo
void tuTreo_phanTinh()
{
	// màu tủ
	color4 materialColor = RGBtoColor(193, 100, 56);
	color4 reflexColor = RGBtoColor(193, 100, 56);
	color4 mirrorReflexColor = RGBtoColor(193, 100, 56);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//hộp tủ bên phải
	mat4 tuTreo_hopTuTrai = Translate(-.35, .4, 0) * Scale(.01, .8, .4);
	drawCube(tuTreo_hopTuTrai, tuTreoPos);
	//hộp tủ bên trái
	mat4 tuTreo_hopTuPhai = Translate(.35, .4, 0) * Scale(.01, .8, .4);
	drawCube(tuTreo_hopTuPhai, tuTreoPos);
	//hộp tủ mặt đáy
	mat4 tuTreo_hopDay = Scale(.7, .01, .4);
	drawCube(tuTreo_hopDay, tuTreoPos);
	//hộp tủ mặt trên
	mat4 tuTreo_hopTren = Translate(0, .8, 0) * Scale(.7, .01, .4);
	drawCube(tuTreo_hopTren, tuTreoPos);

	//hộp tủ phía sau
	mat4 tuTreo_hopTuSau = Translate(0, .4, -.2) * Scale(.7, .8, .01);
	drawCube(tuTreo_hopTuSau, tuTreoPos);

	materialColor = RGBtoColor(199, 189, 181);
	reflexColor = RGBtoColor(199, 189, 181);
	mirrorReflexColor = RGBtoColor(199, 189, 181);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//tấm ngăn ngang
	mat4 tuTreo_tamNoiNgang = Translate(0, .5, 0) * Scale(.69, .01, .39);
	drawCube(tuTreo_tamNoiNgang, tuTreoPos);
	//tấm ngăn dọc
	mat4 tuTreo_tamNoiDoc = Translate(0, .25, -.045) * Scale(.01, .5, .3);
	drawCube(tuTreo_tamNoiDoc, tuTreoPos);
}
void tuTreo_phanDong() {
	//cửa mở trái
	mat4 tuTreo_cuaTrai = Translate(-.35, .25, 0.2) * RotateY(-value[1]) * Translate(.17, 0, 0) * Scale(.35, .5, .01);
	drawCube(tuTreo_cuaTrai, tuTreoPos);
	//cửa mở phải
	mat4 tuTreo_cuaPhai = Translate(.35, .25, 0.2) * RotateY(value[1]) * Translate(-.17, 0, 0) * Scale(.35, .5, .01);
	drawCube(tuTreo_cuaPhai, tuTreoPos);
	//cửa lật lên trên
	mat4 tuTreo_cuaLat = Translate(0, .8, 0.2) * RotateX(-value[1]) * Translate(0, -.15, 0) * Scale(.69, .3, .01);
	drawCube(tuTreo_cuaLat, tuTreoPos);
}
void tuTreo() {
	// cao 80 rộng 70 sâu 40


	tuTreoPos = Translate(2.5, 1, -4.5);
	tuTreo_phanTinh();
	tuTreo_phanDong();
}
#pragma endregion


void tuTreo2() {
	// cao 80 rộng 70 sâu 40


	tuTreoPos = Translate(-2.5, 1, -4.5);
	tuTreo_phanTinh();
	tuTreo_phanDong();
}

//-------------------------tủ quần áo--------------------------------
#pragma region Tủ quần áo
void tuQuanAo_phanTinh() {
	// màu tủ
	color4 materialColor = RGBtoColor(142, 84, 23);
	color4 reflexColor = RGBtoColor(142, 84, 23);
	color4 mirrorReflexColor = RGBtoColor(142, 84, 23);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//hộp tủ bên trái
	mat4 tuQuanAo_hopTrai = Translate(-.595, 1.025, 0) * Scale(.01, 1.94, .5);
	drawCube(tuQuanAo_hopTrai, tuQuanAoPos);
	//hộp tủ bên phải
	mat4 tuQuanAo_hopPhai = Translate(.595, 1.025, 0) * Scale(.01, 1.94, .5);
	drawCube(tuQuanAo_hopPhai, tuQuanAoPos);
	//tấm ngăn giữa 
	mat4 tuQuanAo_tamGiua = Translate(-.2, 1.025, 0) * Scale(.01, 1.94, .5);
	drawCube(tuQuanAo_tamGiua, tuQuanAoPos);
	//hộp đáy tủ
	mat4 tuQuanAo_dayTu = Translate(0, .03, 0) * Scale(1.2, .05, .5);
	drawCube(tuQuanAo_dayTu, tuQuanAoPos);
	//nóc
	mat4 tuQuanAo_nocTu = Translate(0, 1.99, 0) * Scale(1.2, .01, .5);
	drawCube(tuQuanAo_nocTu, tuQuanAoPos);
	//hộp tủ phía sau
	mat4 tuQuanAo_matSau = Translate(0, 1.025, -.25) * Scale(1.18, 1.94, .01);
	drawCube(tuQuanAo_matSau, tuQuanAoPos);
	//tấm ngang nóc dài
	mat4 tuQuanAo_tamNgang = Translate(0, 1.65, 0) * Scale(1.18, .01, .5);
	drawCube(tuQuanAo_tamNgang, tuQuanAoPos);
	//các tấm ngang hộp tủ trái
	//màu thanh ngang
	materialColor = RGBtoColor(199, 189, 181);
	reflexColor = RGBtoColor(199, 189, 181);
	mirrorReflexColor = RGBtoColor(199, 189, 181);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 tuQuanAo_tamNgang1 = Translate(-.4, .43, 0) * Scale(.4, .01, .5);
	drawCube(tuQuanAo_tamNgang1, tuQuanAoPos);

	mat4 tuQuanAo_tamNgang2 = Translate(-.4, .83, 0) * Scale(.4, .01, .5);
	drawCube(tuQuanAo_tamNgang2, tuQuanAoPos);

	mat4 tuQuanAo_tamNgang3 = Translate(-.4, 1.23, 0) * Scale(.4, .01, .5);
	drawCube(tuQuanAo_tamNgang3, tuQuanAoPos);
	//đòn treo quần áo
	mat4 tuQuanAo_macTreo = Translate(.2, 1.6, 0) * Scale(.8, .01, .01);
	drawCylinder(tuQuanAo_macTreo, tuQuanAoPos);

}
void tuQuanAo_phanDong() {
	//cánh cửa hộp tủ trái
	mat4 tuQuanAo_cuaHopTrai = Translate(-.6, 1.025, .25) * RotateY(-tuQuanAo_moCua) * Translate(0.2, 0, 0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaHopTrai, tuQuanAoPos);
	//cánh tủ chính bên trái
	mat4 tuQuanAo_cuaTrai = Translate(-.2, 1.025, .25) * RotateY(-tuQuanAo_moCua) * Translate(.2, 0, 0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaTrai, tuQuanAoPos);
	//cánh tủ chính bên phải
	mat4 tuQuanAo_cuaPhai = Translate(.595, 1.025, .25) * RotateY(tuQuanAo_moCua) * Translate(-.2, 0, 0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaPhai, tuQuanAoPos);
}
void tuQuanAo() {
	tuQuanAoPos = Translate(tuQuanAo_x,tuQuanAo_y,tuQuanAo_z) * RotateY(tuQuanAoSpin);

	tuQuanAo_phanTinh();
	tuQuanAo_phanDong();
}
#pragma endregion

//--------------------- Vẽ bàn chữ Z---------------------------
#pragma region Bàn chữ Z
void BanchuZ_matban(float x, float y, float z) {
	// màu vang
	color4 materialColor = RGBtoColor(255, 11, 11);
	color4 reflexColor = RGBtoColor(255, 11, 11);
	color4 mirrorReflexColor = RGBtoColor(255, 11, 11);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_matban = Translate(x, y, z) * Scale(1.2, 0.02, 0.65);
	drawCube(banChuZ_matban, banChuZPos);
}
void BanChuZ_matdoc(float x, float y, float z) {
	color4 materialColor = RGBtoColor(255, 0, 0);
	color4 reflexColor = RGBtoColor(255, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(255, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_matdoc = Translate(x, y, z) * Scale(1.2, .2, 0.02);
	drawCube(banChuZ_matdoc, banChuZPos);

}
void BanChuZ_chanban(GLfloat transX, GLfloat transY, GLfloat transZ) {
	//màu đen
	color4 materialColor = RGBtoColor(10, 10, 10);
	color4 reflexColor = RGBtoColor(30, 30, 30);
	color4 mirrorReflexColor = RGBtoColor(30, 30, 30);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_chanban = Translate(transX, transY, transZ) * Scale(0.06, 0.06, 0.5);
	drawCube(banChuZ_chanban, banChuZPos);

}
void BanChuZ_chancheo(GLfloat transX, GLfloat transY, GLfloat transZ) {
	//màu đen
	color4 materialColor = RGBtoColor(10, 10, 10);
	color4 reflexColor = RGBtoColor(30, 30, 30);
	color4 mirrorReflexColor = RGBtoColor(30, 30, 30);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_chanban = Translate(transX, transY, transZ) * RotateX(58) * Scale(0.05, 0.05, 0.85);
	drawCube(banChuZ_chanban, banChuZPos);

}
void BanChuZ() {
	banChuZPos = Translate(3, 0, -2) * RotateY(-90);
	BanchuZ_matban(0, 0.8, 0);
	BanChuZ_matdoc(0, 0.7, -0.3);
	BanChuZ_chanban(-0.52, 0.77, 0);
	BanChuZ_chanban(0.52, 0.77, 0);

	BanChuZ_chancheo(-0.52, 0.4, 0);
	BanChuZ_chancheo(0.52, 0.4, 0);

	BanChuZ_chanban(-0.52, 0.03, 0);
	BanChuZ_chanban(0.52, 0.03, 0);



}
#pragma endregion

//--------------------------Vẽ bàn tròn---------------------------
#pragma region Bàn tròn
void BanTron_matban(float R, float G, float B) {
	// màu đỏ
	color4 materialColor = RGBtoColor(R, G, B);
	color4 reflexColor = RGBtoColor(R, G, B);
	color4 mirrorReflexColor = RGBtoColor(R, G, B);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banTron_matban = Translate(0, 0.8, 0) * Scale(1.2, 0.1, 1.2);
	drawCylinder(banTron_matban, banTronPos);

}
void BanTron_chanban(float R, float G, float B) {
	// màu đen
	color4 materialColor = RGBtoColor(R, G, B);
	color4 reflexColor = RGBtoColor(R, G, B);
	color4 mirrorReflexColor = RGBtoColor(R, G, B);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banTron_chanban = Translate(0, 0.4, 0) * Scale(0.15, 0.7, 0.15);
	drawCylinder(banTron_chanban, banTronPos);

	mat4 banTron_chandayban = Translate(0, 0.1, 0) * RotateY(22.5) * Scale(0.5, 0.05, 0.5);
	drawCylinder(banTron_chandayban, banTronPos);
}
void banTron_gheBanTron(float x, float y, float z, float R, float G, float B) {
	color4 materialColor = RGBtoColor(R, G, B);
	color4 reflexColor = RGBtoColor(R, G, B);
	color4 mirrorReflexColor = RGBtoColor(R, G, B);

	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 gheBanTron = Translate(x, y, z) * Scale(0.25, 0.5, 0.25);
	drawCylinder(gheBanTron, banTronPos);
}

void BanTron() {
	banTronPos = Translate(1, 0, -1);
	BanTron_matban(200, 50, 11);
	BanTron_chanban(40, 43, 42);

	banTron_gheBanTron(-1, 0.25, 0, 220, 30, 166);
	banTron_gheBanTron(1, 0.25, 0, 220, 30, 166);
	banTron_gheBanTron(0, 0.25, -1, 220, 30, 166);
	banTron_gheBanTron(0, 0.25, 1, 220, 30, 166);
}
#pragma endregion


void BanTron2() {
	banTronPos = Translate(1, 0, 2);
	BanTron_matban(205, 151, 65);
	BanTron_chanban(63, 56, 58);

	banTron_gheBanTron(-1, 0.25, 0, 78, 102, 49);
	banTron_gheBanTron(1, 0.25, 0, 78, 102, 49);
	banTron_gheBanTron(0, 0.25, -1, 78, 102, 49);
	banTron_gheBanTron(0, 0.25, 1, 78, 102, 49);

}
//---------------------quầy lễ tân----------------------

#pragma region Quầy lễ tân
void theLeTan(GLfloat x, GLfloat z) {
	color4 materialColor = RGBtoColor(0, 0, 0);
	color4 reflexColor = RGBtoColor(0, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 theLetan1 = Translate(x, 0.02, z) * Scale(0.3, 0.08, 0.02);
	drawCube(theLetan1, quayLeTanPos);

	materialColor = RGBtoColor(255, 255, 51);
	reflexColor = RGBtoColor(255, 255, 51);
	mirrorReflexColor = RGBtoColor(255, 255, 51);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 theLetan2 = Translate(x, 0.07, z) * Scale(0.28, 0.1, 0.01);
	drawCube(theLetan2, quayLeTanPos);
}
void BanLeTan() {
	// màu đỏ
	color4 materialColor = RGBtoColor(114, 147, 76);
	color4 reflexColor = RGBtoColor(114, 147, 76);
	color4 mirrorReflexColor = RGBtoColor(114, 147, 76);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 matban1 = Scale(2, 0.02, 0.3);
	drawCube(matban1, quayLeTanPos);

	mat4 matban2 = Translate(1.15, 0, 0.35) * Scale(0.3, 0.02, 1);
	drawCube(matban2, quayLeTanPos);


	materialColor = RGBtoColor(203, 186, 170);
	reflexColor = RGBtoColor(203, 186, 170);
	mirrorReflexColor = RGBtoColor(203, 186, 170);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 chan1 = Translate(-1 + 0.06 / 2, -0.6, 0) * Scale(.06, 1.2, .3);
	drawCube(chan1, quayLeTanPos);

	mat4 chan2 = Translate(1 - 0.06 / 2 + 0.3, -0.6, 0.35) * Scale(.06, 1.2, 1);
	drawCube(chan2, quayLeTanPos);

	mat4 chan3 = Translate(0.15, -0.6, -0.15 + 0.1 / 2) * Scale(2 + .3, 1.2, .1);
	drawCube(chan3, quayLeTanPos);

	mat4 chan4 = Translate(1.15, -0.6, 1 - 0.18) * Scale(.3, 1.2, .06);
	drawCube(chan4, quayLeTanPos);
}

void mayTinh() {
	// màu đỏ
	color4 materialColor = RGBtoColor(125, 125, 125);
	color4 reflexColor = RGBtoColor(125, 125, 125);
	color4 mirrorReflexColor = RGBtoColor(125, 125, 125);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 chande1 = Translate(0, 0.02, 0) * Scale(0.1, 0.01, 0.1);
	drawCube(chande1, quayLeTanPos);

	mat4 chande2 = Translate(0, 0.15, 0) * Scale(0.02, 0.3, 0.02);
	drawCube(chande2, quayLeTanPos);

	materialColor = RGBtoColor(0, 0, 0);
	reflexColor = RGBtoColor(0, 0, 0);
	mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 manHinhPC = Translate(0, 0.3, 0.01) * Scale(0.4, 0.3, 0.02);
	drawCube(manHinhPC, quayLeTanPos);


}
void QuayLeTan() {
	quayLeTanPos = Translate(-2.6, 1.2, 3) * RotateY(-90);

	theLeTan(0.7, 0);
	BanLeTan();
	mayTinh();
}
#pragma endregion


//Vẽ đồng hồ
#pragma region Đồng hồ
mat4 dongHoPos;
void veDongHo() {
	color4 materialColor = RGBtoColor(0, 0, 0);
	color4 reflexColor = RGBtoColor(0, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 khungDongHo = Scale(1.1, 0.01, 1.1);
	drawCylinder(khungDongHo, dongHoPos);

	materialColor = RGBtoColor(255, 255, 255);
	reflexColor = RGBtoColor(255, 255, 255);
	mirrorReflexColor = RGBtoColor(255, 255, 255);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 100);
	mat4 matDongHo = Scale(1, 0.02, 1);
	drawCylinder(matDongHo, dongHoPos);

	materialColor = RGBtoColor(210, 0, 0);
	reflexColor = RGBtoColor(210, 0, 0);
	mirrorReflexColor = RGBtoColor(210, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 kimGio = Translate(0, 0.02, 0.1) * Scale(0.02, 0.02, 0.2);
	drawCube(kimGio, dongHoPos);

	mat4 kimPhut = RotateY(90) * Translate(0, 0.02, 0.15) * Scale(0.02, 0.02, 0.3);
	drawCube(kimPhut, dongHoPos);

	materialColor = RGBtoColor(10, 0, 0);
	reflexColor = RGBtoColor(10, 0, 0);
	mirrorReflexColor = RGBtoColor(10, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 kimGiay = RotateY(120) * Translate(0, 0.02, 0.18) * Scale(0.02, 0.02, 0.36);
	drawCube(kimGiay, dongHoPos);
}

void DongHo() {
	dongHoPos = Translate(0, 3.5, -4.9) * RotateX(90) * Scale(0.7, 0.7, 0.7);
	veDongHo();
}

#pragma endregion

//----------------------- Vẽ khung tranh---------------------
#pragma region Tranh trang trí
mat4 khungTranhPos;
void khungTranh() {

	mat4 khungTranh_canhTren = Scale(0.3, 0.04, 0.04);
	drawCube(khungTranh_canhTren, khungTranhPos);

	mat4 khungTranh_canhDuoi = Translate(0, 0, 0.5) * Scale(0.3, 0.04, 0.04);
	drawCube(khungTranh_canhDuoi, khungTranhPos);

	mat4 khungTranh_canhPhai = Translate(0.13, 0, 0.25) * Scale(0.04, 0.04, 0.5);
	drawCube(khungTranh_canhPhai, khungTranhPos);

	mat4 khungTranh_canhTrai = Translate(-0.13, 0, 0.25) * Scale(0.04, 0.04, 0.5);
	drawCube(khungTranh_canhTrai, khungTranhPos);
}

void ndTranh() {

	mat4 ndTranh = Translate(0, 0.01, 0.25) * Scale(0.26, 0.02, 0.46);
	drawCube(ndTranh, khungTranhPos);

}

void Tranh1() {

	khungTranhPos = Translate(3.3, 2.8, 0) * RotateY(90) * RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();

	materialColor = RGBtoColor(255, 255, 255);
	reflexColor = RGBtoColor(255, 255, 255);
	mirrorReflexColor = RGBtoColor(255, 255, 255);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}

void Tranh2() {

	khungTranhPos = Translate(3.3, 2.8, 2) * RotateY(90) * RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();

	materialColor = RGBtoColor(97, 166, 199);
	reflexColor = RGBtoColor(97, 166, 199);
	mirrorReflexColor = RGBtoColor(97, 166, 199);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}

void Tranh3() {

	khungTranhPos = Translate(3.3, 2.8, -2) * RotateY(90) * RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();
	materialColor = RGBtoColor(82, 115, 14);
	reflexColor = RGBtoColor(82, 115, 14);
	mirrorReflexColor = RGBtoColor(82, 115, 14);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}

void Tranh4() {

	khungTranhPos = Translate(-3.3, 2.8, 2) * RotateY(90) * RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();
	materialColor = RGBtoColor(82, 115, 14);
	reflexColor = RGBtoColor(82, 115, 14);
	mirrorReflexColor = RGBtoColor(82, 115, 14);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}

void Tranh5() {

	khungTranhPos = Translate(-3.3, 2.8, 0) * RotateY(90) * RotateX(90);
	//khungTranhPos =  RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();

	materialColor = RGBtoColor(97, 166, 199);
	reflexColor = RGBtoColor(97, 166, 199);
	mirrorReflexColor = RGBtoColor(97, 166, 199);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}

void Tranh6() {

	khungTranhPos = Translate(-3.3, 2.8, -2) * RotateY(90) * RotateX(90);
	color4 materialColor = RGBtoColor(156, 91, 46);
	color4 reflexColor = RGBtoColor(156, 91, 46);
	color4 mirrorReflexColor = RGBtoColor(156, 91, 46);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	khungTranh();

	materialColor = RGBtoColor(255, 255, 255);
	reflexColor = RGBtoColor(255, 255, 255);
	mirrorReflexColor = RGBtoColor(255, 255, 255);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	ndTranh();
}
#pragma endregion


//-------------------- Vẽ đèn treo tường--------------------
#pragma region Đèn treo tường
mat4 denTuongPos;
void initDenTuong() {

	color4 materialColor = RGBtoColor(10, 0, 0);
	color4 reflexColor = RGBtoColor(10, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(10, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 chanDe = Scale(0.2, 0.04, 0.2);
	drawCylinder(chanDe, denTuongPos);

	mat4 truDen1 = Translate(0, 0.15, 0) * Scale(0.04, 0.3, 0.04);
	drawCylinder(truDen1, denTuongPos);

	mat4 truDen2 = Translate(0.04, 0.32, 0) * RotateZ(90) * Scale(0.04, 0.14, 0.04);
	drawCylinder(truDen2, denTuongPos);

	mat4 deDen = Translate(0.105, 0.31, 0) * RotateZ(90) * Scale(0.1, 0.01, 0.1);
	drawCylinder(deDen, denTuongPos);

	if (batDen) {
		materialColor = RGBtoColor(255, 255, 51);
		reflexColor = RGBtoColor(255, 255, 100);
		mirrorReflexColor = RGBtoColor(255, 255,100);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 50);
	}
	else {
		materialColor = RGBtoColor(100, 100, 51);
		reflexColor = RGBtoColor(100, 100, 51);
		mirrorReflexColor = RGBtoColor(100, 100, 51);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	}

	mat4 den = Translate(0.205, 0.31, 0) * RotateZ(90) * Scale(0.15, 0.2, 0.15);
	drawCylinder(den, denTuongPos);
}

void DenTuong1() {
	denTuongPos = Translate(3.43, 3.2, 0.2) * RotateZ(90);
	initDenTuong();
}
void DenTuong2() {
	denTuongPos = Translate(3.43, 3.2, 2.2) * RotateZ(90);
	initDenTuong();
}
void DenTuong3() {
	denTuongPos = Translate(3.43, 3.2, -2.2) * RotateZ(90);
	initDenTuong();
}
void DenTuong4() {
	denTuongPos = Translate(-3.43, 3.2, 0.2) * RotateY(180) * RotateZ(90);
	initDenTuong();
}
void DenTuong5() {
	denTuongPos = Translate(-3.43, 3.2, 2.2) * RotateY(180) * RotateZ(90);
	initDenTuong();
}
void DenTuong6() {
	denTuongPos = Translate(-3.43, 3.2, -2.2) * RotateY(180) * RotateZ(90);
	initDenTuong();
}
#pragma endregion
//-------------------vẽ quạt trần-------------------
#pragma region Quạt trần
mat4 quatTranPos, quatTranAct;
void quatTran_canhQuat(float x, float y, float z, float k) {
	mat4 canhquat = RotateY(k) * Translate(x, y, z) * Scale(0.15, 0.02, 0.7);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * quatTranPos * quatTranAct * canhquat);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}
void quatTran_khung() {
	mat4 khungTreo = Translate(0, -0.25, 0) * Scale(0.03, 0.5, 0.03);
	drawCylinder(khungTreo, quatTranPos);
	mat4 trucXoay = Translate(0, -0.5, 0) * Scale(0.2, 0.05, 0.2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * quatTranPos * quatTranAct * trucXoay);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}
void quatTran() {
	color4 materialColor = RGBtoColor(50, 240, 50);
	color4 reflexColor = RGBtoColor(50, 240, 50);
	color4 mirrorReflexColor = RGBtoColor(50, 240, 50);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 150);
	quatTranPos = Translate(0, 4, 0);
	quatTranAct = RotateY(quatTranSpin);
	quatTran_khung();
	quatTran_canhQuat(0, -0.5, 0.35, 0);
	quatTran_canhQuat(0, -0.5, 0.35, 120);
	quatTran_canhQuat(0, -0.5, 0.35, 240);
}
#pragma endregion


//------------------------bộ ghế sofa--------------------
#pragma region Bộ sofa
mat4 sofa_banPos;

void sofa_cube(float x, float y, float z, float a, float b, float c) {
	mat4 sofaCube = Translate(x, y, z) * Scale(a, b, c);
	drawCube(sofaCube, sofa_banPos);
}
void sofa_cylinder(float x, float y, float z, float a, float b, float c) {
	mat4 sofaCylinder = Translate(x, y, z) * Scale(a, b, c);
	drawCylinder(sofaCylinder, sofa_banPos);
}
void sofa_ban() {
	//mặt bàn 1

	color4 materialColor = RGBtoColor(54, 56, 55);
	color4 reflexColor = RGBtoColor(54, 56, 55);
	color4 mirrorReflexColor = RGBtoColor(54, 56, 55);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	sofa_cube(0, 0.45, 0, 1.3, 0.05, 0.85);

	materialColor = RGBtoColor(249, 243, 234);
	reflexColor = RGBtoColor(249, 243, 234);
	mirrorReflexColor = RGBtoColor(249, 243, 234);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//mặt bàn 2
	sofa_cube(0, 0.4, 0, 1.2, 0.05, 0.8);

	//ngan ban
	sofa_cube(0, 0.1, 0, 1.17, 0.02, 0.77);

	materialColor = RGBtoColor(116, 75, 35);
	reflexColor = RGBtoColor(116, 75, 35);
	mirrorReflexColor = RGBtoColor(116, 75, 35);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//chân 1
	sofa_cylinder(-.57, 0.2, -.37, 0.06, 0.4, 0.06);
	//chân 2
	sofa_cylinder(.57, 0.2, -.37, 0.06, 0.4, 0.06);
	//chân 3
	sofa_cylinder(-.57, 0.2, .37, 0.06, 0.4, 0.06);
	//chân 4
	sofa_cylinder(.57, 0.2, .37, 0.06, 0.4, 0.06);
}
mat4 sofa_gheDaiPos;
void sofa_gheDai_cube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Scale(a, b, c);
	drawCube(instance, sofa_gheDaiPos);
}
void sofa_gheDai() {
	color4 materialColor = RGBtoColor(116, 75, 35);
	color4 reflexColor = RGBtoColor(116, 75, 35);
	color4 mirrorReflexColor = RGBtoColor(116, 75, 35);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//tấm lớn
	sofa_gheDai_cube(0, 0.15, 0, 2.6, 0.02, 0.6);
	//tấm lớn đặt lưng
	sofa_gheDai_cube(0, 0.46, -0.325, 2.4, 0.6, 0.05);
	//tấm dài chắn trước
	sofa_gheDai_cube(0, 0.11, 0.325, 2.4, 0.1, 0.05);

	materialColor = RGBtoColor(239, 222, 206);
	reflexColor = RGBtoColor(239, 222, 206);
	mirrorReflexColor = RGBtoColor(239, 222, 206);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//--trái
	//chân 1
	sofa_gheDai_cube(-1.25, 0.25, -0.325, 0.1, 0.5, 0.05);
	//chân 2
	sofa_gheDai_cube(-1.25, 0.25, 0.325, 0.1, 0.5, 0.05);
	//thanh ngang tì tay
	sofa_gheDai_cube(-1.25, 0.525, 0, 0.1, 0.05, 0.7);
	//thanh dọc nhỏ 1
	sofa_gheDai_cube(-1.25, 0.33, -0.13, 0.03, 0.34, 0.07);
	//thanh dọc nhỏ 2
	sofa_gheDai_cube(-1.25, 0.33, 0.13, 0.03, 0.34, 0.07);
	//--phải
	//chân 3
	sofa_gheDai_cube(1.25, 0.25, -0.325, 0.1, 0.5, 0.05);
	//chân 4
	sofa_gheDai_cube(1.25, 0.25, 0.325, 0.1, 0.5, 0.05);
	//thanh ngang tì tay
	sofa_gheDai_cube(1.25, 0.525, 0, 0.1, 0.05, 0.7);
	//thanh dọc nhỏ 1
	sofa_gheDai_cube(1.25, 0.33, -0.13, 0.03, 0.34, 0.07);
	//thanh dọc nhỏ 2
	sofa_gheDai_cube(1.25, 0.33, 0.13, 0.03, 0.34, 0.07);

	materialColor = RGBtoColor(198, 160, 126);
	reflexColor = RGBtoColor(198, 160, 126);
	mirrorReflexColor = RGBtoColor(198, 160, 126);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//đệm nằm
	sofa_gheDai_cube(0, 0.21, 0.035, 2.4, 0.1, 0.66);
	//đệm tựa
	sofa_gheDai_cube(0, 0.56, -0.25, 2.4, 0.6, 0.1);
	//gối tựa 
	materialColor = RGBtoColor(150, 80, 150);
	reflexColor = RGBtoColor(150, 80, 150);
	mirrorReflexColor = RGBtoColor(150, 80, 150);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 goiTua1 = Translate(-0.7, 0.5, -0.13) * RotateX(80) * RotateZ(10) * Scale(0.5, 0.1, 0.5);
	drawCylinder(goiTua1, sofa_gheDaiPos);
	mat4 goiTua2 = Translate(0, 0.5, -0.13) * RotateX(80) * RotateZ(-10) * Scale(0.5, 0.1, 0.5);
	drawCylinder(goiTua2, sofa_gheDaiPos);
	mat4 goiTua3 = Translate(0.7, 0.5, -0.13) * RotateX(80) * Scale(0.5, 0.1, 0.5);
	drawCylinder(goiTua3, sofa_gheDaiPos);
}
mat4 sofa_gheDonPos;
void sofa_gheDon_cube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Scale(a, b, c);
	drawCube(instance, sofa_gheDonPos);
}
void sofa_gheDon() {
	color4 materialColor = RGBtoColor(116, 75, 35);
	color4 reflexColor = RGBtoColor(116, 75, 35);
	color4 mirrorReflexColor = RGBtoColor(116, 75, 35);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	//tấm lớn
	sofa_gheDon_cube(0, 0.15, 0, 0.9, 0.02, 0.6);
	//tấm lớn đặt lưng
	sofa_gheDon_cube(0, 0.46, -0.325, 0.8, 0.6, 0.05);
	//tấm dài chắn trước
	sofa_gheDon_cube(0, 0.11, 0.325, 0.8, 0.1, 0.05);

	materialColor = RGBtoColor(239, 222, 206);
	reflexColor = RGBtoColor(239, 222, 206);
	mirrorReflexColor = RGBtoColor(239, 222, 206);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//chân 1
	sofa_gheDon_cube(-0.45, 0.25, -0.325, 0.1, 0.5, 0.05);
	//chân 2
	sofa_gheDon_cube(-0.45, 0.25, 0.325, 0.1, 0.5, 0.05);
	//chân 3
	sofa_gheDon_cube(0.45, 0.25, -0.325, 0.1, 0.5, 0.05);
	//chân 4
	sofa_gheDon_cube(0.45, 0.25, 0.325, 0.1, 0.5, 0.05);
	//--trái
	//thanh ngang tì tay
	sofa_gheDon_cube(-0.45, 0.525, 0, 0.1, 0.05, 0.7);
	//thanh dọc nhỏ 1
	sofa_gheDon_cube(-0.45, 0.33, -0.13, 0.03, 0.34, 0.07);
	//thanh dọc nhỏ 2
	sofa_gheDon_cube(-0.45, 0.33, 0.13, 0.03, 0.34, 0.07);
	//--phải
	//thanh ngang tì tay
	sofa_gheDon_cube(0.45, 0.525, 0, 0.1, 0.05, 0.7);
	//thanh dọc nhỏ 1
	sofa_gheDon_cube(0.45, 0.33, -0.13, 0.03, 0.34, 0.07);
	//thanh dọc nhỏ 2
	sofa_gheDon_cube(0.45, 0.33, 0.13, 0.03, 0.34, 0.07);

	//đệm nằm
	materialColor = RGBtoColor(198, 160, 126);
	reflexColor = RGBtoColor(198, 160, 126);
	mirrorReflexColor = RGBtoColor(198, 160, 126);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	sofa_gheDon_cube(0, 0.21, 0.035, 0.8, 0.1, 0.66);
	//đệm tựa
	sofa_gheDon_cube(0, 0.56, -0.25, 0.8, 0.6, 0.1);
	//gối tựa
	materialColor = RGBtoColor(150, 80, 150);
	reflexColor = RGBtoColor(150, 80, 150);
	mirrorReflexColor = RGBtoColor(150, 80, 150);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 goiTuaDon = Translate(0, 0.5, -0.13) * RotateX(80) * Scale(0.5, 0.1, 0.5);
	drawCylinder(goiTuaDon, sofa_gheDonPos);
}
void sofa() {
	sofa_banPos = Translate(-1.6, 0, -1.5) * RotateY(90);

	sofa_ban();

	sofa_gheDaiPos = Translate(-3, 0, -1.5) * RotateY(90);
	sofa_gheDai();
	sofa_gheDonPos = Translate(-1.6, 0, -3);
	sofa_gheDon();
	sofa_gheDonPos = Translate(-1.6, 0, 0) * RotateY(180);
	sofa_gheDon();
}

#pragma endregion

#pragma region Robot
void robotCube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Scale(a, b, c);
	drawCube(instance, robotPos);
}
void robotCylinder(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Scale(a, b, c);
	drawCylinder(instance, robotPos);
}

void robot_chan() {
	color4 materialColor = RGBtoColor(49, 105, 133);
	color4 reflexColor = RGBtoColor(49, 105, 133);
	color4 mirrorReflexColor = RGBtoColor(49, 105, 133);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//bàn chân trái
	robotCube(-0.1, 0.05, 0.05, 0.15, 0.1, 0.2);
	//bàn chân phải
	robotCube(0.1, 0.05, 0.05, 0.15, 0.1, 0.2);
	//cẳng chân trái
	robotCylinder(-0.1, 0.35, 0, 0.1, 0.5, 0.1);
	//cẳng chân phải
	robotCylinder(0.1, 0.35, 0, 0.1, 0.5, 0.1);
	//đầu gối
	robotCylinder(-0.1, 0.35, 0, 0.12, 0.05, 0.12);
	robotCylinder(0.1, 0.35, 0, 0.14, 0.05, 0.14);
}
mat4 robotAct;
void robot_than() {
	color4 materialColor = RGBtoColor(49, 105, 133);
	color4 reflexColor = RGBtoColor(49, 105, 133);
	color4 mirrorReflexColor = RGBtoColor(49, 105, 133);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 robot_than = Translate(0, 0.85, 0) * Scale(0.4, 0.5, 0.3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_than);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
mat4 robot_handAct;
void robot_vai() {

	mat4 robot_vai1 = Translate(-0.27, 1.03, 0) * RotateZ(90) * Scale(0.15, 0.15, 0.15);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_vai1);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);

	mat4 robot_vai2 = Translate(0.27, 1.03, 0) * RotateZ(90) * Scale(0.15, 0.15, 0.15);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_vai2);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}
void robot_tay() {
	mat4 robot_tayTrai = Translate(-0.27, 0.8, 0) * Scale(0.08, 0.35, 0.08);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_tayTrai);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);

	mat4 robot_tayPhai = Translate(0.27, 0.8, 0) * Scale(0.08, 0.35, 0.08);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_tayPhai);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}
void robot_banTay() {
	mat4 robot_banTayTrai = Translate(-0.27, 0.6, 0) * Scale(0.1, 0.1, 0.1);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_banTayTrai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);

	mat4 robot_banTayPhai = Translate(0.27, 0.6, 0) * Scale(0.1, 0.1, 0.1);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_banTayPhai);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
mat4 robot_headAct;
void robot_dau() {
	//cổ
	mat4 robot_phanCo = Translate(0, 1.13, 0) * Scale(0.2, 0.06, 0.2);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_phanCo);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//đầu
	mat4 robot_phanDau = Translate(0, 1.36, 0) * Scale(0.5, 0.4, 0.3);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct* robot_headAct * robot_phanDau);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//mắt
	color4 materialColor = RGBtoColor(207, 98, 14);
	color4 reflexColor = RGBtoColor(207, 98, 14);
	color4 mirrorReflexColor = RGBtoColor(207, 98, 14);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 150);
	mat4 robot_matTrai = Translate(-0.1, 1.4, 0.15) * RotateX(90) * Scale(0.1, 0.04, 0.1);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_matTrai);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//mắt
	mat4 robot_matPhai = Translate(0.1, 1.4, 0.15) * RotateX(90) * Scale(0.1, 0.04, 0.1);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_matPhai);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//tai
	mat4 robot_tai1 = Translate(-0.25, 1.4, 0) * RotateZ(90) * Scale(0.15, 0.1, 0.15);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_tai1);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//tai
	mat4 robot_tai2 = Translate(0.25, 1.4, 0) * RotateZ(90) * Scale(0.15, 0.1, 0.15);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_tai2);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//miệng
	materialColor = RGBtoColor(207, 98, 14);
	reflexColor = RGBtoColor(207, 98, 14);
	mirrorReflexColor = RGBtoColor(207, 98, 14);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 robot_mieng = Translate(0, 1.25, 0.15) * Scale(0.3, 0.1, 0.05);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_mieng);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
	//ăng ten
	materialColor = RGBtoColor(11, 13, 10);
	reflexColor = RGBtoColor(11, 13, 10);
	mirrorReflexColor = RGBtoColor(11, 13, 10);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	mat4 robot_angTen = Translate(0, 1.76, 0) * Scale(0.02, 0.2, 0.02);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_angTen);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//đế ăng ten
	mat4 robot_deAngTen = Translate(0, 1.61, 0) * Scale(0.1, 0.1, 0.1);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_deAngTen);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
	//đầu ăng ten
	mat4 robot_dauAngTen = Translate(0, 1.88, 0) * Scale(0.05, 0.05, 0.05);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * robotPos * robotAct * robot_headAct * robot_dauAngTen);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}
void robot() {
	robotPos = Translate(-2, 0, 3.5);// *RotateY(90);
	robot_chan();
	robotAct = Translate(0, 0.6, 0) * RotateX(robot_baseHi)*RotateY(robot_baseSpin) * Translate(0, -0.6, 0);
	robot_than();
	robot_vai();
	robot_tay();
	robot_banTay();
	robot_headAct = RotateY(robot_headSpin);
	robot_dau();
}
#pragma endregion

//-------------------cửa hàng-----------------------
#pragma region Cửa hàng
void storeCube(float x, float y, float z, float a, float b, float c) {
	mat4 storeCube = Translate(x, y, z) * Scale(a, b, c);
	drawCube(storeCube, storePos);
}
void door(float x, float y, float z, float tx) {
	mat4 door = Translate(x, y, z) * Translate(tx, 0, 0) * Scale(1, 3.98, 0.02);
	drawCube(door, storePos);
}
void store_door() {
	color4 materialColor = RGBtoColor(204, 255, 229);
	color4 reflexColor = RGBtoColor(204, 255, 229);
	color4 mirrorReflexColor = RGBtoColor(204, 255, 229);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//cửa 1 từ trái sang
	door(-3, 2, 5, door_tx[0]);
	//cửa 2 từ trái sang
	door(-2, 2, 4.99, door_tx[1]);
	//cửa 3 từ trái sang
	door(-1, 2, 4.98, door_tx[2]);
	//cửa 4 từ trái sang
	door(0, 2, 4.97, door_tx[3]);
	//cửa 5 từ trái sang
	door(1, 2, 4.96, door_tx[4]);
	//cửa 5 từ trái sang
	door(2, 2, 4.95, door_tx[5]);
}
void store_wall() {
	//trục oxyz đặt tại chính giữa nền cửa hàng
	//sàn nhà
	if (batDen) {
		color4 materialColor = RGBtoColor(255, 255, 255);
		color4 reflexColor = RGBtoColor(255, 255, 255);
		color4 mirrorReflexColor = RGBtoColor(255, 255, 255);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 500);
	}
	else {
		color4 materialColor = RGBtoColor(120, 120, 120);
		color4 reflexColor = RGBtoColor(120, 120, 120);
		color4 mirrorReflexColor = RGBtoColor(120, 120, 120);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	}

	
	storeCube(0, 0, 0, 7, 0.01, 10);
	
	if (batDen) {
		materialColor = RGBtoColor(153, 255, 255);
		reflexColor = RGBtoColor(153, 255, 255);
		mirrorReflexColor = RGBtoColor(153, 255, 255);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	}
	else {
		materialColor = RGBtoColor(100, 100, 100);
		reflexColor = RGBtoColor(100, 100, 100);
		mirrorReflexColor = RGBtoColor(100, 100, 100);
		initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	}
	//trần nhà
	storeCube(0, 4, 0, 7, 0.01, 10);
	//tường trái
	storeCube(-3.45, 2, 0, 0.05, 4, 10);
	//tường phải
	storeCube(3.45, 2, 0, 0.05, 4, 10);
	//tường sau
	storeCube(0, 2, -4.95, 6.9, 4, 0.05);

	//tưởng phía trước ben phai
	storeCube(3, 2, 4.95, 1, 4, 0.05);
}
void store() {
	store_wall();
	store_door();
}
//--------------------------------------------------
//-----------------bảng hiệu--------------------------
mat4 bangHieuPos;
void bangHieu_chu() {
	//chữ G
	mat4 gngang1 = Translate(-0.4, 1.5, 0.05) * Scale(0.5, 0.1, 0.1);
	drawCube(gngang1, bangHieuPos);
	mat4 gdoc1 = Translate(-0.65, 1, 0.05) * Scale(0.1, 1, 0.1);
	drawCube(gdoc1, bangHieuPos);
	mat4 gngang2 = Translate(-0.4, 0.5, 0.05) * Scale(0.5, 0.1, 0.1);
	drawCube(gngang2, bangHieuPos);
	mat4 gdoc2 = Translate(-0.15, 0.75, 0.05) * Scale(0.1, 0.5, 0.1);
	drawCube(gdoc2, bangHieuPos);
	mat4 gngang3 = Translate(-0.15, 1, 0.05) * Scale(0.3, 0.1, 0.1);
	drawCube(gngang3, bangHieuPos);
	//số 3
	mat4 ngang1 = Translate(0.4, 1.5, 0.05) * Scale(0.5, 0.1, 0.1);
	drawCube(ngang1, bangHieuPos);
	mat4 ngang2 = Translate(0.4, 1, 0.05) * Scale(0.5, 0.1, 0.1);
	drawCube(ngang2, bangHieuPos);
	mat4 ngang3 = Translate(0.4, 0.5, 0.05) * Scale(0.5, 0.1, 0.1);
	drawCube(ngang3, bangHieuPos);
	mat4 doc = Translate(0.65, 1, 0.05) * Scale(0.1, 1, 0.1);
	drawCube(doc, bangHieuPos);
}
void bangHieu() {
	color4 materialColor = RGBtoColor(49, 105, 133);
	color4 reflexColor = RGBtoColor(49, 105, 133);
	color4 mirrorReflexColor = RGBtoColor(49, 105, 133);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	bangHieuPos = Translate(0, 4, 5);
	mat4 bangHieu = Translate(0, 1, 0) * Scale(7, 2, 0.02);
	drawCube(bangHieu, bangHieuPos);
	//chữ
	materialColor = RGBtoColor(240, 15, 15);
	reflexColor = RGBtoColor(240, 15, 15);
	mirrorReflexColor = RGBtoColor(240, 15, 15);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 150);
	bangHieu_chu();

}
#pragma endregion


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	at = direction + eye;
	view = RotateY(cameraRotate[1]) * LookAt(eye, at, up);
	//view = RotateX(cameraRotate[1]) * LookAt(eye, at, up);

	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);

	mat4 p = Frustum(l, r, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, p);

	//draw model
	//bối cảnh cửa hàng rộng 7m, cao 4m, sâu 10m, tường dày 5cm
	store();
	bangHieu();
	table();
	table2();
	keTV();		
	tuCaoDon();
	tuCaoDon2();
	tuTreo();	
	tuTreo2();
	tuQuanAo(); 
	BanChuZ();
	BanTron();
	BanTron2();
	QuayLeTan();
	DongHo();
	

	Tranh1();
	Tranh2();
	Tranh3();
	Tranh4();
	Tranh5();
	Tranh6();

	DenTuong1();
	DenTuong2();
	DenTuong3();
	DenTuong4();
	DenTuong5();
	DenTuong6();

	quatTran();
	robot();
	sofa();
	
	glutSwapBuffers();

}
//----------------------------------------------------------------------


void keyboard(unsigned char key, int x, int y)
{

	switch (key) {

	 case 'Q':
		exit(EXIT_SUCCESS);
		break;
#pragma region camera controller
	case 'y':
		cameraRotate[1] += 5;
		break;
	case 'Y':
		cameraRotate[1] -= 5;
		break;
	case 'u':
		eye += vec3(0, 0.05, 0);
		break;
	case 'U':
		eye += vec3(0, -0.05, 0);
		break;
	case 'w':
		eye -= direction;
		break;
	case 's':
		eye += direction;
		break;
	case 'a':
		eye += cameraRight;
		break;
	case 'd':
		eye -= cameraRight;
		break;
#pragma endregion
		//control door 
	case '7': //kéo 1 số ngăn kéo
		value[0] += .05;
		if (value[0] > .3) value[0] = .3;
		break;
	case '8':
		value[0] -= .05;
		if (value[0] < 0) value[0] = 0;
		break;
	case '('://mở 1 số cửa tủ
		value[1] += 5;
		if (value[1] > 90) value[1] = 90;
		break;
	case ')':
		value[1] -= 5;
		if (value[1] < 0) value[1] = 0;
		break;
#pragma region Door control
	case '1':
		door_tx[0] += 0.1;
		if (door_tx[0] >= 1)
		{
			batDen = true;
			door_tx[1] += 0.1;
			if (door_tx[1] >= 1)
			{
				door_tx[2] += 0.1;
				if (door_tx[2] >= 1)
				{
					door_tx[3] += 0.1;
					if (door_tx[3] >= 1)
					{
						robot_baseHi += 2.5;
						if (robot_baseHi >= 45) value[2] = 45;
						door_tx[4] += 0.1;
						if (door_tx[4] >= 1) {
							door_tx[5] += 0.1;
							if (door_tx[5] >= 1) {
								door_tx[0] = 6;
								door_tx[1] = 5;
								door_tx[2] = 4;
								door_tx[3] = 3;
								door_tx[4] = 2;
								door_tx[5] = 1;
								robot_baseHi -= 5;
								if (robot_baseHi <= 0)
									robot_baseHi = 0;
							}
						}
					}
				}
			}
		}
		break;
	case '2':
		door_tx[0] -= 0.1;
		if (door_tx[0] <= 5)
		{
			door_tx[1] -= 0.1;
			if (door_tx[1] <= 4)
			{
				door_tx[2] -= 0.1;
				if (door_tx[2] <= 3)
				{
					door_tx[3] -= 0.1;
					if (door_tx[3] <= 2)
					{
						batDen = false;
						robot_baseHi -= 2.5;
						if (robot_baseHi <= 0) robot_baseHi = 0;
						door_tx[4] -= 0.1;
						if (door_tx[4] <= 1)
						{
							door_tx[5] -= 0.1;
							if (door_tx[5] <= 0) {
								door_tx[0] = 0;
								door_tx[1] = 0;
								door_tx[2] = 0;
								door_tx[3] = 0;
								door_tx[4] = 0;
								door_tx[5] = 0;
							}
						}
					}
				}
			}
		}
		break;
#pragma endregion
		//quạt trần
	case '`':batQuat = !batQuat;
	case '+': quatTranSpeed += 1;
		if (quatTranSpeed >= 5) quatTranSpeed = 5;
		break;
	case '-':quatTranSpeed -= 1;
		if (quatTranSpeed <= 1) quatTranSpeed = 1;
		break;
	case '?': batDen = !batDen;
		break;
	//chế độ ngược, xoay chiều di chuyển
	case '3': nguoc = !nguoc;
		break;
	// điều khiển bàn học
	case 'i': table_x+= (0.1 * (nguoc ? -1 : 1));
		break;
	case 'o': table_z += (0.1 * (nguoc ? -1 : 1));
		break;
	case 'p': tableSpin += (5 * (nguoc ? -1 : 1));
		break;
	case '[': table_keo += (0.1 * (nguoc ? -1 : 1));
		if (table_keo >= 0.3) table_keo = 0.3;
		if (table_keo <= 0) table_keo = 0;
		break;
	case ']': table_moCuaTu += (2 * (nguoc ? -1 : 1));
		if (table_moCuaTu >= 90) table_moCuaTu = 90;
		if (table_moCuaTu <= 0) table_moCuaTu = 0;
		break;
	//điều khiển kệ tv
	case '{': keTV_x += (0.1 *(nguoc ? -1 : 1));
		break;
	case '}': keTV_z +=  (0.1 * (nguoc ? -1 : 1)) ;
		break;
	case '/': keTV_keo +=  (0.02 * (nguoc ? -1 : 1)) ;
		if (keTV_keo >= 0.3) keTV_keo = 0.3;
		if (keTV_keo <= 0) keTV_keo = 0;
		break;
	case '|': keTV_xoay += (0.1 * (nguoc ? -1 : 1)) ;
		break;
	//robot control
	case 'h':
		robot_headSpin += (5 * (nguoc ? -1 : 1)) ;
		break;
	case 'b':
		robot_baseSpin +=  (5 * (nguoc ? -1 : 1));
		break;
	case 'n':
		robot_baseHi += 2.5 * (nguoc ? -1 : 1);
		if (robot_baseHi >= 45) robot_baseHi = 45;
		if (robot_baseHi <= 0) robot_baseHi = 0;
		break;
	// tủ cao

	case 'j': tuCao_x += (0.1 * (nguoc ? -1 : 1));
		break;
	case 'k': tuCao_z += (0.1 * (nguoc ? -1 : 1));
		break;
	case 'l': tuCaoSpin += (5 * (nguoc ? -1 : 1));
		break;
	case ':': tuCao_keo += (0.1 * (nguoc ? -1 : 1));
		if (tuCao_keo >= 0.3) tuCao_keo = 0.3;
		if (tuCao_keo <= 0) tuCao_keo = 0;
		break;
	case ';': tuCao_keo2 += (0.1 * (nguoc ? -1 : 1));
		if (tuCao_keo2 >= 0.3) tuCao_keo2 = 0.3;
		if (tuCao_keo2 <= 0) tuCao_keo2 = 0;
		break;
	case '\'': tuCao_moCua += (2 * (nguoc ? -1 : 1));
		if (tuCao_moCua >= 90) tuCao_moCua = 90;
		if (tuCao_moCua <= 0) tuCao_moCua = 0;
		break;
	//tủ quần áo
	case 'x': tuQuanAo_x += (0.1 * (nguoc ? -1 : 1));
		break;
	case 'z': tuQuanAo_z += (0.1 * (nguoc ? -1 : 1));
		break;
	case 'c': tuQuanAoSpin += (5 * (nguoc ? -1 : 1));
		break;
	case 'v': tuQuanAo_moCua += (2 * (nguoc ? -1 : 1));
		if (tuQuanAo_moCua >= 90) tuQuanAo_moCua = 90;
		if (tuQuanAo_moCua <= 0) tuQuanAo_moCua = 0;
		break;
	//reset view volumn
	case ' ':
		eye = vec3(0, 2, 8);
		at = vec3(0, 0, 0);
		up = vec3(0, 1, 0);
		cameraRotate[1] = 90;
		
		break;
	}
	glutPostRedisplay();

}
void idleControl() {
	if (batQuat) {
		quatTranSpin += 1 * quatTranSpeed;
		if (quatTranSpin >= 360) quatTranSpin -= 360;
	}
	else quatTranSpin = 0;
	glutPostRedisplay();
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
	generateModels();
	initGPUBuffer();
	shaderSetup();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idleControl);
	glutMainLoop();

	return 0;
}