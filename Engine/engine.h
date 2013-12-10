#ifndef ENGINE_H
#define ENGINE_H


class Engine
{
public:
    Engine();

    void initialize(int argc, char *argv[]);

    void keyboard(unsigned char key, int x, int y);

    void display();


};

#endif // ENGINE_H
