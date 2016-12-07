#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include "Particle.h"
#include "ParticleManager.h"
#include "Physics/LorenzAttractor.h"
#include "Physics/Newtonian.h"
#include "Emitters/Emitter.h"
#include "Emitters/FountainEmitter.h"

// Window size
int windowWidth = 1920;
int windowHeight = 1080;

// Time/Performance variables
float lastUpdateTime = 0;
int currentFPS = 0;
double averageFrameTime = 0;
float lastFPSUpdateTime = 0;
int framesSinceFPSUpdate = 0;

// Menu variables
int selectedParam = 0;

// Camera variables
float camDist = 100.0;
int mouseX, mouseY, prevMouseX, prevMouseY, mouseDraggedX, mouseDraggedY;
bool cameraMoving = false;

// GL_POINTS or GL_QUADS rendering
enum drawType {POINTS, QUADS, LINES};
enum drawType currentDrawType = POINTS;
bool alphaEnabled = false;

// Particle lifetime enable
bool particleLifetime = true;

// Emission rate per millisecond
int emissionRate = 1;

// Keep track of all the particles with a manager
ParticleManager *particleManager;

// Manage fixed number of emitters
Emitter *emitter1;
Emitter *emitter2;

// GLUT display function
void GLDisplay()
{
    // Move camera if appropriate
    glLoadIdentity();

    // Move camera depending on mouse dragging
    float camX = camDist * -sinf(mouseDraggedX * M_PI/180) * cosf(mouseDraggedY * M_PI/180),
          camY = camDist * -sinf(mouseDraggedY * M_PI/180),
          camZ = camDist * cosf(mouseDraggedX * M_PI/180) * cosf(mouseDraggedY * M_PI/180);

    gluLookAt(camX, camY, camZ,    // eye
              0.0, 0.0, 0.0,       // center
              0.0, 1.0, 0.0);      // up

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Info text
    glColor3f(255, 255, 255);
    std::string performanceText = "Frame Time: " + std::to_string(averageFrameTime) + "ms\n" +
                                  "FPS: " + std::to_string(currentFPS) + "\n" +
                                  "Particles: " + std::to_string(particleManager->getNumParticles());

    std::pair<std::string, double> currentParam = particleManager->getPhysics()->getParameter(selectedParam);
    std::string physicsText = "Current Physics Model: " + particleManager->getPhysics()->getName() + "\n" +
                              "Editing Parameter: " + std::get<0>(currentParam) +
                              " (" + std::to_string(std::get<1>(currentParam)) + ") [Arrow Keys]";

    std::tuple<unsigned char, unsigned char, unsigned char> c = emitter1->getColor();
    std::string emitterText = "Emitter 1 - Type: " + emitter1->getName() + " - " +
                              "Colour (" + std::to_string(std::get<0>(c)) + "," +
                              std::to_string(std::get<1>(c)) + "," + std::to_string(std::get<2>(c)) + ")\n";
    if (emitter2 == NULL) {
        emitterText += "Emitter 2 - None";
    } else {
        std::tuple<unsigned char, unsigned char, unsigned char> c2 = emitter2->getColor();
        emitterText += "Emitter 2 - Type: " + emitter2->getName() + " - " +
                       "Colour (" + std::to_string(std::get<0>(c2)) + "," +
                       std::to_string(std::get<1>(c2)) + "," + std::to_string(std::get<2>(c2)) + ")";
    }

    // Camera manipulation to print text in a fixed position for the GUI
    // Save old matrices and replace with identity matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Print text to the top left of the screen
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glRasterPos2i(10, windowHeight - 30);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)performanceText.c_str());

    // Bottom left for physics model
    glRasterPos2i(10, 50);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)physicsText.c_str());

    // Bottom right for emitter models
    glRasterPos2i(windowWidth - 400, 50);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)emitterText.c_str());

    // Restore the original projection and modelview matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // Draw a grid to represent the ground
    glBegin(GL_LINES);
        for (int i=0; i < 17; i++) {
            // X axis lines, first one is an indicator in red
            if (i == 0) {
                glColor3f(0.4, 0.1, 0.1);
            } else {
                glColor3f(0.4, 0.4, 0.4);
            }
            glVertex3f(i*5 - 40, 0, -40);
            glVertex3f(i*5 - 40 ,0, 40);

            // Y axis lines, first one is an indicator in blue
            if (i == 0) {
                glColor3f(0.1, 0.1, 0.4);
            } else {
                glColor3f(0.4, 0.4, 0.4);
            }
            glVertex3f(-40, 0, i*5 - 40);
            glVertex3f(40, 0, i*5 - 40);
        }
    glEnd();

    // Draw the particles
    switch (currentDrawType) {
        case POINTS:
            glPointSize(4.0);
            glBegin(GL_POINTS);
                // Draw all the particles from the particle manager as points
                for (int i = 0; i < particleManager->getNumParticles(); i++) {
                    Particle *currentParticle = particleManager->getParticle(i);
                    std::tuple<double, double, double> currentPos = currentParticle->getPos();
                    std::tuple<unsigned char, unsigned char, unsigned char> currentColor = currentParticle->getColor();
                    glColor3b(std::get<0>(currentColor), std::get<1>(currentColor), std::get<2>(currentColor));
                    glVertex3d(std::get<0>(currentPos), std::get<1>(currentPos), std::get<2>(currentPos));
                }
            glEnd();
            break;
        case QUADS:
            glBegin(GL_QUADS);
                // Draw all the particles from the particle manager as quads
                for (int i = 0; i < particleManager->getNumParticles(); i++) {
                    Particle *currentParticle = particleManager->getParticle(i);

                    std::tuple<unsigned char, unsigned char, unsigned char> currentColor = currentParticle->getColor();
                    // Enable or disable alpha blending for the quads
                    if (alphaEnabled) {
                        glColor4b(std::get<0>(currentColor), std::get<1>(currentColor), std::get<2>(currentColor), 70);
                    } else {
                        glColor3b(std::get<0>(currentColor), std::get<1>(currentColor), std::get<2>(currentColor));
                    }

                    // Get the position of the particle
                    std::tuple<double, double, double> currentPos = currentParticle->getPos();
                    double x = std::get<0>(currentPos);
                    double y = std::get<1>(currentPos);
                    double z = std::get<2>(currentPos);

                    // Draw vertexes
                    glVertex3d(x, y, z);
                    glVertex3d(x + 0.5, y, z);
                    glVertex3d(x + 0.5, y + 0.5, z);
                    glVertex3d(x, y + 0.5, z);
                }
            glEnd();
            break;
        case LINES:
            glBegin(GL_LINES);
                // Draw all the particles from the particle manager as lines
                for (int i = 0; i < particleManager->getNumParticles(); i++) {
                    Particle *currentParticle = particleManager->getParticle(i);

                    std::tuple<unsigned char, unsigned char, unsigned char> currentColor = currentParticle->getColor();
                    // Enable or disable alpha blending for the lines
                    if (alphaEnabled) {
                        glColor4b(std::get<0>(currentColor), std::get<1>(currentColor), std::get<2>(currentColor), 70);
                    } else {
                        glColor3b(std::get<0>(currentColor), std::get<1>(currentColor), std::get<2>(currentColor));
                    }

                    // Get the position of the particle
                    std::tuple<double, double, double> currentPos = currentParticle->getPos();
                    double x = std::get<0>(currentPos);
                    double y = std::get<1>(currentPos);
                    double z = std::get<2>(currentPos);

                    // Vertex for current position
                    glVertex3d(x, y, z);

                    // Get previous position of the particle
                    std::tuple<double, double, double> velocity = currentParticle->getVelocity();
                    std::tuple<double, double, double> prevVelocity = currentParticle->getPrevVelocity();
                    double prevX = std::get<0>(currentPos) - std::get<0>(velocity) - std::get<0>(prevVelocity);
                    double prevY = std::get<1>(currentPos) - std::get<1>(velocity) - std::get<1>(prevVelocity);
                    double prevZ = std::get<2>(currentPos) - std::get<2>(velocity) - std::get<2>(prevVelocity);

                    // Vertex for T-2 position
                    glVertex3d(prevX, prevY, prevZ);
                }
            glEnd();
            break;
    }

    // Swap double buffers
    glutSwapBuffers();
}

// GLUT idle function
void GLIdle()
{
    framesSinceFPSUpdate++;

    // Calculate time since last frame was generated
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    // Main simulation
    // Create emissionRate new particles per millisecond
    if (emitter2 == NULL) {
        for (int i = 0; i < emissionRate; i++) {
            emitter1->emitParticles(deltaTime);
        }
    } else {
        for (int i = 0; i < emissionRate; i++) {
            emitter1->emitParticles(round(deltaTime / 2));
            emitter2->emitParticles(round(deltaTime / 2));
        }
    }

    // Run simulation on each particle using current physics
    particleManager->timeStep(deltaTime);

    // Recalculate fps average and average frame time every 100ms
    if (currentTime - lastFPSUpdateTime > 100)
    {
        averageFrameTime = (currentTime - lastFPSUpdateTime) / framesSinceFPSUpdate;
        currentFPS = (int)round(1 / averageFrameTime  * 1000.0);
        lastFPSUpdateTime = currentTime;
        framesSinceFPSUpdate = 0;
    }

    // Call display function to draw the frame
    glutPostRedisplay();
}

// Handles keyboard input
void GLKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'r': // reset
            particleManager->getPhysics()->resetParameters();
            break;
        case '+':
        case '=':
            camDist--;
            break;
        case '-':
            camDist++;
            break;
        case 32: // space
            particleManager->clearParticles();
            break;
        case 27: // esc
            exit(0);
        default:
            break;
    }

    glutPostRedisplay();
}

// Handles special keys eg arrow
void GLKeyboardSpecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            particleManager->getPhysics()->setParameter(selectedParam, std::get<1>(
                    particleManager->getPhysics()->getParameter(selectedParam)) + 0.1);
            break;
        case GLUT_KEY_DOWN:
            particleManager->getPhysics()->setParameter(selectedParam, std::get<1>(
                    particleManager->getPhysics()->getParameter(selectedParam)) - 0.1);
            break;
        case GLUT_KEY_RIGHT:
            if (selectedParam + 1 < particleManager->getPhysics()->getNumEditableParameters()) {
                selectedParam++;
            } else {
                selectedParam = 0;
            }
            break;
        case GLUT_KEY_LEFT:
            if (selectedParam != 0) {
                selectedParam--;
            } else {
                selectedParam = particleManager->getPhysics()->getNumEditableParameters() - 1;
            }
            break;
        default:
            break;
    }
}

// Handles mouse clicks
void GLMouse(int button, int state, int x, int y) {
    // If camera is being dragged, set variable to be used in GLMotion function
    cameraMoving = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
}

// Handles mouse movement
void GLMotion(int x, int y) {
    // Keep track of previous and current mouse coordinates
    if (cameraMoving) {
        prevMouseX = mouseX;
        prevMouseY = mouseY;
        mouseX = x;
        mouseY = y;
        mouseDraggedX += prevMouseX - mouseX;
        mouseDraggedY += prevMouseY - mouseY;
    }
}

// Handles window reshape
void GLReshape(int width, int height)
{
    // Keep track of window width and height
    windowWidth = width;
    windowHeight = height;

    // Camera change to react to resize
    glClearColor(0, 0.05, 0.1, 1.0);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

// GLUT and OpenGL initialisation
void GLInit(int argc, char* argv[])
{
    glutInit(&argc, argv);

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Center the window on the screen depending on dimensions
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((screenWidth - windowWidth) / 2,
                           (screenHeight - windowHeight) / 2);

    // GLUT settings
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("COMP37111 Particles");

    // GLUT callback functions
    glutDisplayFunc(GLDisplay);
    glutIdleFunc(GLIdle);
    glutKeyboardFunc(GLKeyboard);
    glutSpecialFunc(GLKeyboardSpecial);
    glutReshapeFunc(GLReshape);
    glutMouseFunc(GLMouse);
    glutMotionFunc(GLMotion);

    // GL settings
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Handle the GLUT menu clicks
void GLMenu(int item) {
    switch (item) {
        case 1:
            exit(0);
        case 2:
            particleManager->setPhysics(new Newtonian());
            selectedParam = 0;
            break;
        case 3:
            particleManager->setPhysics(new LorenzAttractor());
            selectedParam = 0;
            break;
        case 4:
            currentDrawType = POINTS;
            break;
        case 5:
            currentDrawType = LINES;
            alphaEnabled = false;
            break;
        case 6:
            currentDrawType = LINES;
            alphaEnabled = true;
            break;
        case 7:
            currentDrawType = QUADS;
            alphaEnabled = false;
            break;
        case 8:
            currentDrawType = QUADS;
            alphaEnabled = true;
            break;
        case 9:
            delete emitter2;
            emitter2 = NULL;
            emitter1 = new FountainEmitter(particleManager, 0, 0, 0);
            break;
        case 10:
            emitter1->setPos(10, 0, 10);
            emitter2 = new FountainEmitter(particleManager, -10, 0, -10, 100, 0, 0);
            break;
        case 11:
            particleLifetime = !particleLifetime;
            particleManager->setLifetimeEnabled(particleLifetime);
            break;
        case 12:
            emissionRate = 1;
            break;
        case 13:
            emissionRate = 10;
            break;
        case 14:
            emissionRate = 100;
            break;
        default:
            break;
    }
}

// Creates the menu for the application
void createMenu() {
    int physicsSubmenu = glutCreateMenu(GLMenu);
    glutAddMenuEntry("Newtonian", 2);
    glutAddMenuEntry("Lorenz Attractor", 3);

    int particleSubmenu = glutCreateMenu(GLMenu);
    glutAddMenuEntry("GL_POINT", 4);
    glutAddMenuEntry("GL_LINES", 5);
    glutAddMenuEntry("GL_LINES Alpha", 6);
    glutAddMenuEntry("GL_QUADS", 7);
    glutAddMenuEntry("GL_QUADS Alpha", 8);

    int emitterSubmenu = glutCreateMenu(GLMenu);
    glutAddMenuEntry("Fountain", 9);
    glutAddMenuEntry("Fountain (x2)", 10);

    int numberSubmenu = glutCreateMenu(GLMenu);
    glutAddMenuEntry("Toggle Lifetime", 11);
    glutAddMenuEntry("1,000", 12);
    glutAddMenuEntry("10,000", 13);
    glutAddMenuEntry("100,000", 14);

    glutCreateMenu(GLMenu);
    glutAddSubMenu("Physics", physicsSubmenu);
    glutAddSubMenu("Particle", particleSubmenu);
    glutAddSubMenu("Emitter", emitterSubmenu);
    glutAddSubMenu("Number", numberSubmenu);
    glutAddMenuEntry("Exit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char *argv[])
{
    // Initialise OpenGL
    GLInit(argc, argv);

    // Create GLUT right click menu
    createMenu();

    // Create particle manager and physics
    Physics *newtonian = new Newtonian();
    particleManager = new ParticleManager(newtonian);

    // Create emitter
    emitter1 = new FountainEmitter(particleManager, 0, 0, 0, 0, 100, 0);

    // Hand over to GLUT main loop
    glutMainLoop();
}