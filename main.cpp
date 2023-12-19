#include <GL/freeglut.h>
#include <cmath>

// untuk kontrol pergerakan bulan
float moonX = -1.0f;
float moonY = 0.5f;
float moonRadius = 0.15f;
float moonSpeed = 0.01f;
float totalTime = 0.0f;
float stopTime = 5.0f; // Waktu berhenti (dalam detik)
bool isMoonStopped = false; // penanda apakah bulan sedang berhenti


float stopStartTime = 0.0f; // Waktu dimulainya berhenti
float elapsedStopTime = 0.0f; // Waktu yang sudah berlalu ketika bulan berhenti

    // Menggambar stickman (orang)
void drawStickman() {
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    // Kepala
    float headRadius = 0.05f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = 2.0f * M_PI * i / 360.0f;
        float x = 0.7f + headRadius * cos(theta);
        float y = -0.7f + headRadius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Tubuh (garis)
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.7f + headRadius); // Ujung atas tubuh
    glVertex2f(0.7f, -0.9f); // Ujung bawah tubuh
    glEnd();

    // Tangan kiri (garis)
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.8f); // Pangkal tangan
    glVertex2f(0.6f, -0.8f); // Ujung tangan
    glEnd();

    // Tangan kanan (garis)
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.8f); // Pangkal tangan
    glVertex2f(0.8f, -0.8f); // Ujung tangan
    glEnd();

    // Kaki kiri (garis)
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.9f); // Pangkal kaki
    glVertex2f(0.6f, -1.0f); // Ujung kaki
    glEnd();

    // Kaki kanan (garis)
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.9f); // Pangkal kaki
    glVertex2f(0.8f, -1.0f); // Ujung kaki
    glEnd();
}
//menggambar/render objek
void drawObjects() {
    // Menggambar matahari
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f); // Warna kuning
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = 2.0f * M_PI * i / 360.0f;
        float x = -0.5f + 0.3f * cos(theta); // Letakkan matahari di sisi kiri
        float y = 0.5f + 0.3f * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();

    // Menggambar bulan
    glColor3f(0.5f, 0.5f, 0.5f); // Warna abu-abu
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = 2.0f * M_PI * i / 360.0f;
        float x = moonX + moonRadius * cos(theta);
        float y = moonY + moonRadius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    //render stickman
    drawStickman();
}

//bikin langit
void drawSky() {
    // Warna langit berubah segera saat bulan berada di tengah matahari
    glColor3f(0.0f, 0.5f, 1.0f);
    if (moonX >= -0.5f && moonX <= -0.2f) {
        glColor3f(0.0f, 0.0f, 0.2f); // Warna biru gelap saat bulan berada di tengah matahari
    }

    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

// tombol "Restart Game"
// FIXME: bulannya gak mau jalan kalo pencet tombol ini
void drawRestartButton() {
    glColor3f(0.0f, 1.0f, 0.0f); // Warna hijau
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f); // Pojok kiri bawah
    glVertex2f(-0.8f, -1.0f); // Pojok kanan bawah
    glVertex2f(-0.8f, -0.9f); // Pojok kanan atas
    glVertex2f(-1.0f, -0.9f); // Pojok kiri atas
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glRasterPos2f(-0.95f, -0.95f); // Posisi teks
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *)"Restart Game");
}


// untuk merender tampilan
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawSky();
    drawObjects();
    drawRestartButton();

    glutSwapBuffers();
}


// update posisi bulan
/*void updateMoon(int value) {
    if (totalTime >= 40.0f) {
        moonSpeed = 0.01f; // Setel kembali kecepatan bulan setelah gerhana selesai
    } else {
        if (!isMoonStopped) {
            moonX += moonSpeed; // Biarkan bulan terus bergerak
        }

        // Setelah bulan mencapai tengah matahari, berhenti
        if (moonX >= -0.5f && moonX <= -0.2f && !isMoonStopped) {
            isMoonStopped = true;
            moonSpeed = 0.0f; // Hentikan bulan saat berada di tengah matahari
        }

        // Reset posisi bulan setelah 5 detik berhenti
        if (isMoonStopped) {
           elapsedStopTime = totalTime - stopStartTime;
            if (elapsedStopTime >= stopTime) {
                isMoonStopped = false;
                moonSpeed = 0.01f; // Setel kembali kecepatan bulan setelah berhenti
            }
        }
    }

    // Hentikan bulan ketika mencapai ujung window
    if (moonX + moonRadius >= 1.0f) {
        moonSpeed = 0.0f;
    }

    totalTime += 0.1f; // Menggunakan interval 0.1 detik

    glutPostRedisplay();
    glutTimerFunc(100, updateMoon, 0);
}*/

void updateMoon(int value) {
    if (totalTime >= 40.0f) {
        moonSpeed = 0.01f; // Setel kembali kecepatan bulan setelah gerhana selesai
    } else {
        if (!isMoonStopped) {
            moonX += moonSpeed; // Biarkan bulan terus bergerak
        }

        // Setelah bulan mencapai tengah matahari, berhenti
        if (moonX >= -0.5f && moonX <= -0.2f && !isMoonStopped) {
            isMoonStopped = true;
            moonSpeed = 0.0f; // Hentikan bulan saat berada di tengah matahari
        }

        // Reset posisi bulan setelah 5 detik berhenti
        if (isMoonStopped) {
            elapsedStopTime = totalTime - stopStartTime;
            if (elapsedStopTime >= stopTime) {
                isMoonStopped = false;
                moonSpeed = 0.01f; // Setel kembali kecepatan bulan setelah berhenti
            }
        }
    }

    totalTime += 0.1f; // Menggunakan interval 0.1 detik

    glutPostRedisplay();
    glutTimerFunc(100, updateMoon, 0);
}

void mouse(int button, int state, int x, int y) {
    // Koordinat layar ke koordinat window OpenGL
    float winX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
    float winY = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Tombol kiri ditekan
        if (winX >= -1.0f && winX <= -0.8f && winY >= -1.0f && winY <= -0.9f) {
            // Klik pada tombol "Restart Game"
            moonX = -1.0f;
            isMoonStopped = false;
            totalTime = 0.0f;
            stopStartTime = 0.0f; // Inisialisasi ulang waktu berhenti
            elapsedStopTime = 0.0f; // Inisialisasi ulang waktu yang sudah berlalu ketika bulan berhenti
            // initialMoonSpeed = 0.01f; // Inisialisasi ulang kecepatan awal bulan
            moonSpeed = 0.1f; // Setel kembali kecepatan awal bulan
            glutTimerFunc(0, updateMoon, 0);
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Gerhana Matahari");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(0, updateMoon, 0);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
