#include <iostream>
#include <random>
using namespace std;

const int FILAS = 5;
const int COLUMNAS = 5;
const char OBJETO = 'O';
const char CASILLA = '-';
const string META = "META";
const int NUM_NUMEROS = 4; // Número de casillas adyacentes donde aparecerán números aleatorios
const int MAX_INTENTOS = 8; // Número máximo de intentos

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 10);

void limpiarNumerosAdyacentes(int fila, int columna, char cuadro[][COLUMNAS])
{
    int filasAdyacentes[NUM_NUMEROS] = {fila, fila, fila - 1, fila + 1};
    int columnasAdyacentes[NUM_NUMEROS] = {columna - 1, columna + 1, columna, columna};

    for (int i = 0; i < NUM_NUMEROS; i++)
    {
        int filaAdyacente = filasAdyacentes[i];
        int columnaAdyacente = columnasAdyacentes[i];

        if (filaAdyacente >= 0 && filaAdyacente < FILAS && columnaAdyacente >= 0 && columnaAdyacente < COLUMNAS)
        {
            cuadro[filaAdyacente][columnaAdyacente] = CASILLA;
        }
    }
}

void generarNumerosAleatorios(int fila, int columna, char cuadro[][COLUMNAS])
{
    int filasAdyacentes[NUM_NUMEROS] = {fila, fila, fila - 1, fila + 1};
    int columnasAdyacentes[NUM_NUMEROS] = {columna - 1, columna + 1, columna, columna};

    for (int i = 0; i < NUM_NUMEROS; i++)
    {
        int filaAdyacente = filasAdyacentes[i];
        int columnaAdyacente = columnasAdyacentes[i];

        if (filaAdyacente >= 0 && filaAdyacente < FILAS && columnaAdyacente >= 0 && columnaAdyacente < COLUMNAS)
        {
            cuadro[filaAdyacente][columnaAdyacente] = '0' + dis(gen);
        }
    }
}

void imprimirCuadro(char cuadro[][COLUMNAS])
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (i == 0 && j == 4)
            {
                cout << META << "\t";
            }
            else
            {
                cout << cuadro[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int calcularTotalSuperior(int filaObjeto, int columnaObjeto, char cuadro[][COLUMNAS])
{
    int sumaSuperior = 0;
    for (int i = 0; i < 3; i++)
    {
        int filaSuperior = filaObjeto - 1;
        int columnaSuperior = columnaObjeto - 1 + i;
        sumaSuperior += cuadro[filaSuperior][columnaSuperior] - '0';
    }

    int numeroDerecha = cuadro[filaObjeto][columnaObjeto + 1] - '0';

    return sumaSuperior * numeroDerecha;
}

int calcularTotalInferior(int filaObjeto, int columnaObjeto, char cuadro[][COLUMNAS])
{
    int sumaInferior = 0;
    for (int i = 0; i < 3; i++)
    {
        int filaInferior = filaObjeto + 1;
        int columnaInferior = columnaObjeto - 1 + i;
        sumaInferior += cuadro[filaInferior][columnaInferior] - '0';
    }

    int numeroIzquierda = cuadro[filaObjeto][columnaObjeto - 1] - '0';

    return sumaInferior * numeroIzquierda;
}

int main()
{
    // Crear una matriz de 5x5
    char cuadro[FILAS][COLUMNAS];

    // Inicializar el cuadro con casillas vacías
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            cuadro[i][j] = CASILLA;
        }
    }

    // Establecer la posición inicial del objeto
    int filaObjeto = 2;
    int columnaObjeto = 2;
    cuadro[filaObjeto][columnaObjeto] = OBJETO;

    // Generar números aleatorios en las casillas adyacentes
    generarNumerosAleatorios(filaObjeto, columnaObjeto, cuadro);

    // Imprimir el cuadro inicial
    imprimirCuadro(cuadro);

    int intentos = 0;

    while (true)
    {
        cout << "Intentos restantes: " << MAX_INTENTOS - intentos << std::endl;
        cout << "Ingrese la dirección para mover el objeto (w: arriba, s: abajo, a: izquierda, d: derecha): ";
        char direccion;
        cin >> direccion;

        // Actualizar la posición del objeto según la dirección ingresada
        int nuevaFilaObjeto = filaObjeto;
        int nuevaColumnaObjeto = columnaObjeto;

        if (direccion == 'w' && filaObjeto >= 2)
        {
            nuevaFilaObjeto -= 2;
        }
        else if (direccion == 's' && filaObjeto < FILAS - 2)
        {
            nuevaFilaObjeto += 2;
        }
        else if (direccion == 'a' && columnaObjeto >= 2)
        {
            nuevaColumnaObjeto -= 2;
        }
        else if (direccion == 'd' && columnaObjeto < COLUMNAS - 2)
        {
            nuevaColumnaObjeto += 2;
        }
        else
        {
            cout << "Dirección inválida. Intente nuevamente." << endl;
            continue;
        }

        // Calcular el total superior e inferior
        int totalSuperior = calcularTotalSuperior(nuevaFilaObjeto, nuevaColumnaObjeto, cuadro);
        int totalInferior = calcularTotalInferior(nuevaFilaObjeto, nuevaColumnaObjeto, cuadro);

        // Limpiar los números adyacentes a la posición anterior del objeto
        limpiarNumerosAdyacentes(filaObjeto, columnaObjeto, cuadro);

        // Actualizar la matriz con la nueva posición del objeto
        cuadro[filaObjeto][columnaObjeto] = CASILLA;
        cuadro[nuevaFilaObjeto][nuevaColumnaObjeto] = OBJETO;

        // Generar números aleatorios en las casillas adyacentes a la nueva posición del objeto
        generarNumerosAleatorios(nuevaFilaObjeto, nuevaColumnaObjeto, cuadro);

        // Imprimir el cuadro actualizado
        imprimirCuadro(cuadro);

        // Verificar si el objeto ha llegado a la meta
        if (nuevaFilaObjeto == 0 && nuevaColumnaObjeto == 4)
        {
            cout << "¡Felicidades! Has alcanzado la META." << endl;
            break;
        }

        // Calcular el resultado final
        int resultadoFinal = totalSuperior - totalInferior;
        cout << "Resultado final: " << resultadoFinal << endl;

        // Verificar si el jugador acierta
        int respuesta;
        cout << "Ingrese el resultado final: ";
        cin >> respuesta;

        if (respuesta == resultadoFinal)
        {
            // Actualizar la posición del objeto
            filaObjeto = nuevaFilaObjeto;
            columnaObjeto = nuevaColumnaObjeto;

            intentos++;
        }
        else
        {
            cout << "Respuesta incorrecta. El objeto vuelve a su posición anterior." << endl;

            // Restaurar la posición del objeto
            cuadro[filaObjeto][columnaObjeto] = CASILLA;
            cuadro[nuevaFilaObjeto][nuevaColumnaObjeto] = OBJETO;

            // Generar números aleatorios en las casillas adyacentes a la posición anterior del objeto
            generarNumerosAleatorios(filaObjeto, columnaObjeto, cuadro);

            // Imprimir el cuadro actualizado
            imprimirCuadro(cuadro);
        }

        // Verificar si el jugador ha agotado los intentos
        if (intentos >= MAX_INTENTOS)
        {
            cout << "Has agotado los intentos. ¡Perdiste la partida!" << endl;
            break;
        }
    }

    return 0;
}

