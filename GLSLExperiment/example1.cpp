
#include "Angel.h"
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
const int numPointsOfCube = 36; //số điểm tạo hlp
const int numPointsOfCylinder = 96; //số điểm tạo htru
const int numPointsOfCircle = 192; //số điểm tạo htron
//danh sach cac dinh tam giac
point4 arrVertices[numPointsOfCube + numPointsOfCylinder ];
//danh sach cac color
color4 arrColors[numPointsOfCube+ numPointsOfCylinder];
//danh sach cac vector phap tuyen
vec3 arrNormals[numPointsOfCube+ numPointsOfCylinder];
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
GLuint viewLoc,modelLoc, projectionLoc,program;
mat4 view,model,tablePos,keTVPos,tuCaoPos,tuTreoPos,tuQuanAoPos, banChuZPos,banTronPos,quayLeTanPos;
GLfloat value[] = { 0,0,0,0 };
GLfloat cameraRotate[] = { 0,0,0 };
//Lookat function
GLfloat l = -0.5, r = 0.5, bottom = -0.5, top = 0.5, zNear = 0.5, zFar = 10;
//camera controller 
vec3 eye = vec3(0,2,5);
vec3 at = vec3(0,0,0);
vec3 up = vec3(0, 1, 0);
GLfloat t = 0.05;
vec3 direction = normalize(vec3(cosf(DegreesToRadians*cameraRotate[0]) * abs(sinf(DegreesToRadians * cameraRotate[1])),
	sinf(DegreesToRadians * cameraRotate[0]),
	cosf(DegreesToRadians * cameraRotate[2]) * abs(cosf(DegreesToRadians * cameraRotate[1]))));
vec3 cameraLeft = normalize(cross(direction, up));

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
	/*for (int i = 0; i < 7; i++) {
		sideOfCylinder(2*(i+1), 2*(i + 1)-1, 2 * (i + 1) +1, 2*i + 4, i);
	}
	sideOfCylinder(16, 15, 1, 2, 7);*/

	// 3x8
	
	bottomTriange_Cylinder(2, 17, 16, 9);
	bottomTriange_Cylinder(16, 17, 14, 9);
	bottomTriange_Cylinder(14, 17, 12, 9);
	bottomTriange_Cylinder(12, 17, 10, 9);
	bottomTriange_Cylinder(10, 17, 8, 9);
	bottomTriange_Cylinder(8, 17, 6, 9);
	bottomTriange_Cylinder(6, 17, 4, 9);
	bottomTriange_Cylinder(4, 17, 2, 9);
	/*bottomTriange_Cylinder(2, 17, 16, 8);

	for (int i = 6; i >=0; i--) {
		bottomTriange_Cylinder(2 * i+4, 17, 2 * i + 2, 8);
	}
	for (int i = 0; i <= 6; i++) {
		bottomTriange_Cylinder(2 * (i + 1) - 1, 0, 2 * (i + 1) + 1, 9);
	}
	bottomTriange_Cylinder(15, 0, 1, 9);*/

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
float convertColor(float x)
{
	return x / 255;
}
color4 RGBtoColor(int R, int G, int B)
{
	return color4(convertColor(R), convertColor(G), convertColor(B));
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

	// Retrieve transformation uniform variable locations
	viewLoc = glGetUniformLocation(program, "View");
	modelLoc = glGetUniformLocation(program, "Model");
	projectionLoc = glGetUniformLocation(program, "Projection");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void drawCube(mat4 instance,mat4 localPos)
{
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * localPos * instance);
	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
}
void drawCylinder(mat4 instance,mat4 localPos)
{
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model *localPos* instance);
	glDrawArrays(GL_TRIANGLES, 36, numPointsOfCylinder);
}

//----------------------------------------------------------------------

void chanBan(float x, float y, float z) {
	mat4 chan = Translate(x, y,z) * Scale(.06, .8, .06);
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
//-------------------ngăn kéo 54 x 2 x 60--------------------------
void table_nganKeo() {
	// hộp tủ ngăn kéo bên trái
	mat4 tuNganKeo = Translate(-.55, -.06, 0) * Scale(.02, .1, .48);
	drawCube(tuNganKeo, tablePos);
	//ngăn kéo chính
	mat4 nganKeo = Translate(-.27, -.1, 0) * Translate(0, 0, value[0]) * Scale(.54, .02, .58);
	drawCube(nganKeo, tablePos);
	//cửa ngăn kéo phía trước
	mat4 cuaNganKeo = Translate(-.27, -.075, .28) * Translate(0, 0, value[0]) * Scale(.54, .15, .02);
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
	mat4 cuaTu = Translate(.53, -.36, .29) * RotateY(value[1]) * Translate(-.27, 0, 0) * Scale(.55, .7, .02);
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
void table() {
	tablePos = Translate(-2.2, 0.81, 2.5)* RotateY(90);
	materialColor = RGBtoColor(220, 150, 90);
	reflexColor = RGBtoColor(220, 150, 90);
	mirrorReflexColor = RGBtoColor(220, 150, 90);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	table_ban4chan();
	table_nganKeo();
	table_hopTu();
	table_keSach();
}

void keTV_tinh_cube(float x, float y, float z,float a,float b,float c) {
	mat4 instance = Translate(x,y,z) * Scale(a,b,c);
	drawCube(instance, keTVPos);
}
void keTV_dong_cube(float x, float y, float z, float a, float b, float c) {
	mat4 instance = Translate(x, y, z) * Translate(0, 0, value[0]) * Scale(a,b,c);
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
	keTV_tinh_cube(.99, .61, -.15,0.02,1.2,0.3); //4
	//xương dọc sau tủ trái
	//keTV_tinh_cube(-0.81,0.61,-0.29,0.34,1.2,0.02);
	mat4 xuongDoc5 = Translate(-.81, .61, -.29) * Scale(.34, 1.2, .02);
	drawCube(xuongDoc5, keTVPos);
	//xương dọc sau tủ phải
	mat4 xuongDoc6 = Translate(.81, .61, -.29) * Scale(.34, 1.2, .02);
	drawCube(xuongDoc6, keTVPos);
	//tấm ngang
	keTV_tinh_cube(-.81, 1.22, -.15, .38, 0.2, .3);
	keTV_tinh_cube(.81, 1.22, -.15, .38, 0.2, .3);
	keTV_tinh_cube(-.81, .92, -.15, .38, 0.2, .28);
	keTV_tinh_cube(.81, .92, -.15, .38, 0.2, .28);
	keTV_tinh_cube(-.81, .62, -.15, .38, 0.2, .28);
	keTV_tinh_cube(.81, .62, -.15, .38, 0.2, .28);
	keTV_tinh_cube(-.81, .32, -.15, .38, 0.2, .28);
	keTV_tinh_cube(.81, .32, -.15, .38, 0.2, .28);
	//tam ngang giua
	mat4 tamNgangGiua = Translate(0,1.1,-.15) * Scale(1.28, .02, .2);
	drawCube(tamNgangGiua, keTVPos);
}

void keTV() {
	keTVPos = Translate(0, .5, -2);//*RotateY(90);
	keTV_keTu();
	keTV_nganKeo();
	keTV_tuKinh();
}
void tuCao_phanTinh() {
	color4 materialColor = RGBtoColor(255, 255, 172);
	color4 reflexColor = RGBtoColor(255, 255, 172);
	color4 mirrorReflexColor = RGBtoColor(255, 255, 172);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//hộp tủ sau
	mat4 tuCao_hopTuSau = Translate(0,0,-.175) * Scale(0.4, 2, .02);
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
void tuCao_phanDong() {
	//ngăn kéo
	mat4 tuCao_nganKeo1 = Translate(0, -.63, 0)*Translate(0,0,value[0]) * Scale(.36, .02, .35);
	drawCube(tuCao_nganKeo1, tuCaoPos);
	mat4 tuCao_nganKeo2 = Translate(0, -.97, 0) * Translate(0, 0, value[0]) * Scale(.36, .02, .35);
	drawCube(tuCao_nganKeo2, tuCaoPos);
	//cửa kéo
	mat4 tuCao_cuaKeo1 = Translate(0, -.48, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	drawCube(tuCao_cuaKeo1, tuCaoPos);
	mat4 tuCao_cuaKeo2 = Translate(0, -.82, .18) * Translate(0, 0, value[0]) * Scale(.36, .33, .02);
	drawCube(tuCao_cuaKeo2, tuCaoPos);
	//hộp ngăn kéo
	//trên
	mat4 tuCao_hopKeo1 = Translate(-.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	drawCube(tuCao_hopKeo1, tuCaoPos);
	mat4 tuCao_hopKeo2 = Translate(.18, -.55, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	drawCube(tuCao_hopKeo2, tuCaoPos);
	//dưới
	mat4 tuCao_hopKeo3 = Translate(-.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	drawCube(tuCao_hopKeo3, tuCaoPos);
	mat4 tuCao_hopKeo4 = Translate(.18, -.89, 0) * Translate(0, 0, value[0]) * Scale(.01, .2, .35);
	drawCube(tuCao_hopKeo4, tuCaoPos);
	//cửa tủ
	mat4 tuCao_cuaTu = Translate(.2, .35, .18) * RotateY(value[1])*Translate(-.2, 0, 0) * Scale(.4, 1.3, .02);
	drawCube(tuCao_cuaTu, tuCaoPos);
}
void tuCaoDon() {
	tuCaoPos = Translate(0, 1, 0);//*RotateY(90);
	tuCao_phanTinh();
	tuCao_phanDong();
}
void tuTreo_phanTinh()
{
	// màu tủ
	color4 materialColor = RGBtoColor(193, 100, 56);
	color4 reflexColor = RGBtoColor(193, 100, 56);
	color4 mirrorReflexColor = RGBtoColor(193, 100, 56);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
	//hộp tủ bên phải
	mat4 tuTreo_hopTuTrai = Translate(-.35,.4,0) * Scale(.01, .8, .4);
	drawCube(tuTreo_hopTuTrai, tuTreoPos);
	//hộp tủ bên trái
	mat4 tuTreo_hopTuPhai = Translate(.35, .4, 0) * Scale(.01, .8, .4);
	drawCube(tuTreo_hopTuPhai, tuTreoPos);
	//hộp tủ mặt đáy
	mat4 tuTreo_hopDay = Scale(.7, .01, .4);
	drawCube(tuTreo_hopDay, tuTreoPos);
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
	mat4 tuTreo_cuaTrai = Translate(-.35, .25, 0.2)*RotateY(-value[1])*Translate(.17,0,0) * Scale(.35, .5, .01);
	drawCube(tuTreo_cuaTrai, tuTreoPos);
	//cửa mở phải
	mat4 tuTreo_cuaPhai = Translate(.35, .25, 0.2) * RotateY(value[1]) * Translate(-.17,0,0) * Scale(.35, .5, .01);
	drawCube(tuTreo_cuaPhai, tuTreoPos);
	//cửa lật lên trên
	mat4 tuTreo_cuaLat = Translate(0, .8, 0.2) * RotateX(-value[1])*Translate(0,-.15,0) * Scale(.69, .3, .01);
	drawCube(tuTreo_cuaLat, tuTreoPos);
}
void tuTreo() {
	// cao 80 rộng 70 sâu 40
	tuTreoPos = Translate(1, 1, -3);
	tuTreo_phanTinh();
	tuTreo_phanDong();
}
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
	mat4 tuQuanAo_tamNgang = Translate(0,1.65, 0) * Scale(1.18, .01, .5);
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
	drawCylinder(tuQuanAo_hopTrai, tuQuanAoPos);

}
void tuQuanAo_phanDong() {
	//cánh cửa hộp tủ trái
	mat4 tuQuanAo_cuaHopTrai = Translate(-.6, 1.025, .25)*RotateY(-value[1])*Translate(.2,0,0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaHopTrai, tuQuanAoPos);
	//cánh tủ chính bên trái
	mat4 tuQuanAo_cuaTrai = Translate(-.2, 1.025, .25) * RotateY(-value[1]) * Translate(.2, 0, 0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaHopTrai, tuQuanAoPos);
	//cánh tủ chính bên phải
	mat4 tuQuanAo_cuaPhai = Translate(.595, 1.025, .25) * RotateY(value[1]) * Translate(-.2, 0, 0) * Scale(.39, 1.94, .01);
	drawCube(tuQuanAo_cuaPhai, tuQuanAoPos);
}
void tuQuanAo() {
	tuQuanAoPos = Translate(1, 0, 2.5);// * RotateY(180);
	tuQuanAo_phanTinh();
	tuQuanAo_phanDong();
}
// Vẽ bàn chữ Z
void BanchuZ_matban() {
	// màu đỏ
	color4 materialColor = RGBtoColor(137, 11, 11);
	color4 reflexColor = RGBtoColor(137, 11, 11);
	color4 mirrorReflexColor = RGBtoColor(137, 11, 11);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_matban = Scale(1.6, .06, 0.8);
	drawCube(banChuZ_matban, banChuZPos);
}
void BanChuZ_matdoc() {
	color4 materialColor = RGBtoColor(255, 0, 0);
	color4 reflexColor = RGBtoColor(255, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(255, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_matdoc = Translate(0, -0.15, -0.34) * Scale(1.6, .3, 0.06);
	drawCube(banChuZ_matdoc, banChuZPos);

}
void BanChuZ_chanban(GLfloat transX, GLfloat transY, GLfloat transZ) {
	//màu đen
	color4 materialColor = RGBtoColor(10, 10, 10);
	color4 reflexColor = RGBtoColor(30, 30, 30);
	color4 mirrorReflexColor = RGBtoColor(30, 30, 30);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_chanban = Translate(transX, transY, transZ) * Scale(0.1, 0.1, 0.6);
	drawCube(banChuZ_chanban, banChuZPos);

}
void BanChuZ_chancheo(GLfloat transX, GLfloat transY, GLfloat transZ) {
	//màu đen
	color4 materialColor = RGBtoColor(10, 10, 10);
	color4 reflexColor = RGBtoColor(30, 30, 30);
	color4 mirrorReflexColor = RGBtoColor(30, 30, 30);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banChuZ_chanban = Translate(transX, transY, transZ) * RotateX(63) * Scale(0.1, 0.1, 1.26);
	drawCube(banChuZ_chanban, banChuZPos);

}
void BanChuZ() {

	BanchuZ_matban();
	BanChuZ_matdoc();

	BanChuZ_chanban(0.75, -1.2, 0);
	BanChuZ_chanban(-0.75, -1.2, 0);
	BanChuZ_chanban(0.75, -0.05, 0);
	BanChuZ_chanban(-0.75, -0.05, 0);

	BanChuZ_chancheo(0.75, -0.67, 0);
	BanChuZ_chancheo(-0.75, -0.67, 0);

}
//Vẽ bàn tròn
void BanTron_matban() {
	// màu đỏ
	color4 materialColor = RGBtoColor(222, 215, 204);
	color4 reflexColor = RGBtoColor(222, 215, 204);
	color4 mirrorReflexColor = RGBtoColor(222, 215, 204);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banTron_matban = Scale(3, 0.25, 1.5);
	drawCylinder(banTron_matban, banTronPos);

}
void BanTron_chanban() {
	// màu đen
	color4 materialColor = RGBtoColor(40, 43, 42);
	color4 reflexColor = RGBtoColor(40, 43, 42);
	color4 mirrorReflexColor = RGBtoColor(40, 43, 42);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 banTron_chanban = Translate(0, -0.75, 0) * Scale(0.25, 1.5, 0.25);
	drawCylinder(banTron_chanban, banTronPos);

	mat4 banTron_chandayban = Translate(0, -1.5 - 0.1 / 2, 0) * Scale(0.75, 0.1, 0.75);
	drawCylinder(banTron_chandayban, banTronPos);
}
void BanTron() {
	BanTron_matban();
	BanTron_chanban();
}

void theLeTan(GLfloat transX, GLfloat transY, GLfloat transZ) {
	color4 materialColor = RGBtoColor(0, 0, 0);
	color4 reflexColor = RGBtoColor(0, 0, 0);
	color4 mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 theLetan1 = Scale(0.3, 0.08, 0.02);
	drawCube(theLetan1, quayLeTanPos);

	materialColor = RGBtoColor(255, 255, 51);
	reflexColor = RGBtoColor(255, 255, 51);
	mirrorReflexColor = RGBtoColor(255, 255, 51);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 theLetan2 = Translate(0, 0.05, 0) * Scale(0.28, 0.1, 0.01);
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

	mat4 chande1 = Translate(1.15, 0.05, 0.45) * Scale(0.1, 0.01, 0.1);
	drawCube(chande1, quayLeTanPos);

	mat4 chande2 = Translate(1.15, 0.2, 0.45) * Scale(0.02, 0.4, 0.02);
	drawCube(chande2, quayLeTanPos);

	materialColor = RGBtoColor(0, 0, 0);
	reflexColor = RGBtoColor(0, 0, 0);
	mirrorReflexColor = RGBtoColor(0, 0, 0);
	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);

	mat4 manHinhPC = Translate(1.13, 0.3, 0.45) * Scale(0.02, 0.4, 0.3);
	drawCube(manHinhPC, quayLeTanPos);


}
void QuayLeTan() {
	theLeTan(0, 0, 0);
	BanLeTan();
	mayTinh();
}
//bối cảnh
//void store() {
//	materialColor = RGBtoColor(190, 240, 240, 1);
//	reflexColor = RGBtoColor(190, 240, 240, 1);
//	mirrorReflexColor = RGBtoColor(190, 240, 240, 1);
//	initMaterial(materialColor, reflexColor, mirrorReflexColor, 1000);
//	//trục oxyz đặt tại chính giữa nền cửa hàng
//	mat4 ground = Scale(7, .01, 10);
//	drawCube(ground, model);
//
//	//tường trái
//	mat4 wall1 =Translate(-3.45,2,0)* Scale(0.05, 4, 10);
//	drawCube(wall1, model);
//	
//	//tường phải
//	mat4 wall2 = Translate(3.45, 2, 0) * Scale(0.05, 4, 10);
//	drawCube(wall2, model);
//
//	//tường sau
//	mat4 wall3 = Translate(0,2,4.95) * Scale(6.9, 4, 0.05);
//	drawCube(wall3);
//	//tường phía trước
//	//tường lề trái 
//	mat4 frontWall1 = Translate(-((width/2)-0.5), height/2, depth/2) * Scale(1, height, wallWidth);
//	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * frontWall1);
//	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
//	//tường lề phải
//	mat4 frontWall2 = Translate(1.5, height / 2, depth / 2)* Scale(3, height, wallWidth);
//	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model * frontWall2);
//	glDrawArrays(GL_TRIANGLES, 0, numPointsOfCube);
//
//}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//at = vec3(cosf(DegreesToRadians *cameraRotate[0]),0,cosf(DegreesToRadians*cameraRotate[2])) + eye;
	at = direction + eye;
	view = RotateY(cameraRotate[1]) * LookAt(eye, at, up);
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view );

	mat4 p = Frustum(l, r, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projectionLoc, 1, GL_TRUE,p);


	//draw model
	//bối cảnh cửa hàng rộng 5m, cao 3.5m, sâu 7m, tường dày 5cm
	//table();	//bàn học
	//keTV();		//kệ tivi
	//tuCaoDon(); //tủ cao 
	//tuTreo();	//tủ treo
	//tuQuanAo();  //tủ quần áo
	//BanChuZ();
	BanTron();
	//QuayLeTan();
	
	glutSwapBuffers();

}
//----------------------------------------------------------------------


void keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
		
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'y':
		cameraRotate[1] += 5;
		glutPostRedisplay();
		break;
	case 'Y':
		cameraRotate[1] -=5;
		glutPostRedisplay();
		break;
	
	case 'w':
		eye -= direction;
		glutPostRedisplay();
		break;
	case 's':
		eye += direction ;
		glutPostRedisplay();
		break;
	case 'a':
		eye +=cameraLeft ;
		glutPostRedisplay();
		break;
	case 'd':
		eye -= cameraLeft;
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
		eye = vec3(0, 2, 5);
		at = vec3(0, 0, 0);
		up = vec3(0, 1, 0);
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