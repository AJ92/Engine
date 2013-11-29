//QT 4.x
//#include <QtGui/QApplication>

//QT 5.x
#include <QApplication>
#include "Debug/Ui/debugwindow.h"
#include "Graphics/freeglut/include/GL/freeglut.h"

void keyboard(unsigned char key, int x, int y);
void display(void);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugWindow w;
    w.show();

    w.add_log("Engine started.");


    glutInit(&argc, argv);
    glutCreateWindow("GLUT Test");
    glutKeyboardFunc(&keyboard);
    glutDisplayFunc(&display);
    glutMainLoop();
    
    return a.exec();
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case '\x1B':
      exit(EXIT_SUCCESS);
      break;
  }
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);

  glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
  glEnd();

  glFlush();
}
