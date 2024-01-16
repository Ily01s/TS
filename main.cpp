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


// Prototypes des fonctions pour la gestion d'OpenGL
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
    cube.buildCube(2.5f);  // Créer un cube d'une longueur de côté 1.0

    // Initialisation d'une simulation
    Simulation simulation;
    simulation.initialize();

    // ... [Votre code actuel pour la simulation] ...

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

        //dessin sphere
        // Obtenir les coordonnées du sommet 1 du cube
            const Triangle& triangle1 = cube.getFaces()[0].first;
            Vertex v1(triangle1.getVertex1().getX(), triangle1.getVertex1().getY(), triangle1.getVertex1().getZ(),1);
            Sphere mySphere(v1, 0.5f);
            mySphere.drawSphere(mySphere);


        SwapBuffers(hDC);// Échanger les tampons de l'affichage
        }
    }

    // Désactivation d'OpenGL et destruction de la fenêtre
    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);

    return msg.wParam;
}


/*int main() {

    // Création d'un maillage simple pour le test
    Mesh mesh;
    mesh.addTriangle(Triangle(Vertex(0.0f, 0.0f, 0.0f, 1),
                              Vertex(1.0f, 0.0f, 0.0f, 2),
                              Vertex(0.0f, 1.0f, 0.0f, 3)));
    mesh.addTriangle(Triangle(Vertex(0.0f, 1.0f, 0.0f, 3),
                              Vertex(1.0f, 0.0f, 0.0f, 2),
                              Vertex(1.0f, 1.0f, 0.0f, 4)));

    // Construction du graphe basé sur le maillage
    mesh.buildGraph();

    // Initialisation d'une simulation
    Simulation simulation;
    simulation.initialize();

    // Définir les identifiants des sommets de départ et d'arrivée pour la trajectoire
    int startVertexId = 1; // Supposons que 1 est l'ID de votre sommet de départ
    int endVertexId = 4;   // Supposons que 4 est l'ID de votre sommet d'arrivée

    // Exécution de l'algorithme de Dijkstra pour trouver la trajectoire
    simulation.runAlgorithm();

    // Affichage de la trajectoire calculée
    simulation.updateDisplay();

    // Affichage de la longueur totale de la trajectoire
    std::cout << "Longueur totale de la trajectoire: "
              << simulation.getTrajectoire().calculateLength() << " unités" << std::endl;

    return 0;
    std::cin.get();
}*/


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
