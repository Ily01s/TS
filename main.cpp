//main.cpp
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Cube.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Simulation.h"
#include "Trajectoire.h"

#include <iostream>
#include <vector>

// Prototypes des fonctions pour la gestion d'OpenGL
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

// Variables globales pour l'animation
int startVertexId, endVertexId;
float animationSpeed = 0.1f;
int currentPointIndex = 0;
float progress = 0.0f;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    std::cout << "Enter the start vertex ID: ";
    std::cin >> startVertexId;
    std::cout << "Enter the end vertex ID: ";
    std::cin >> endVertexId;

    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1024,
                          1024,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    // Création d'un maillage simple pour le test
    Mesh mesh;
   // Création d'un cube
    Cube cube;
    cube.buildCube(mesh,2.5f);  // Créer un cube d'une longueur de côté 1.0

    mesh.buildGraph();
    mesh.verifyGraph();

    // Initialisation d'une simulation
    Simulation simulation;
    simulation.initialize();

   // Création d'une instance de Trajectoire
    Trajectoire traj;

    // Génération de la trajectoire en utilisant l'algorithme de Dijkstra
    traj.generateTrajectoryDijkstra(mesh, startVertexId, endVertexId);

    traj.visualize();

    Vertex v= mesh.getVertexById(startVertexId);

    //liste des point a parcourir
    std::vector<Vertex> p;
    p=traj.getPoints();


    DWORD lastTime = GetTickCount();  //compteur de temps


    // Boucle principale pour la fenêtre OpenGL
    while (!bQuit) {
        // Gestion des messages Windows
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            // Code de rendu OpenGL
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        // Configurer la projection et la vue
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)256 / (double)256, 1.0, 200.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


        if (currentPointIndex < p.size() - 1) {
            DWORD currentTime = GetTickCount();
            float timeDelta = (float)(currentTime - lastTime) / 1000.0f; // Temps écoulé en secondes
            lastTime = currentTime;

            Vertex& currentPoint = p[currentPointIndex];
            Vertex& nextPoint = p[currentPointIndex + 1];

            progress += timeDelta * animationSpeed;
            if (progress >= 1.0f) {
                currentPointIndex++;
                progress = 0.0f;
            } else {
                v.setX(currentPoint.getX() + (nextPoint.getX() - currentPoint.getX()) * progress);
                v.setY(currentPoint.getY() + (nextPoint.getY() - currentPoint.getY()) * progress);
                v.setZ(currentPoint.getZ() + (nextPoint.getZ() - currentPoint.getZ()) * progress);
            }
        }


        // Dessiner le cube
        //glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        for (const auto& face : cube.getFaces()) {
            // Accéder directement à chaque triangle dans la paire
            const Triangle& triangle1 = face.first;
            const Triangle& triangle2 = face.second;

            // Dessiner le premier triangle
            glVertex3f(triangle1.getVertex1().getX(), triangle1.getVertex1().getY(), triangle1.getVertex1().getZ());
            glVertex3f(triangle1.getVertex2().getX(), triangle1.getVertex2().getY(), triangle1.getVertex2().getZ());
            glVertex3f(triangle1.getVertex3().getX(), triangle1.getVertex3().getY(), triangle1.getVertex3().getZ());

            // Dessiner le second triangle
            glVertex3f(triangle2.getVertex1().getX(), triangle2.getVertex1().getY(), triangle2.getVertex1().getZ());
            glVertex3f(triangle2.getVertex2().getX(), triangle2.getVertex2().getY(), triangle2.getVertex2().getZ());
            glVertex3f(triangle2.getVertex3().getX(), triangle2.getVertex3().getY(), triangle2.getVertex3().getZ());
        }
        glEnd();

        // Dessiner les arêtes en bleu
         // Couleur bleue pour les arêtes
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 1.0f);
        for (const auto& face : cube.getFaces()) {
            // Dessiner les arêtes pour chaque triangle dans la paire
            const Triangle& triangle1 = face.first;
            const Triangle& triangle2 = face.second;

            // Arêtes du premier triangle
            glVertex3f(triangle1.getVertex1().getX(), triangle1.getVertex1().getY(), triangle1.getVertex1().getZ());
            glVertex3f(triangle1.getVertex2().getX(), triangle1.getVertex2().getY(), triangle1.getVertex2().getZ());

            glVertex3f(triangle1.getVertex2().getX(), triangle1.getVertex2().getY(), triangle1.getVertex2().getZ());
            glVertex3f(triangle1.getVertex3().getX(), triangle1.getVertex3().getY(), triangle1.getVertex3().getZ());

            glVertex3f(triangle1.getVertex3().getX(), triangle1.getVertex3().getY(), triangle1.getVertex3().getZ());
            glVertex3f(triangle1.getVertex1().getX(), triangle1.getVertex1().getY(), triangle1.getVertex1().getZ());

            // Arêtes du second triangle
            glVertex3f(triangle2.getVertex1().getX(), triangle2.getVertex1().getY(), triangle2.getVertex1().getZ());
            glVertex3f(triangle2.getVertex2().getX(), triangle2.getVertex2().getY(), triangle2.getVertex2().getZ());

            glVertex3f(triangle2.getVertex2().getX(), triangle2.getVertex2().getY(), triangle2.getVertex2().getZ());
            glVertex3f(triangle2.getVertex3().getX(), triangle2.getVertex3().getY(), triangle2.getVertex3().getZ());

            glVertex3f(triangle2.getVertex3().getX(), triangle2.getVertex3().getY(), triangle2.getVertex3().getZ());
            glVertex3f(triangle2.getVertex1().getX(), triangle2.getVertex1().getY(), triangle2.getVertex1().getZ());
        }
        glEnd();

            //dessin Point
            glDisable(GL_DEPTH_TEST);
            glColor3f(1.0f, 0.0f, 0.0f);
            glEnable(GL_POINT_SMOOTH);
            glPointSize(20.0f);
            glBegin(GL_POINTS);
            glVertex3f(v.getX(), v.getY(), v.getZ());
            glEnd();
            glEnable(GL_DEPTH_TEST);

        SwapBuffers(hDC);// Échanger les tampons de l'affichage
        }
    }

    // Désactivation d'OpenGL et destruction de la fenêtre
    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);

    return msg.wParam;
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
