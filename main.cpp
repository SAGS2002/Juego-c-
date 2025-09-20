#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <winuser.h>
#include <commctrl.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Necesario para std::shuffle

// Define los colores específicos
#define PURPLE_COLOR        RGB(140, 82, 255) // Morado (#8c52ff)
#define BLUE_COLOR          RGB(0, 0, 255)    // Azul puro
#define LIME_GREEN          RGB(0, 255, 0)    // Verde brillante para la respuesta correcta

// Colores para el gradiente de fondo
#define GRADIENT_START_COLOR PURPLE_COLOR
#define GRADIENT_END_COLOR   RGB(0, 0, 128)    // Un azul más oscuro para el final del gradiente

// Identificadores para los controles
#define IDC_START_BUTTON     1000
#define IDC_PROJECT_LABEL    1001 // "PROYECTO REALIZADO POR"
#define IDC_TEAM_LABEL       1002 // "TEAM MULTITECHNEW"
#define IDC_CREDITS_LABEL    1003 // Nombres de los integrantes×××
#define IDC_ENJOY_LABEL      1004 // "¡DISFRUTEN!"
#define IDC_50_50_BUTTON     1005 // Botón 50/50
#define IDC_BUTTON_HINT      1008 // Botón Hint
#define IDC_RETIRE_BUTTON    1009 // Botón de Retirarse
#define IDC_RESTART_BUTTON   1010 // Nuevo botón para reiniciar

// Declaración de handles y variables globales
HWND hMainWindow;
HWND hQuestionLabel;
HWND hOptionA;
HWND hOptionB;
HWND hOptionC;
HWND hOptionD;
HWND hChaosLabel; // Etiqueta del contador de Chaos
HWND h5050Button; // Botón 50/50
HWND hHintButton; // Botón Hint
HWND hRetireButton; // Botón de Retirarse
HWND hQuestionNumberLabel; // Etiqueta para el número de pregunta

// Controles de la pantalla de inicio
HWND hProjectLabel; // "PROYECTO REALIZADO POR"
HWND hTeamLabel;     // "TEAM MULTITECHNEW"
HWND hStartButton;
HWND hCreditsLabel; // Nombres de los integrantes
HWND hEnjoyLabel;     // Etiqueta para "¡DISFRUTEN!"
HWND hRestartButton; // Nuevo handle para el botón de reiniciar

int currentQuestionIndex = 0;
int correctAnswers = 0;
int totalChaos = 0; // Variable para el contador de Chaos
bool fiftyFiftyUsed = false; // Bandera para el uso del 50/50
bool hintUsed = false; // Bandera para el uso del Hint

const int totalQuestions = 20;

// Pinceles globales para los colores sólidos de los botones
HBRUSH hBrushCorrect = NULL;
HBRUSH hBrushBlue = NULL;

// Fuentes globales para el texto
HFONT hFontQuestion = NULL;
HFONT hFontOption = NULL;
HFONT hFontChaos = NULL;
HFONT hFontProjectLabel = NULL;
HFONT hFontTeamLabel = NULL;
HFONT hFontCredits = NULL;
HFONT hFontEnjoy = NULL;
HFONT hFontHelpers = NULL; // Nueva fuente para los botones de ayuda
HFONT hFontRestartButton = NULL; // Nueva fuente para el botón de reiniciar

// Estructura para almacenar preguntas, opciones y respuesta correcta
struct Question {
    std::string questionText;
    std::string optionA;
    std::string optionB;
    std::string optionC;
    std::string optionD;
    char correctOption;
    int chaosReward; // Recompensa de Chaos por pregunta
};

// Vector de preguntas
std::vector<Question> questions;
// Vector para mantener el orden aleatorio de las preguntas
std::vector<int> questionOrder;

// Prototipos de las funciones
std::string intToString(int num);
void initQuestions();
void LoadNextQuestion(HWND hWnd);
void Use5050();
void UseHint();
void ShowRetireResult(); // Nueva función para mostrar resultado al retirarse
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void ShowResult(bool won); // Modificada para indicar si se ganó o se perdió
void UpdateChaosDisplay();
void ShowGameControls();
void HideStartScreen();
void ShowStartScreen();
void ResetGameState();
void HideGameControls(); // Nueva función para reiniciar el estado del juego

// Función auxiliar para convertir un entero a string
std::string intToString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void initQuestions() {
    Question q;
    
    	
    
    // Pregunta 1
    q.questionText = "¿Cuál es la extensión de archivo estándar para un programa en C++?";
    q.optionA = ".cp"; q.optionB = ".cxxp"; q.optionC = ".exe"; q.optionD = ".cpp";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 2
    q.questionText = "¿Qué palabra clave se utiliza para declarar una variable constante en C++?";
    q.optionA = "define"; q.optionB = "constant"; q.optionC = "static"; q.optionD = "const";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 3
    q.questionText = "¿Qué símbolo se utiliza para terminar una instrucción en C++?";
    q.optionA = ","; q.optionB = "."; q.optionC = ":"; q.optionD = ";";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 4
    q.questionText = "¿Qué se usa para imprimir en la consola en C++?";
    q.optionA = "cout"; q.optionB = "echo"; q.optionC = "print"; q.optionD = "display";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 5
    q.questionText = "¿Qué biblioteca se debe incluir para usar cout?";
    q.optionA = "#include <stdio.h>"; q.optionB = "#include <string>"; q.optionC = " #include <iostream>"; q.optionD = "#include <conio.h>";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 6
    q.questionText = "¿Cuál es el tipo de dato para números enteros en C++?";
    q.optionA = "float"; q.optionB = "char"; q.optionC = "int"; q.optionD = "bool Ángel";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 7
    q.questionText = "¿Qué palabra clave se usa para definir una función en C++?";
    q.optionA = "procedure"; q.optionB = "void"; q.optionC = "define"; q.optionD = "func";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 8
    q.questionText = "¿Cuál es el operador de comparación de igualdad en C++?";
    q.optionA = "!="; q.optionB = "=="; q.optionC = "="; q.optionD = "===";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 9
    q.questionText = "¿Qué tipo de dato se usa para almacenar texto en C++?";
    q.optionA = "string"; q.optionB = "text"; q.optionC = "word"; q.optionD = "char";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 10
    q.questionText = "¿Qué estructura se usa para repetir instrucciones en C++?";
    q.optionA = "repeat"; q.optionB = "iterate"; q.optionC = "for"; q.optionD = "loop";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 11
    q.questionText = "¿Qué elemento químico tiene el símbolo 'O'?";
    q.optionA = "Oro"; q.optionB = "Oxígeno"; q.optionC = "Plata"; q.optionD = "Osmio";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 12
    q.questionText = "¿Quién fue el primer presidente de los Estados Unidos?";
    q.optionA = "Thomas Jefferson"; q.optionB = "Abraham Lincoln"; q.optionC = "George Washington"; q.optionD = "John Adams";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 13
    q.questionText = "¿Cuanto es 77 + 33?";
    q.optionA = "110"; q.optionB = "100"; q.optionC = "108"; q.optionD = "105";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 14
    q.questionText = "¿Cuál es el valor de x si 2x - 5 = 15?";
    q.optionA = "8"; q.optionB = "9"; q.optionC = "10"; q.optionD = "11";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 15
    q.questionText = "¿Cuál es el valor de x si 3x + 7 = 19?";
    q.optionA = "3"; q.optionB = "4"; q.optionC = "5"; q.optionD = "6";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 16
    q.questionText = "¿Quién inventó la bombilla?";
    q.optionA = "Nikola Tesla"; q.optionB = "Thomas Edison"; q.optionC = "Alexander Graham Bell"; q.optionD = "Benjamin Franklin";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 17
    q.questionText = "¿Qué instrumento se utiliza para medir la presión atmosférica?";
    q.optionA = "Termómetro"; q.optionB = "Higrómetro"; q.optionC = "Barómetro"; q.optionD = "Anemómetro";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 18
    q.questionText = "¿La costumbre jurídica es:?";
    q.optionA = "Una conducta contraria al derecho."; q.optionB = "Una relación jurídica.."; q.optionC = "Una ley especial."; q.optionD = "Una fuente próxima del derecho.";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 19
    q.questionText = "¿Una de las características de la normal jurídica es la: ?";
    q.optionA = "Generalidad."; q.optionB = "Autonomía."; q.optionC = "Unilateralidad."; q.optionD = "Interioridad";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);

    // Pregunta 20
    q.questionText = "¿Cuál es la capital de Australia?";
    q.optionA = "Sídney"; q.optionB = "Melbourne"; q.optionC = "Canberra"; q.optionD = "Brisbane";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
    
	// Pregunta 21
    q.questionText = "¿Cuál es el lenguaje de programación conocido por su uso en el desarrollo de Android?";
    q.optionA = "C++"; q.optionB = "Java"; q.optionC = "Python"; q.optionD = "JavaScript";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 22
    q.questionText = "¿Quién es considerado el padre de la computación?";
    q.optionA = "Alan Turing"; q.optionB = "Bill Gates"; q.optionC = "Steve Jobs"; q.optionD = "Charles Babbage";
    q.correctOption = 'D'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 23
    q.questionText = "¿Cuál es la sintaxis correcta para un bucle 'while' en C++?";
    q.optionA = "while { }"; q.optionB = "while (condition)"; q.optionC = "while: { }"; q.optionD = "loop (condition)";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 24
    q.questionText = "¿Qué operador se utiliza para la asignación de valor en C++?";
    q.optionA = "=="; q.optionB = "->"; q.optionC = "="; q.optionD = "<-";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 25
    q.questionText = "¿Cuál es el resultado de la siguiente operación: 10 % 3?";
    q.optionA = "3"; q.optionB = "1"; q.optionC = "0"; q.optionD = "2";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 26
    q.questionText = "¿Qué país tiene la Torre Eiffel?";
    q.optionA = "Italia"; q.optionB = "Alemania"; q.optionC = "Francia"; q.optionD = "España";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 27
    q.questionText = "¿Cuál es el valor de 'x' en la ecuación 5x - 10 = 20?";
    q.optionA = "4"; q.optionB = "5"; q.optionC = "6"; q.optionD = "8";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 28
    q.questionText = "¿Qué tipo de dato se utiliza para almacenar valores booleanos (verdadero/falso)?";
    q.optionA = "int"; q.optionB = "string"; q.optionC = "bool"; q.optionD = "char";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 29
    q.questionText = "¿Quién escribió el libro 'Cien años de soledad'?";
    q.optionA = "Julio Cortázar"; q.optionB = "Pablo Neruda"; q.optionC = "Gabriel García Márquez"; q.optionD = "Mario Vargas Llosa";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 30
    q.questionText = "¿Cuál es la raíz cuadrada de 144?";
    q.optionA = "10"; q.optionB = "12"; q.optionC = "14"; q.optionD = "16";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 31
    q.questionText = "¿Cuál es la capital de Italia?";
    q.optionA = "Milán"; q.optionB = "Venecia"; q.optionC = "Roma"; q.optionD = "Nápoles";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 32
    q.questionText = "¿Cuál es el resultado de (2 + 3) * 5 - 1?";
    q.optionA = "24"; q.optionB = "20"; q.optionC = "16"; q.optionD = "22";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 33
    q.questionText = "¿Qué significa 'POO' en programación?";
    q.optionA = "Programación de Objetos Orientados"; q.optionB = "Programación Orientada a Objetos"; q.optionC = "Planificación Organizada de Objetos"; q.optionD = "Programación de Operadores";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 34
    q.questionText = "¿Qué lenguaje de programación es 'padre' de C++?";
    q.optionA = "Java"; q.optionB = "C"; q.optionC = "Python"; q.optionD = "COBOL";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 35
    q.questionText = "¿En qué año ocurrió el alunizaje del Apolo 11?";
    q.optionA = "1969"; q.optionB = "1971"; q.optionC = "1965"; q.optionD = "1975";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 36
    q.questionText = "¿Qué operador se utiliza para la operación de módulo en C++?";
    q.optionA = "/"; q.optionB = "*"; q.optionC = "%"; q.optionD = "mod";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 37
    q.questionText = "¿Qué animal puede cambiar de color para camuflarse?";
    q.optionA = "León"; q.optionB = "Cebra"; q.optionC = "Camaleón"; q.optionD = "Tigre";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 38
    q.questionText = "¿Cuál es el resultado de 5 + 4 * 2?";
    q.optionA = "18"; q.optionB = "13"; q.optionC = "10"; q.optionD = "14";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 39
    q.questionText = "¿Qué operador se usa para la desreferencia de punteros en C++?";
    q.optionA = "&"; q.optionB = "->"; q.optionC = "*"; q.optionD = ".";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 40
    q.questionText = "¿Qué estructura de control se usa para tomar decisiones?";
    q.optionA = "for"; q.optionB = "while"; q.optionC = "switch"; q.optionD = "do-while";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 41
    q.questionText = "¿Qué significa el acrónimo IDE en el contexto de la programación?";
    q.optionA = "Internet Development Environment"; q.optionB = "Integrated Development Environment"; q.optionC = "Interface Definition Engine"; q.optionD = "Integrated Design Editor";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 42
    q.questionText = "¿Qué representa el acrónimo API?";
    q.optionA = "Application Programming Interface"; q.optionB = "Advanced Protocol Integration"; q.optionC = "Application Performance Index"; q.optionD = "Automated Program Interaction";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 43
    q.questionText = "¿Qué significa SQL?";
    q.optionA = "Simple Query Language"; q.optionB = "Structured Query Language"; q.optionC = "System Query Locator"; q.optionD = "Standard Question Language";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 44
    q.questionText = "¿Qué representa HTML?";
    q.optionA = "HyperText Markup Language"; q.optionB = "High-Level Text Manager Language"; q.optionC = "Hyperlink and Text Management"; q.optionD = "Home Tool Markup Language";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 45
    q.questionText = "¿Qué significa CSS en diseño web?";
    q.optionA = "Creative Style Sheets"; q.optionB = "Computer Style Syntax"; q.optionC = "Cascading Style Sheets"; q.optionD = "Custom Styling System";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 46
    q.questionText = "¿Qué significa URL?";
    q.optionA = "Uniform Resource Link"; q.optionB = "Universal Reference Locator"; q.optionC = "Uniform Resource Locator"; q.optionD = "Unified Resource Location";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 47
    q.questionText = "¿Qué significa HTTP?";
    q.optionA = "Hypertext Transfer Protocol"; q.optionB = "High-Tech Transfer Protocol"; q.optionC = "Hyperlink Text Protocol"; q.optionD = "Host Transfer Program";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 48
    q.questionText = "¿Qué representa el acrónimo GUI?";
    q.optionA = "General User Interface"; q.optionB = "Global User Instruction"; q.optionC = "Graphical User Interface"; q.optionD = "Gateway User Interaction";
    q.correctOption = 'C'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 49
    q.questionText = "¿Qué significa JSON?";
    q.optionA = "JavaScript Object Notation"; q.optionB = "Java Standard Object Network"; q.optionC = "Joint Service Object Notation"; q.optionD = "JavaScript Oriented Network";
    q.correctOption = 'A'; q.chaosReward = 1; questions.push_back(q);
	
	// Pregunta 50
    q.questionText = "¿Qué significa DBMS?";
    q.optionA = "Data Backup Management System"; q.optionB = "Database Management System"; q.optionC = "Dynamic Binary Machine System"; q.optionD = "Distributed Business Model Solution";
    q.correctOption = 'B'; q.chaosReward = 1; questions.push_back(q); 

    // Inicializar el vector de orden de preguntas
    for (int i = 0; i < 15; ++i) {
        questionOrder.push_back(i);
    }

    // 3. Baraja el vector UNA SOLA VEZ para obtener un orden aleatorio.
    std::random_shuffle(questionOrder.begin(), questionOrder.end());
    
}

// Función de entrada principal
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};

    srand(time(0)); // Inicializa la semilla del generador de números aleatorios
    initQuestions();

    // Creación de los pinceles
    hBrushCorrect = CreateSolidBrush(LIME_GREEN);
    hBrushBlue = CreateSolidBrush(BLUE_COLOR);

    // Creación de las fuentes
    hFontQuestion = CreateFont(40, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontOption = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontChaos = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontProjectLabel = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontTeamLabel = CreateFont(80, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Times New Roman"));
    hFontCredits = CreateFont(26, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontEnjoy = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontHelpers = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial"));
    hFontRestartButton = CreateFont(50, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial")); // Fuente más grande para el botón de reiniciar


    // Configuración de la clase de ventana
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = TEXT("myWindowClass");
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("Error al registrar la clase de ventana."), TEXT("Error"), MB_ICONERROR | MB_OK);
        return -1;
    }

    // Creación de la ventana principal con nuevas dimensiones
    hMainWindow = CreateWindow(TEXT("myWindowClass"), TEXT("Quiz Game"), WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
                                CW_USEDEFAULT, CW_USEDEFAULT, 1200, 900, NULL, NULL, hInst, NULL);

    if (!hMainWindow) {
        MessageBox(NULL, TEXT("Error al crear la ventana principal."), TEXT("Error"), MB_ICONERROR | MB_OK);
        return -1;
    }

    // Bucle de mensajes
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Liberar los recursos
    if (hBrushCorrect) DeleteObject(hBrushCorrect);
    if (hBrushBlue) DeleteObject(hBrushBlue);
    if (hFontQuestion) DeleteObject(hFontQuestion);
    if (hFontOption) DeleteObject(hFontOption);
    if (hFontChaos) DeleteObject(hFontChaos);
    if (hFontProjectLabel) DeleteObject(hFontProjectLabel);
    if (hFontTeamLabel) DeleteObject(hFontTeamLabel);
    if (hFontCredits) DeleteObject(hFontCredits);
    if (hFontEnjoy) DeleteObject(hFontEnjoy);
    if (hFontHelpers) DeleteObject(hFontHelpers);
    if (hFontRestartButton) DeleteObject(hFontRestartButton); // Liberar la nueva fuente

    return 0;
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE: {
            // Controles del juego (posiciones ajustadas para la nueva ventana)
            hQuestionNumberLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_RIGHT, 980, 20, 180, 30, hWnd, NULL, NULL, NULL);
            SendMessage(hQuestionNumberLabel, WM_SETFONT, (WPARAM)hFontChaos, TRUE);
            hQuestionLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_CENTER, 150, 80, 900, 120, hWnd, NULL, NULL, NULL);
            SendMessage(hQuestionLabel, WM_SETFONT, (WPARAM)hFontQuestion, TRUE);
            hOptionA = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 250, 900, 60, hWnd, (HMENU)1, NULL, NULL);
            SendMessage(hOptionA, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionB = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 340, 900, 60, hWnd, (HMENU)2, NULL, NULL);
            SendMessage(hOptionB, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionC = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 430, 900, 60, hWnd, (HMENU)3, NULL, NULL);
            SendMessage(hOptionC, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hOptionD = CreateWindow(TEXT("Button"), TEXT(""), WS_CHILD, 150, 520, 900, 60, hWnd, (HMENU)4, NULL, NULL);
            SendMessage(hOptionD, WM_SETFONT, (WPARAM)hFontOption, TRUE);
            hChaosLabel = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | SS_RIGHT, 980, 840, 180, 30, hWnd, NULL, NULL, NULL);
            SendMessage(hChaosLabel, WM_SETFONT, (WPARAM)hFontChaos, TRUE);
            h5050Button = CreateWindow(TEXT("Button"), TEXT("50/50"), WS_CHILD, 50, 800, 100, 40, hWnd, (HMENU)IDC_50_50_BUTTON, NULL, NULL);
            SendMessage(h5050Button, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);

            // Nuevos botones de ayuda
            hHintButton = CreateWindow(TEXT("Button"), TEXT("Localizar"), WS_CHILD, 170, 800, 100, 40, hWnd, (HMENU)IDC_BUTTON_HINT, NULL, NULL);
            SendMessage(hHintButton, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);

            hRetireButton = CreateWindow(TEXT("Button"), TEXT("Retirarse"), WS_CHILD, 290, 800, 100, 40, hWnd, (HMENU)IDC_RETIRE_BUTTON, NULL, NULL);
            SendMessage(hRetireButton, WM_SETFONT, (WPARAM)hFontHelpers, TRUE);


            // Controles de la pantalla de inicio (posiciones ajustadas)
            hProjectLabel = CreateWindow(TEXT("Static"), TEXT("PROYECTO REALIZADO POR"), WS_CHILD | SS_CENTER, 0, 180, 1200, 50, hWnd, (HMENU)IDC_PROJECT_LABEL, NULL, NULL);
            SendMessage(hProjectLabel, WM_SETFONT, (WPARAM)hFontProjectLabel, TRUE);

            hTeamLabel = CreateWindow(TEXT("Static"), TEXT("TEAM MULTITECHNEW"), WS_CHILD | SS_CENTER, 0, 250, 1200, 80, hWnd, (HMENU)IDC_TEAM_LABEL, NULL, NULL);
            SendMessage(hTeamLabel, WM_SETFONT, (WPARAM)hFontTeamLabel, TRUE);

            hStartButton = CreateWindow(TEXT("Button"), TEXT("INICIAR"), WS_CHILD, 475, 400, 250, 80, hWnd, (HMENU)IDC_START_BUTTON, NULL, NULL);
            SendMessage(hStartButton, WM_SETFONT, (WPARAM)hFontQuestion, TRUE);

            // Etiqueta "¡DISFRUTEN!"
            hEnjoyLabel = CreateWindow(TEXT("Static"), TEXT("¡DISFRUTEN!"), WS_CHILD | SS_CENTER, 0, 700, 1200, 60, hWnd, (HMENU)IDC_ENJOY_LABEL, NULL, NULL);
            SendMessage(hEnjoyLabel, WM_SETFONT, (WPARAM)hFontEnjoy, TRUE);

            // Botón de Reiniciar (inicialmente oculto y más grande/centrado)
            // Ancho: 400, Alto: 100. Centrado: (1200 - 400) / 2 = 400. Posición Y: 400 (justo debajo de TEAM MULTITECHNEW)
            hRestartButton = CreateWindow(TEXT("Button"), TEXT("¿DESEA REINICIAR?"), WS_CHILD, 300, 500, 600, 150, hWnd, (HMENU)IDC_RESTART_BUTTON, NULL, NULL);
            SendMessage(hRestartButton, WM_SETFONT, (WPARAM)hFontRestartButton, TRUE);
            ShowWindow(hRestartButton, SW_HIDE);

            HideGameControls(); // Ocultar controles del juego al inicio
            ShowStartScreen();

            break;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            // Dibujar el gradiente de fondo
            for (int i = 0; i < clientRect.bottom; ++i) {
                COLORREF currentColor;
                int r1 = GetRValue(GRADIENT_START_COLOR);
                int g1 = GetGValue(GRADIENT_START_COLOR);
                int b1 = GetBValue(GRADIENT_START_COLOR);

                int r2 = GetRValue(GRADIENT_END_COLOR);
                int g2 = GetGValue(GRADIENT_END_COLOR);
                int b2 = GetBValue(GRADIENT_END_COLOR);

                int r = r1 + (r2 - r1) * i / clientRect.bottom;
                int g = g1 + (g2 - g1) * i / clientRect.bottom;
                int b = b1 + (b2 - b1) * i / clientRect.bottom;

                currentColor = RGB(r, g, b);

                HBRUSH hBrushLine = CreateSolidBrush(currentColor);
                RECT lineRect = { clientRect.left, i, clientRect.right, i + 1 };
                FillRect(hdc, &lineRect, hBrushLine);
                DeleteObject(hBrushLine);
            }

            EndPaint(hWnd, &ps);
            break;
        }
        case WM_CTLCOLORSTATIC: {
            if ((HWND)lp == hQuestionLabel || (HWND)lp == hChaosLabel || 
        (HWND)lp == hProjectLabel || (HWND)lp == hTeamLabel || 
        (HWND)lp == hCreditsLabel || (HWND)lp == hEnjoyLabel ||
        (HWND)lp == hQuestionNumberLabel) { // <--- ¡Aquí está el cambio!
        SetBkMode((HDC)wp, TRANSPARENT);
        SetTextColor((HDC)wp, RGB(255, 255, 255)); // Asegura que el texto sea blanco
        return (LRESULT)GetStockObject(NULL_BRUSH); // Devuelve un pincel nulo para no pintar el fondo
    }

            break;
        }
        case WM_CTLCOLORBTN: {
            HDC hdc = (HDC)wp;
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            return (LRESULT)hBrushBlue;
        }
        case WM_COMMAND: {
            if (LOWORD(wp) == IDC_START_BUTTON) {
                HideStartScreen();
                ShowGameControls();
                LoadNextQuestion(hWnd);
            } else if (LOWORD(wp) == IDC_RESTART_BUTTON) {
                ResetGameState();
                HideGameControls(); // Ocultar los controles del juego
                ShowStartScreen(); // Mostrar la pantalla de inicio (con "TEAM MULTITECHNEW")
                ShowWindow(hRestartButton, SW_HIDE); // Ocultar el botón de reiniciar
            }
            else if (LOWORD(wp) == IDC_50_50_BUTTON) {
                if (!fiftyFiftyUsed) {
                    Use5050();
                    fiftyFiftyUsed = true;
                    EnableWindow(h5050Button, FALSE);
                    ShowWindow(h5050Button, SW_HIDE);
                }
            } else if (LOWORD(wp) == IDC_BUTTON_HINT) {
                if (!hintUsed) {
                    UseHint();
                    hintUsed = true;
                    EnableWindow(hHintButton, FALSE);
                    ShowWindow(hHintButton, SW_HIDE);
                }
            } else if (LOWORD(wp) == IDC_RETIRE_BUTTON) {
                ShowRetireResult();
            }
            else if (LOWORD(wp) >= 1 && LOWORD(wp) <= 4) {
                // Verifica si aún hay preguntas por mostrar
                if (currentQuestionIndex < questionOrder.size()) {
                    char selectedOption = ' ';
                    if (LOWORD(wp) == 1) { selectedOption = 'A'; }
                    else if (LOWORD(wp) == 2) { selectedOption = 'B'; }
                    else if (LOWORD(wp) == 3) { selectedOption = 'C'; }
                    else if (LOWORD(wp) == 4) { selectedOption = 'D'; }

                    // Usa el índice del vector de orden barajado para obtener la pregunta correcta
                    int actualQuestionIndex = questionOrder[currentQuestionIndex];

                    if (selectedOption != questions[actualQuestionIndex].correctOption) {
                        // *** MODIFICACIÓN PRINCIPAL ***
                        // Al perder, en lugar de un mensaje genérico, muestra la pregunta incorrecta y su respuesta correcta.
                        std::string message = "Pregunta incorrecta: " + questions[actualQuestionIndex].questionText + "\n";
                        message += "La respuesta correcta era: ";
                        switch (questions[actualQuestionIndex].correctOption) {
                            case 'A': message += questions[actualQuestionIndex].optionA; break;
                            case 'B': message += questions[actualQuestionIndex].optionB; break;
                            case 'C': message += questions[actualQuestionIndex].optionC; break;
                            case 'D': message += questions[actualQuestionIndex].optionD; break;
                        }
                        message += "\n\n";
                        message += "Juego terminado. Caramelos acumulado: " + intToString(totalChaos) + ".";
                        MessageBox(hMainWindow, message.c_str(), "Fin del Juego", MB_ICONERROR | MB_OK);

                        // Oculta todos los controles del juego y muestra el botón de reiniciar
                        HideGameControls();
                        ShowWindow(hRestartButton, SW_SHOW);
                        EnableWindow(hRestartButton, TRUE);

                        break;
                    } else {
                        correctAnswers++;
                        int chaosGained = questions[actualQuestionIndex].chaosReward;
                        totalChaos += chaosGained;

                        // Oculta temporalmente los controles del juego para la transición
                        HideGameControls(); // Oculta todos los controles para la transición

                        // Restablece el color de fondo de los botones a azul antes de la siguiente pregunta
                        SetClassLongPtr(hOptionA, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionB, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionC, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        SetClassLongPtr(hOptionD, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
                        InvalidateRect(hOptionA, NULL, TRUE);
                        InvalidateRect(hOptionB, NULL, TRUE);
                        InvalidateRect(hOptionC, NULL, TRUE);
                        InvalidateRect(hOptionD, NULL, TRUE);

                        Sleep(500); // Pequeña pausa para el efecto visual

                        currentQuestionIndex++; // Incrementa el índice solo si la respuesta fue correcta
                        LoadNextQuestion(hWnd);
                    }
                } else {
                    ShowResult(true);
                }
            }
            break;
        }
        case WM_CLOSE: {
            DestroyWindow(hWnd);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

// Carga la siguiente pregunta o muestra el resultado final
void LoadNextQuestion(HWND hWnd) {
    if (currentQuestionIndex < questionOrder.size()) {
        ShowGameControls(); // Asegúrate de que los controles del juego sean visibles

		// Actualizar la etiqueta con el número de la pregunta
        std::string questionNumText = "Pregunta: " + intToString(currentQuestionIndex + 1) + " /15";
        SetWindowText(hQuestionNumberLabel, questionNumText.c_str());
			
        // Obtiene el índice real de la pregunta del vector barajado
        int actualQuestionIndex = questionOrder[currentQuestionIndex];

        SetWindowTextA(hQuestionLabel, questions[actualQuestionIndex].questionText.c_str());
        SetWindowTextA(hOptionA, ("A) " + questions[actualQuestionIndex].optionA).c_str());
        SetWindowTextA(hOptionB, ("B) " + questions[actualQuestionIndex].optionB).c_str());
        SetWindowTextA(hOptionC, ("C) " + questions[actualQuestionIndex].optionC).c_str());
        SetWindowTextA(hOptionD, ("D) " + questions[actualQuestionIndex].optionD).c_str());

    } else {
        ShowResult(true);
    }
}

// Función para usar la ayuda 50/50
void Use5050() {
    int actualQuestionIndex = questionOrder[currentQuestionIndex];
    Question currentQ = questions[actualQuestionIndex];
    char correctOption = currentQ.correctOption;

    std::vector<HWND> incorrectButtons;
    if (correctOption != 'A') incorrectButtons.push_back(hOptionA);
    if (correctOption != 'B') incorrectButtons.push_back(hOptionB);
    if (correctOption != 'C') incorrectButtons.push_back(hOptionC);
    if (correctOption != 'D') incorrectButtons.push_back(hOptionD);

    if (incorrectButtons.size() >= 2) {
        int randomIndex1 = rand() % incorrectButtons.size();
        HWND buttonToHide1 = incorrectButtons[randomIndex1];
        incorrectButtons.erase(incorrectButtons.begin() + randomIndex1);

        int randomIndex2 = rand() % incorrectButtons.size();
        HWND buttonToHide2 = incorrectButtons[randomIndex2];

        ShowWindow(buttonToHide1, SW_HIDE);
        ShowWindow(buttonToHide2, SW_HIDE);
    } else if (incorrectButtons.size() == 1) {
        HWND buttonToHide1 = incorrectButtons[0];
        ShowWindow(buttonToHide1, SW_HIDE);

        std::vector<HWND> correctButtons;
        if (correctOption == 'A') correctButtons.push_back(hOptionA);
        if (correctOption == 'B') correctButtons.push_back(hOptionB);
        if (correctOption == 'C') correctButtons.push_back(hOptionC);
        if (correctOption == 'D') correctButtons.push_back(hOptionD);

        if (!correctButtons.empty()) {
            // Encuentra el botón correcto que no fue ocultado por la opción incorrecta si hay 2
            // Oculta uno de los correctos si solo hay una opción incorrecta
            ShowWindow(correctButtons[0], SW_HIDE);
        }
    }
}

// Función para usar la ayuda Hint
void UseHint() {
    int actualQuestionIndex = questionOrder[currentQuestionIndex];
    Question currentQ = questions[actualQuestionIndex];
    char correctOption = currentQ.correctOption;
    std::string hint = "Una de las opciones incorrectas es: ";

    std::vector<char> incorrectOptions;
    if (correctOption != 'A') incorrectOptions.push_back('A');
    if (correctOption != 'B') incorrectOptions.push_back('B');
    if (correctOption != 'C') incorrectOptions.push_back('C');
    if (correctOption != 'D') incorrectOptions.push_back('D');

    if (!incorrectOptions.empty()) {
        int randomIndex = rand() % incorrectOptions.size();
        hint += incorrectOptions[randomIndex];
        MessageBox(hMainWindow, hint.c_str(), "Ayuda Hint", MB_ICONINFORMATION | MB_OK);
    } else {
        MessageBox(hMainWindow, "No hay opciones incorrectas para mostrar como pista.", "Ayuda Hint", MB_ICONINFORMATION | MB_OK);
    }
}

// Función para retirarse y mostrar el resultado
void ShowRetireResult() {
    std::string message = "Has decidido retirarte.\n";
    message += "Has respondido correctamente " + intToString(correctAnswers) + " de " + intToString(currentQuestionIndex) + " preguntas.\n";
    message += "Caramelos acumulado: " + intToString(totalChaos) + ".";
    MessageBox(hMainWindow, message.c_str(), "Juego terminado", MB_OK);

    HideGameControls();
    ShowWindow(hRestartButton, SW_SHOW);
    EnableWindow(hRestartButton, TRUE);
}

// Oculta los controles de la pantalla de inicio
void HideStartScreen() {
    ShowWindow(hProjectLabel, SW_HIDE);
    ShowWindow(hTeamLabel, SW_HIDE);
    ShowWindow(hStartButton, SW_HIDE);
    ShowWindow(hCreditsLabel, SW_HIDE);
    ShowWindow(hEnjoyLabel, SW_HIDE);
}

// Oculta los controles del juego principal
void HideGameControls() {
    ShowWindow(hQuestionLabel, SW_HIDE);
    ShowWindow(hOptionA, SW_HIDE);
    ShowWindow(hOptionB, SW_HIDE);
    ShowWindow(hOptionC, SW_HIDE);
    ShowWindow(hOptionD, SW_HIDE);
    ShowWindow(hChaosLabel, SW_HIDE);
    ShowWindow(h5050Button, SW_HIDE);
    ShowWindow(hHintButton, SW_HIDE);
    ShowWindow(hRetireButton, SW_HIDE);
    ShowWindow(hQuestionNumberLabel, SW_HIDE); 	
}


// Muestra los controles del juego principal
void ShowGameControls() {
    ShowWindow(hQuestionLabel, SW_SHOW);
    ShowWindow(hOptionA, SW_SHOW);
    ShowWindow(hOptionB, SW_SHOW);
    ShowWindow(hOptionC, SW_SHOW);
    ShowWindow(hOptionD, SW_SHOW);
    UpdateChaosDisplay();
    ShowWindow(hChaosLabel, SW_SHOW);
    ShowWindow(hQuestionNumberLabel, SW_SHOW); 

    if (!fiftyFiftyUsed) {
        ShowWindow(h5050Button, SW_SHOW);
        EnableWindow(h5050Button, TRUE);
    } else {
        ShowWindow(h5050Button, SW_HIDE);
        EnableWindow(h5050Button, FALSE);
    }

    if (!hintUsed) {
        ShowWindow(hHintButton, SW_SHOW);
        EnableWindow(hHintButton, TRUE);
    } else {
        ShowWindow(hHintButton, SW_HIDE);
        EnableWindow(hHintButton, FALSE);
    }

    ShowWindow(hRetireButton, SW_SHOW);
    EnableWindow(hRetireButton, TRUE);

    ShowWindow(hRestartButton, SW_HIDE); // Asegurarse de que el botón de reiniciar esté oculto durante el juego
}

// Actualiza el texto del contador de Chaos
void UpdateChaosDisplay() {
    std::string chaosText = "Caramelos: " + intToString(totalChaos);
    SetWindowTextA(hChaosLabel, chaosText.c_str());
}

// Muestra el resultado final del juego
void ShowResult(bool won) {
    std::stringstream ss;
    if (won && correctAnswers == questions.size()) { // Asegurarse de que realmente respondió todas correctamente
        ss << "¡Felicidades! ¡Has ganado!\n";
        ss << "Has respondido correctamente " << correctAnswers << " de " << questions.size() << " preguntas.\n";
        ss << "Caramelos acumulado: " << totalChaos << ".";
    } else {
        ss << "Has perdido :C.\n"; // Si no ganó, es porque falló o no llegó al mínimo
        ss << "Necesitas responder todas las preguntas correctamente para ganar.\n";
        ss << "Has respondido correctamente " << correctAnswers << " de " << currentQuestionIndex << " preguntas.\n";
        ss << "Caramelos acumulado: " << totalChaos << ".";
    }
    std::string message = ss.str();
    MessageBox(hMainWindow, message.c_str(), "Fin del Juego", MB_OK);

    HideGameControls();
    ShowWindow(hRestartButton, SW_SHOW);
    EnableWindow(hRestartButton, TRUE);
}

// Nueva función para reiniciar el estado del juego
void ResetGameState() {
    currentQuestionIndex = 0;
    correctAnswers = 0;
    totalChaos = 0;
    fiftyFiftyUsed = false;
    hintUsed = false;

    // Volver a barajar las preguntas para un nuevo orden
    std::random_shuffle(questionOrder.begin(), questionOrder.end());

    // Restablecer el color de fondo de los botones a azul
    SetClassLongPtr(hOptionA, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
    SetClassLongPtr(hOptionB, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
    SetClassLongPtr(hOptionC, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
    SetClassLongPtr(hOptionD, GCLP_HBRBACKGROUND, (LONG_PTR)hBrushBlue);
    InvalidateRect(hOptionA, NULL, TRUE);
    InvalidateRect(hOptionB, NULL, TRUE);
    InvalidateRect(hOptionC, NULL, TRUE);
    InvalidateRect(hOptionD, NULL, TRUE);
}

// Función para inicializar y mostrar los controles de la pantalla de inicio
void ShowStartScreen() {
    ShowWindow(hProjectLabel, SW_SHOW);
    ShowWindow(hTeamLabel, SW_SHOW);
    ShowWindow(hStartButton, SW_SHOW);
    ShowWindow(hCreditsLabel, SW_SHOW); // Asegurarse de que los créditos estén visibles
    ShowWindow(hEnjoyLabel, SW_SHOW);

    // Ocultar todos los controles que no pertenecen a la pantalla de inicio
    ShowWindow(hChaosLabel, SW_HIDE);
    ShowWindow(h5050Button, SW_HIDE);
    ShowWindow(hHintButton, SW_HIDE);
    ShowWindow(hRetireButton, SW_HIDE);
    ShowWindow(hRestartButton, SW_HIDE);
}
