#include "GL/freeglut.h"
#include <iostream>

using namespace std;

int oldMousePosX = 0, oldMousePosY = 0; //lưu toạ độ chuột click vừa rồi
float rotateX = 0.0f, rotateY = 0.0f;   //góc xoay vật thể vật theo mouse drag
GLint spin;

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 5.0, 1.0 };

GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

void initialize()
{
	glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //kích hoạt bộ đệm màu sắc, bộ đệm thông tin chiều sâu
	glEnable(GL_DEPTH_TEST);   // Kích hoạt chế độ Depth testing
	glEnable(GL_LIGHTING);     // Kích hoạt chế độ (tính toán) ánh sáng
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //Cài đặt giá trị màu nền

										  //////////////////////////
										  // A Thiết lập ánh sáng //
										  //////////////////////////

										  //Nguon sang 1
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//nguon sang 2
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	//	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	//	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	//	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	////////////////////////////////////////////
	// B Thiết lập độ phản xạ của vật liệu    //
	////////////////////////////////////////////

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; //ko có chất liệu - màu trắng
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; //màu phản xạ môi trường của chất liệu
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 }; //màu môi trường
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 }; //màu phản xạ khuyếch tán của chất liệu
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //màu phản xạ gương của chất liệu
	GLfloat no_shininess[] = { 0.0 }; //độ lấp lánh của chất liệu ko sáng bóng
	GLfloat low_shininess[] = { 5.0 }; //độ lấp lánh trung bình của chất liệu
	GLfloat high_shininess[] = { 100.0 }; //độ lấp lánh cao của chất liệu
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 }; //độ phát xạ màu sắc của chất liệu


	GLfloat diffColors[4] = { 0.5f, 0.5f, 0.9f, 1.0f }; // Thiết lập màu khuyết tán,
	GLfloat specColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // màu phản xạ gương(specular color)
	GLfloat shininess[] = { 100.0f }; //  độ lấp lánh (shininess)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	/* chỉ có phản xạ khuyếch tán
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	*/

	/* chất liệu phản xạ khuyếch tán và phản xạ gương.
	Độ lấp lánh thấp và không có phản xạ môi trường, không phát xạ (emission).
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	*/

	/* chất liệu phản xạ khuyếch tán và phản xạ gương.
	Độ lấp lánh cao và không có phản xạ môi trường, không phát xạ (emission).
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	*/

	/* Vẽ vật thể với chất liệu phản xạ khuyếch tán.
	Không có độ lấp lánh , không có phản xạ môi trường, nhưng có phát xạ (emission).
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

	*/
}

void setupViewPort() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 1.0, 100.0); //(degree fov, uniform aspect ratio, near, far)

	glMatrixMode(GL_MODELVIEW);  // Sử dụng ma trận ModelView - tương tác với vị trí vật thể
	glLoadIdentity();              // Khởi tạo ma trận đơn vị (identity) hoặc xoá ma trận hiện hành thành ma trận đơn vị
	gluLookAt(0.0, 1.0, 5.0,  // Thiết lập vị trí camera [0,0,5], 
		0.0, 1.0, 0.0,		  // hướng nhìn về [0,0,0],
		0.0, 1.0, 0.0);       // với vector hướng lên là [0,1,0] (hướng nhìn đứng là theo toạ độ y (hướng lên trên).

}

// Hàm xử lý khi thay đổi kích thước cửa sổ w, h - chiều rộng và cao của cửa sổ tính trên pixel.
void reshapeFunc(int w, int h)
{
	if (w > h) {
		glViewport((w - h) / 2, 0, h, h);
	}
	else {
		glViewport(0, (h - w) / 2, w, w);
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 1.0, 100.0); //(degree fov, uniform aspect ratio, near, far)
	glMatrixMode(GL_MODELVIEW);
}

// Hàm vẽ các đối tượng.
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xoá ảnh trong buffer trước khi vẽ  //

														/////////////////////////////
														// C Vẽ vật thể 2D hoặc 3D //
														/////////////////////////////
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glPushMatrix();
	glRotated((GLdouble)spin, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glutSolidTeapot(1.0);
	glPopMatrix();

	//	glRotated(spin, 1.0, 0.0, 0.0);
	//	glutSolidTeapot(1.0); // Hàm vẽ ấm trà 
	glutSwapBuffers(); //chuyển đổi buffer và xuất ra màn hình
}

// Hàm Xử lý sự kiện bàn phím 
void keyboardFunc(unsigned char key, int x, int y)
{
	cout << "key press: " << key << endl;
	switch (key)
	{
	case 27: // Phím Escape  (Esc)
		exit(0); //thoát chương trình
		break;
	case 'c':

		break;
	case '1':

		break;
	case '2':

		break;
	case '3':

		break;
	case '4':

		break;
	case '5':

		break;
	case '6':

		break;
	case '7':

		break;
	case '8':

		break;
	case '9':

		break;
	case '0':
		spin = (spin + 30) % 360;
		break;
	case 'W':
	case 'w':

		break;
	case 'S':
	case 's':

		break;
	case 'A':
	case 'a':

		break;
	case 'D':
	case 'd':

		break;
	case 'P':
	case 'p':

		break;
	case 'L':
	case 'l':

		break;

	default:
		cout << "chua xu ly phim nay: " << key << "." << endl;
	}
	// refresh màn hình (vẽ lại khi có thay đổi)
	glutPostRedisplay();
}

// Hàm xử lý sự kiện các phím đặc biệt
void specialFunc(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;
	}
	// refresh màn hình (vẽ lại khi có thay đổi)
	glutPostRedisplay();
}
bool pressed = false;
void mouseButton(int button, int state, int x, int y) {// (phím chuột, trạng thái chuột, toạ độ x, toạ độ y)

	if (button == GLUT_LEFT_BUTTON) { //Chuột trái								 

		pressed = true;
		if (state == GLUT_UP) { //Nhả chuột
			pressed = false;
		}
		else {

		}
	}
	glutPostRedisplay();
}

void mouseMove(int x, int y) { // (toạ độ x, toạ độ y) khi di chuyển chuột
	if (pressed) {
		rotateX += 0.02f*(float)(x - oldMousePosX);
		rotateY += 0.02f*(float)(y - oldMousePosY);
		oldMousePosX = x;
		oldMousePosY = y;
		glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
		glutPostRedisplay();
	}
}


int main(int argc, char** argv)
{
	///////////////////////////////////////////////////
	// Các hàm khởi tạo cửa sổ và thiết lập mặc định //
	///////////////////////////////////////////////////
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Thiết lập chế độ hiển thị hình ảnh
	glutInitWindowPosition(60, 60); // Thiết lập vị trí cửa sổ chính của chương trình
	glutInitWindowSize(360, 360);   // Thiết lập kích thước cửa sổ chính 
	glutCreateWindow("DHNC Lab3"); //Tạo cửa sổ với tiêu đề DHNC Lab3

	initialize(); //Khởi tạo các trạng thái vẽ toàn cục 
	setupViewPort(); //thiết lập camera, khung nhìn, góc nhìn ...
	glutReshapeFunc(reshapeFunc);   // Đăng ký hàm xử lý khi thay đổi kích thước cửa sổ

									///////////////////////////////////////////////////////////////////////////////////
									// Đăng ký các hàm callback (xử lý sự kiện chuột, bàn phím, thay đổi cửa sổ ...  //
									///////////////////////////////////////////////////////////////////////////////////

	glutKeyboardFunc(keyboardFunc); // Xử lý các kí tự ascii thông thường từ bàn phím
	glutSpecialFunc(specialFunc);   // Xử lý các kí tự đặc biệt từ bàn phím

	glutMouseFunc(mouseButton);  //Xử lý các sự kiện bấm chuột
	glutMotionFunc(mouseMove);	 //Xử lý các sự kiện di chuyển chuột

								 ///////////////////
								 // Hàm vẽ chính  //
								 ///////////////////
	glutDisplayFunc(draw);     // Đăng ký hàm vẽ đối tượng

	glutMainLoop(); 	// Khởi tạo vòng lặp chính, hàm glutMainLoop không bao giờ kết thúc trừ khi có sự kiện thoát.

	return 0;
}


/*

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void changeSize(int w, int h) {

// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
if (h == 0)
h = 1;

float ratio = w * 1.0 / h;

// Use the Projection Matrix
glMatrixMode(GL_PROJECTION);

// Reset Matrix
glLoadIdentity();

// Set the viewport to be the entire window
glViewport(0, 0, w, h);

// Set the correct perspective.
gluPerspective(45.0f, ratio, 0.1f, 100.0f);

// Get Back to the Modelview
glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
glTranslatef(0.0f, 0.75f, 0.0f);
glutSolidSphere(0.75f, 20, 20);

// Draw Head
glTranslatef(0.0f, 1.0f, 0.0f);
glutSolidSphere(0.25f, 20, 20);

// Draw Eyes
glPushMatrix();
glColor3f(0.0f, 0.0f, 0.0f);
glTranslatef(0.05f, 0.10f, 0.18f);
glutSolidSphere(0.05f, 10, 10);
glTranslatef(-0.1f, 0.0f, 0.0f);
glutSolidSphere(0.05f, 10, 10);
glPopMatrix();

// Draw Nose
glColor3f(1.0f, 0.5f, 0.5f);
glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
glutSolidCone(0.08f, 0.5f, 10, 2);
}

void computePos(float deltaMove) {

x += deltaMove * lx * 0.1f;
z += deltaMove * lz * 0.1f;
}

void renderScene(void) {

if (deltaMove)
computePos(deltaMove);

// Clear Color and Depth Buffers
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Reset transformations
glLoadIdentity();
// Set the camera
gluLookAt(x, 1.0f, z,
x + lx, 1.0f, z + lz,
0.0f, 1.0f, 0.0f);

// Draw ground

glColor3f(0.9f, 0.9f, 0.9f);
glBegin(GL_QUADS);
glVertex3f(-100.0f, 0.0f, -100.0f);
glVertex3f(-100.0f, 0.0f, 100.0f);
glVertex3f(100.0f, 0.0f, 100.0f);
glVertex3f(100.0f, 0.0f, -100.0f);
glEnd();

// Draw 36 SnowMen

for (int i = -3; i < 3; i++)
for (int j = -3; j < 3; j++) {
glPushMatrix();
glTranslatef(i*10.0, 0, j * 10.0);
drawSnowMan();
glPopMatrix();
}
glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {

if (key == 27)
exit(0);
}

void pressKey(int key, int xx, int yy) {

switch (key) {
case GLUT_KEY_UP: deltaMove = 0.5f; break;
case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
}
}

void releaseKey(int key, int x, int y) {

switch (key) {
case GLUT_KEY_UP:
case GLUT_KEY_DOWN: deltaMove = 0; break;
}
}

void mouseMove(int x, int y) {

// this will only be true when the left button is down
if (xOrigin >= 0) {

// update deltaAngle
deltaAngle = (x - xOrigin) * 0.001f;

// update camera's direction
lx = sin(angle + deltaAngle);
lz = -cos(angle + deltaAngle);
}
}

void mouseButton(int button, int state, int x, int y) {

// only start motion if the left button is pressed
if (button == GLUT_LEFT_BUTTON) {

// when the button is released
if (state == GLUT_UP) {
angle += deltaAngle;
xOrigin = -1;
}
else {// state = GLUT_DOWN
xOrigin = x;
}
}
}

int main(int argc, char **argv) {

// init GLUT and create window
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100, 100);
glutInitWindowSize(320, 320);
glutCreateWindow("Lighthouse3D - GLUT Tutorial");

// register callbacks
glutDisplayFunc(renderScene);
glutReshapeFunc(changeSize);
glutIdleFunc(renderScene);

glutIgnoreKeyRepeat(1);
glutKeyboardFunc(processNormalKeys);
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey);

// here are the two new functions
glutMouseFunc(mouseButton);
glutMotionFunc(mouseMove);

// OpenGL init
glEnable(GL_DEPTH_TEST);

// enter GLUT event processing cycle
glutMainLoop();

return 1;
}

*/