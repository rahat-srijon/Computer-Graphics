#include<bits/stdc++.h>
#include<GL/glut.h>
#include<GL/gl.h>
using namespace std;
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-1600.0, 1600.0, -1200.0, 1200.0, -1.0, 1.0);
}
void mid_point_circle_algo(double ctr_x, double ctr_y, double r, double red, double green, double blue)
{
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    int cur_x = 0;
    int cur_y = r;
    int P = 1 - r;
    while (cur_x <= cur_y)
    {
        glVertex2i(ctr_x + cur_x, ctr_y + cur_y);
        glVertex2i(ctr_x + cur_y, ctr_y + cur_x);
        glVertex2i(ctr_x + cur_x, ctr_y - cur_y);
        glVertex2i(ctr_x + cur_y, ctr_y - cur_x);
        glVertex2i(ctr_x - cur_x, ctr_y + cur_y);
        glVertex2i(ctr_x - cur_y, ctr_y + cur_x);
        glVertex2i(ctr_x - cur_x, ctr_y - cur_y);
        glVertex2i(ctr_x - cur_y, ctr_y - cur_x);
        if (P < 0)
        {
            P = P + 2 * (cur_x + 1) + 1;
        }
        else
        {
            cur_y--;
            P = P + 2 * (cur_x + 1) + 1 - 2 * (cur_y - 1);
        }
        cur_x++;
    }
    glEnd();
}
void create_rectangle(double x, double y, double h, double w, double r, double g, double b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glVertex2f(x + w, y + h);
    glVertex2f(x + w, y);
    glEnd();
}
void star_straight(int x, int y, int s, double r, double g, double b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x - s, y + s);
    glVertex2f(x, y + 5 * s);
    glVertex2f(x + s, y + s);
    glVertex2f(x + 5 * s, y);
    glVertex2f(x + s, y - s);
    glVertex2f(x, y - 5 * s);
    glVertex2f(x - s, y - s);
    glVertex2f(x - 5 * s, y);
    glEnd();
}
void star_rotated(int x, int y, int s, double r, double g, double b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x, y + s);
    glVertex2f(x + 4 * s, y + 4 * s);
    glVertex2f(x + s, y);
    glVertex2f(x + 4 * s, y - 4 * s);
    glVertex2f(x, y - s);
    glVertex2f(x - 4 * s, y - 4 * s);
    glVertex2f(x - s, y);
    glVertex2f(x - 4 * s, y + 4 * s);
    glEnd();
}
void cloud(int cx, int cy, int s)
{
    create_rectangle(cx - 125, cy - 160, 120 + s, 325 + s, .9, .9, .9);
    mid_point_circle_algo(cx, cy, 100 + s, .8, .8, .8);
    mid_point_circle_algo(cx + 150, cy - 40, 60 + s, .85, .85, .85);
    mid_point_circle_algo(cx - 125, cy - 80, 80 + s, .95, .95, .95);
    mid_point_circle_algo(cx + 200, cy - 100, 60 + s, .85, .85, .95);
}
int cur_cloud_1 = -900;
int cur_cloud_2 = -200;
int cur_cloud_3 = 600;
int cnt = 0;
void star(int x, int y, int s) {
    if (((cur_cloud_3 + x + y) / 10) % 3 < 2)star_rotated(x, y, s, 1, 1, 1);
    else star_straight(x, y, s, 1, 1, 1);
}
void moon(int x, int y) {
    mid_point_circle_algo(x, y, 200, 1, 1, 1);
    mid_point_circle_algo(x + 50, y + 50, 185, 0.430000, 0.000000, 0.650000);
}
void sky() {
    int cur_y = -200;
    double r = 0.5, g = 0, b = 1;
    for (int i = 0;cur_y < 1200;i += 50, b -= 0.05, r -= 0.01) {
        create_rectangle(-1600, cur_y, i, 3200, r, g, b);
        cur_y += i;
    }
}
vector<pair<pair<int, int>, int> >Stars;
void gen_stars(int n) {
    for (int i = 0; i < n;i++) {
        int x = -1600 + rand() % 3200;
        int y = 500 + rand() % 700;
        Stars.push_back({ {x, y}, 2 + rand() % 5 });
    }
}
void plot_stars() {
    for (auto [x, y] : Stars) {
        star(x.first, x.second, y);
    }
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    moon(800, 800);
    plot_stars();
    cloud(cur_cloud_1, 400, 0);
    cloud(cur_cloud_2, 600, 0);
    cloud(cur_cloud_3, 1200, 0);
    if (cur_cloud_1 > 1800)cur_cloud_1 = -1800;
    if (cur_cloud_2 > 1800)cur_cloud_2 = -1800;
    if (cur_cloud_3 > 1800)cur_cloud_3 = -1800;
    else if (cnt == 75) {
        cur_cloud_1++;
        cur_cloud_2++;
        cur_cloud_3++;
        cnt = 0;
    }
    cnt++;
    glutPostRedisplay();
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Half moon in cloud");
    init();
    gen_stars(35);
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}

