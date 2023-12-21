#include <GL/glut.h>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <wingdi.h>

int lebarWindow = 800;
int tinggiWindow = 600;
float posisiBulanX = -200.0f;
bool sedangGerhana = false;
float insesitasEfekGerhana = 0.0f;
float insesitasBulan = 0.0f;
using  namespace std;

int i, s, m, y;
string ins[2] = { "Disini kita akan melakukan simulasi gerhana matahari", ""};
string t;

GLfloat road_ambient[] = {.5, .5, .5, .1};
GLfloat ground_ambient[] = {.7, .7, .8, .1};
GLfloat path_ambient[] = {3.5, 3.5, 3.5, .1};
GLfloat doorFront_ambient[] = {4, 4, 4, .1};
GLfloat grass_ambient[] = {.5, 3, .5, .1};

GLfloat doorRot = 0;
GLfloat doorRot2 = 0;
GLfloat schoolDoorRot = 0;

struct Awan
{
    float x;
    float y;
};

std::vector<Awan> posisiAwan;

const int terrainSize = 120;
float terrain[terrainSize][terrainSize];

void text()
{
	m = 0;
	y = 500;
	s = 15;
    
    glTranslatef(-710, -300, 0.0f);

	while (m < 5)
	{
		t = ins[m];
		for (i = 0; i < t.length(); i++)
		{
			glColor3f(1,1,1);
			glRasterPos2i((i * s) + 20, y);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, t.at(i));
		}
		m++;
		y = y - 30;
	}
}

long map(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void circle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void generateTerrain()
{
    for (int i = 0; i < terrainSize; ++i)
    {
        for (int j = 0; j < terrainSize; ++j)
        {
            terrain[i][j] = static_cast<float>(rand() % 100) / 100.0f;
        }
    }
}

void gambarTerrain()
{
    glColor3f(0.3f - (insesitasEfekGerhana * 2.0f), 1.0f - (insesitasEfekGerhana * 2.0f), 0.3f - (insesitasEfekGerhana * 2.0f)); // Warna terrain (hijau)

    glBegin(GL_QUADS);

    for (int i = 0; i < terrainSize - 1; ++i)
    {
        for (int j = 0; j < terrainSize - 1; ++j)
        {
            glVertex3f(i, j, terrain[i][j]);
            glVertex3f(i + 1, j, terrain[i + 1][j]);
            glVertex3f(i + 1, j + 1, terrain[i + 1][j + 1]);
            glVertex3f(i, j + 1, terrain[i][j + 1]);
        }
    }
    glEnd();
}

void background()
{
    glBegin(GL_QUADS);
    glColor3f(0.53f - (insesitasEfekGerhana * 2.0f), 0.81f - (insesitasEfekGerhana * 2.0f), 0.98f - (insesitasEfekGerhana * 2.0f));
    glVertex2f(0, tinggiWindow);
    glVertex2f(lebarWindow, tinggiWindow);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(lebarWindow, 0);
    glVertex2f(0, 0);
    glEnd();
}

void rembulan()
{
    glPushMatrix();
    glTranslatef(150 + posisiBulanX, tinggiWindow - 150, 0.0f);
    glColor4f(0.0f, 0.0f, 0.0f, insesitasBulan);
    glVertex2f(0, 0);
    circle(0, 0, 50.0f, 100);
    glPopMatrix();
}

void matahari()
{
    glPushMatrix();
    glTranslatef(150, tinggiWindow - 150, 0.0f);
    glColor3f(1.0f, 0.8f, 0.0f);
    circle(0, 0, 50.0f, 100);
    glPopMatrix();
}

void corona()
{
    glPushMatrix();
    glTranslatef(150, tinggiWindow - 150, 0.0f);

    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 55.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 60.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 65.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 70.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 75.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 80.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 85.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 90.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 95.0f, 100);
    glColor4f(1.0f, 0.8f, 0.0f, 0.1f - (insesitasEfekGerhana / 4.0f));
    circle(0, 0, 100.0f, 100);

    glPopMatrix();
}

void awan()
{
    for (const auto &posisi : posisiAwan)
    {
        glPushMatrix();
        glTranslatef(posisi.x, posisi.y, 0.0f);

        glColor4f(1.0f - (insesitasEfekGerhana * 2.0f), 1.0f - (insesitasEfekGerhana * 2.0f), 1.0f - (insesitasEfekGerhana * 2.0f), 1.0f);
        circle(0, 0, 30.0f, 100);

        glTranslatef(40.0f, 0.0f, 0.0f);
        circle(0, 0, 30.0f, 100);

        glTranslatef(40.0f, 0.0f, 0.0f);
        circle(0, 0, 30.0f, 100);

        glTranslatef(40.0f, 0.0f, 0.0f);
        circle(0, 0, 30.0f, 100);

        glPopMatrix();
    }
}

void star()
{
    glPushMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, insesitasEfekGerhana);
    glTranslatef(200, 350, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, -100, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, 130, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, 150, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, -200, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, 50, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, 70, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, 20, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, -100, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(50, -20, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(20, 90, 0.0f);
    circle(0, 0, 1.0f, 100);
    glTranslatef(30, -10, 0.0f);
    circle(0, 0, 1.0f, 100);

    glPopMatrix();
}


void update(int value)
{
    posisiBulanX += 1.0f;

    // std::cout << posisiBulanX << "\n";

    if (posisiBulanX > 200.0f)
    {
        posisiBulanX = -200.0f; // reset posisi matahari
        sedangGerhana = !sedangGerhana;
        insesitasBulan = 1.0f;
    }
    else if (posisiBulanX >= 1.0f && posisiBulanX <= 100.0f)
    {
        insesitasEfekGerhana -= 0.0045f; // efek gerhana menghilang ketika bulan meninggalkan area matahari
    }
    else if ((posisiBulanX >= -100.0f && posisiBulanX < 1.0f) && sedangGerhana)
    {
        insesitasEfekGerhana += 0.0045f; // efek jika bulan sudah memasuki area matahari
    }
    else if(posisiBulanX > 100.0f && posisiBulanX <= 200.0f)
    {
        insesitasBulan -= 0.04f;
    }

    insesitasEfekGerhana = std::max(0.0f, std::min(insesitasEfekGerhana, 0.5f));

    for (auto &posisi : posisiAwan)
    {
        posisi.x += 0.5f;
        if (posisi.x > lebarWindow + 30)
        {
            posisi.x = -100.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(60, update, 0); // atur FPS
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glLoadIdentity();

    background();
    star();
    corona();
    matahari();
    if (sedangGerhana)
        rembulan();
    awan();

    glTranslatef(0, 0, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    glTranslatef(50, 00, 0.0f);
    gambarTerrain();
    
    text();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    lebarWindow = w;
    tinggiWindow = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    posisiAwan.push_back({-50.0f, tinggiWindow - 50.0f});
    posisiAwan.push_back({-150.0f, tinggiWindow - 200.0f});
    posisiAwan.push_back({-300.0f, tinggiWindow - 100.0f});
    posisiAwan.push_back({-450.0f, tinggiWindow - 250.0f});
    posisiAwan.push_back({-150.0f, tinggiWindow - 220.0f});

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(lebarWindow, tinggiWindow);
    glutCreateWindow("Animation vs Solar Eclipse");

    gluOrtho2D(0, terrainSize, 0, terrainSize);
    generateTerrain();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
