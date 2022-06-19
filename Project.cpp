#include<bits/stdc++.h>
#include<GL/glut.h>
#include<GL/gl.h>
using namespace std;
void DDA(int sx, int sy, int ex, int ey)
{
    glColor3f(1, 0, 0);
    double dx, dy, st, mx, my, cx, cy;
    dx = abs(ex - sx);
    dy = abs(ey - sy);
    st = dx > dy ? dx : dy;
    dx = ex - sx;
    dy = ey - sy;
    mx = dx / st;
    my = dy / st;
    cx = sx;
    cy = sy;
    glBegin(GL_POINTS);
    for (int i = 0;i <= st;i++) {
        double px = round(cx);
        double py = round(cy);
        glVertex2i(cx, cy);
        cx = cx + mx;
        cy = cy + my;
    }
    glEnd();
}
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
int cur_cloud_1;
int cur_cloud_2;
int cur_cloud_3;
int cnt = 0;
void star(int x, int y, int s) {
    if (abs(((cur_cloud_3 + x + y) / 10) % 3) < 2)star_rotated(x, y, s, 1, 1, 1);
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
int wind = 0;
void boat_base(int x, int y) {
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(x + 400, y + 10);
    glVertex2d(x + 320, y - 30);
    glVertex2d(x + 30, y - 30);
    glEnd();
}
void boat_glass(int x, int y) {
    y -= 120;
    x += 80;
    glColor3f(0, .2, .4);
    glBegin(GL_POLYGON);
    glVertex2d(x + 210, y - 2);
    glVertex2d(x + 304, y - 2);
    glVertex2d(x + 200, y + 64);
    glVertex2d(x + 190, y + 48);
    glEnd();
    glColor3f(0, .4, .7);
    glBegin(GL_POLYGON);
    glVertex2d(x + 220, y);
    glVertex2d(x + 300, y);
    glVertex2d(x + 210, y + 60);
    glVertex2d(x + 200, y + 40);
    glEnd();
}
void boat_back(int x, int y) {
    y -= 120;
    x += 80;
    glColor3f(.2, 0, .2);
    glBegin(GL_POLYGON);
    glVertex2d(x - 5, y - 5);
    glVertex2d(x - 5, y + 35);
    glVertex2d(x + 50, y + 55);
    glVertex2d(x + 50, y - 2);
    glEnd();
    glColor3f(.2, .3, .2);
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(x, y + 30);
    glVertex2d(x + 140, y + 50);
    glVertex2d(x + 145, y);
    glEnd();
    glColor3f(.2, .1, .1);
    glBegin(GL_POLYGON);
    glVertex2d(x + 30, y - 2);
    glVertex2d(x + 60, y + 45);
    glVertex2d(x + 150, y + 65);
    glVertex2d(x + 100, y - 2);
    glEnd();
}
void flag_pole(int x, int y, int h) {
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(x, y);
    glVertex2d(x + 7, y);
    glVertex2d(x + 60, y - 70 * h);
    glVertex2d(x + 53, y - 70 * h);
    glEnd();
}
void flag(int x, int y, int s, double r, double g, double b) {
    vector<pair<int, int> >P[2];
    for (int i = s * 10;i >= 0;i -= s, x -= 6 * s) {
        P[0].push_back({ x,y + i });
        P[1].push_back({ x + 10,y - i });
    }
    vector<int>w;
    reverse(P[1].begin(), P[1].end());
    for (int i = 0;i <= 5;i++)w.push_back(i);
    for (int i = 5;i >= 0;i--)w.push_back(i);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    int curw = (wind / 200) % 10;
    wind %= 100000;
    for (auto [x, y] : P[0]) {
        if (curw > 10)curw = 0;
        glVertex2f(x, y + 2 * w[curw]);
        curw++;
    }
    curw = (wind / 200) % 10 + 3;
    for (auto [x, y] : P[1]) {
        if (curw > 10)curw = 0;
        glVertex2f(x, y + 2 * w[curw]);
        curw++;
    }
    glEnd();

}
void boat_sailor(int x, int y) {
    x += 240;
    y -= 80;
    mid_point_circle_algo(x, y, 15, .3, .3, .6);
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(x + 18, y - 60);
    glVertex2d(x + 38, y - 60);
    glVertex2d(x + 29, y);
    glVertex2d(x + 19, y - 10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(x - 10, y - 60);
    glVertex2d(x + 20, y - 60);
    glVertex2d(x + 10, y - 10);
    glVertex2d(x - 20, y - 15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(x - 5, y - 18);
    glVertex2d(x + 25, y - 18);
    glVertex2d(x + 15, y - 10);
    glVertex2d(x - 15, y - 15);
    glEnd();
}
void boat(int x, int y) {
    //flag(x, y, 3, 0.6, 0, 0);
    y += ((wind / 200) % 10);
    flag_pole(x + 65 + 2, y + 10 + 2 * 2, 2);
    flag(75 + x, y - 20, 2, .5, 0, 0);
    boat_glass(x, y);
    boat_back(x, y);
    boat_sailor(x, y);
    flag_pole(x + 90 + 2, y + 2 * 2, 2);
    flag(100 + x, y - 30, 2, 1, 0, 0);
    boat_base(x + 80, y - 120);
}
vector<pair<int, int> >city_blocks, city_blocks_2, city_blocks_3, city_blocks_4, city_blocks_5;
int city = 0;
void city_landscape() {
    int total_w = -1600;
    if (city_blocks.empty())for (int i = 0;total_w < 64000;i++) {
        int cur_h = 300 + rand() % 250;
        int cur_w = 10 + rand() % 50;
        city_blocks.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    int time = city / 12;
    total_w = -1600 - time;
    for (auto [x, y] : city_blocks) {
        create_rectangle(total_w, -200, y, x, .1, 0, .8);
        total_w += x;
    }
}
void city_landscape_2() {
    int total_w = -1600;
    if (city_blocks_2.empty())for (int i = 0;total_w < 64000;i++) {
        int cur_h = 200 + rand() % 250;
        int cur_w = 10 + rand() % 40;
        city_blocks_2.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    int time = city / 6;
    total_w = -1600 - time;
    for (auto [x, y] : city_blocks_2) {
        create_rectangle(total_w, -220 + x / 10, y, x, .4, .1, .7);
        total_w += x;
    }
}
void city_landscape_3() {
    int total_w = -1600;
    if (city_blocks_3.empty())for (int i = 0;total_w < 64000;i++) {
        int cur_h = 120 + rand() % 100;
        int cur_w = 10 + rand() % 40;
        city_blocks_3.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    int time = city / 3;
    total_w = -1600 - time;
    for (auto [x, y] : city_blocks_3) {
        create_rectangle(total_w, -220 + rand() % 2, y, x, .2, .1, .5);
        total_w += x;
    }
}
void city_landscape_4() {
    int total_w = -1600;
    if (city_blocks_4.empty())for (int i = 0;total_w < 64000;i++) {
        int cur_h = 20 + rand() % 10;
        int cur_w = 200 + rand() % 40;
        city_blocks_4.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    int time = city;
    total_w = -1600 - time;
    for (auto [x, y] : city_blocks_4) {
        create_rectangle(total_w, -220 - y, y, x, 0, 0, 0);
        total_w += x;
    }
}
void city_landscape_5() {
    int total_w = -1600;
    if (city_blocks_5.empty())for (int i = 0;total_w < 64000;i++) {
        int cur_h = 20 + rand() % 10;
        int cur_w = 200 + rand() % 40;
        city_blocks_5.push_back({ cur_w,cur_h });
        total_w += cur_w;
    }
    int time = city;
    total_w = -1600 - time;
    for (auto [x, y] : city_blocks_5) {
        create_rectangle(total_w, -220, y, x, .1, .1, .1);
        total_w += x;
    }
}
void water() {
    double r = 54.0 / 256.0, g = 129.0 / 256.0, b = 157 / 256.0;
    double ir = 54.0 / 256.0, ig = 129.0 / 256.0, ib = 157 / 256.0;
    double tr = 144.0 / 256.0, tg = 198.0 / 256.0, tb = 218.0 / 256.0;
    for (int i = -1200;i < -200;i += 25, r += (tr - r) / 20.0, g += (tg - g) / 20.0, b += (tb - b) / 20.0) {
        create_rectangle(-1600, i, 25, 3200, r, g, b);
        if (abs(r - tr) < 0.01)r = ir;
        if (abs(b - tb) < 0.01)b = ib;
        if (abs(g - tg) < 0.01)g = ig;
    }
    for (int i = 0;i < 100;i++, tr += rand() % 2 == 0 ? .2 : -.2, tb += rand() % 2 == 0 ? .1 : -.1) {
        create_rectangle(-1600 + rand() % 3200, -1200 + rand() % 1000, 5, 30 * (rand() % 10), tr, tg, tb);
    }
}
void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    sky();
    moon(800, 800);
    plot_stars();
    cloud(-cur_cloud_1, 400, 0);
    cloud(-cur_cloud_2, 600, 0);
    cloud(-cur_cloud_3, 1000, 0);
    if (cur_cloud_1 > 1800)cur_cloud_1 = -1800;
    if (cur_cloud_2 > 1800)cur_cloud_2 = -1800;
    if (cur_cloud_3 > 1800)cur_cloud_3 = -1800;
    else if (cnt == 45) {
        cur_cloud_1++;
        cur_cloud_2++;
        cur_cloud_3++;
        cnt = 0;
    }
    cnt++;
    wind++;
    city++;
    city %= 64000 + 1600;
    city_landscape();
    city_landscape_2();
    water();
    city_landscape_3();
    city_landscape_4();
    city_landscape_5();
    glutPostRedisplay();
    glTranslated(tx, ty, 0);
    boat(-1500, -400);
    //create_rectangle(0 - ss / 2, 0 - ss / 2, 50 + ss, 50 + ss, gr, gg, gb);
    glPopMatrix();
    glFlush();
    glEnd();
}
void spe_key(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)tx -= 5;
    else if (key == GLUT_KEY_RIGHT)tx += 5;
    else if (key == GLUT_KEY_UP)ty += 5;
    else if (key == GLUT_KEY_DOWN)ty -= 5;
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
    srand(time(0));
    cur_cloud_1 = rand() % 3200 - 1600;
    cur_cloud_2 = rand() % 3200 - 1600;
    cur_cloud_3 = rand() % 3200 - 1600;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Half moon in cloud");
    init();
    gen_stars(50);
    glutDisplayFunc(Draw);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(my_keyboard);
    glutMainLoop();
    return 0;
}
