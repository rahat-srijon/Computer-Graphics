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
    mid_point_circle_algo(x + 50, y + 50, 185, 0.150000, 0.000000, 0.650000);
}
void sky() {
    int cur_y = -200;
    double r = 0.5, g = 0, b = 1;
    for (int i = 0;cur_y < 1200;i += 50, b -= 0.05, r -= 0.05) {
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
    for (int i = 0;i < Stars.size();i++) {
        star(Stars[i].first.first, Stars[i].first.second, Stars[i].second);
    }
}
double tx = 0.0, ty = 0.0, gr = 0, gg = 0, gb = 0, ss = 0;
vector<pair<int, int> >city_blocks;
void city_landscape() {
    int total_w = -1600;
    if (city_blocks.empty())for (int i = 0;total_w < 1600;i++) {
        int cur_h = 300 + rand() % 250;
        int cur_w = 10 + rand() % 50;
        city_blocks.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    total_w = -1600;
    for (auto [x, y] : city_blocks) {
        create_rectangle(total_w, -200, y, x, .2, .1, .5);
        total_w += x;
    }
}
void water() {
    double r = 54.0 / 256.0, g = 129.0 / 256.0, b = 157 / 256.0;
    double tr = 144.0 / 256.0, tg = 198.0 / 256.0, tb = 218.0 / 256.0;
    for (int i = -1200;i < -200;i += 10, r = (tr - r) / 100.0, g += (tg - g) / 100.0, b += (tb - b) / 100.0) {
        create_rectangle(-1600, i, 50, 3200, r, g, b);
    }
    for (int i = 0;i < 50;i++, tr += rand() % 2 == 0 ? .2 : -.2, tb += rand() % 2 == 0 ? .1 : -.1) {
        create_rectangle(-1600 + rand() % 3200, -1200 + rand() % 1000, 20, 30 * (rand() % 10), tr, tg, tb);
    }
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

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
    city_landscape();
    water();
    glutPostRedisplay();
    glTranslated(tx, ty, 0);
    create_rectangle(0 - ss / 2, 0 - ss / 2, 50 + ss, 50 + ss, gr, gg, gb);
    glPopMatrix();
    glFlush();
    glEnd();
}
void spe_key(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)tx -= 50;
    else if (key == GLUT_KEY_RIGHT)tx += 50;
    else if (key == GLUT_KEY_UP)ty += 50;
    else if (key == GLUT_KEY_DOWN)ty -= 50;
    glutPostRedisplay();
}
void my_keyboard(unsigned char key, int x, int y) {
    if (key == 'q')gr += 0.1;
    else if (key == 'w')gg += 0.1;
    else if (key == 'e')gb += 0.1;
    else if (key == 'a')gr -= 0.1;
    else if (key == 's')gg -= 0.1;
    else if (key == 'd')gb -= 0.1;
    else if (key == 'z')ss += 10;
    else if (key == 'x')ss -= 10;
    gr = max(min(gr, 1.0), 0.0);
    gg = max(min(gg, 1.0), 0.0);
    gb = max(min(gb, 1.0), 0.0);
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("project");
    init();
    gen_stars(35);
    glutDisplayFunc(Draw);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
    return 0;
}
