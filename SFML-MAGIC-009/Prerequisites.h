#pragma once

/*
 * Prerequisites.h
 * Este archivo incluye las bibliotecas y configuraciones esenciales que se usar�n en todo el proyecto.
 * Aqu� tambi�n definimos algunos tipos de formas que el motor gr�fico puede manejar (como c�rculos y tri�ngulos)
 * y tenemos un par de macros para manejar errores y recursos de forma segura.
 */

 // Bibliotecas est�ndar (incluyen utilidades como manejo de cadenas, vectores y m�s).
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

// Librer�as externas para gr�ficos y gesti�n de memoria.
#include <SFML/Graphics.hpp>
#include "../Include/Memory/TWeakPointer.h"
#include "../Include/Memory/TSharedPointer.h"
#include "../Include/Memory/TStaticPtr.h"
#include "../Include/Memory/TUniquePtr.h"

// Enumeraci�n para los tipos de formas que se pueden crear.
enum ShapeType
{
    EMPTY = 0,    // Un tipo de forma vac�a, por defecto.
    CIRCLE = 1,   // Representa un c�rculo.
    RECTANGLE = 2,// Representa un rect�ngulo.
    TRIANGLE = 3, // Representa un tri�ngulo.
};

// �Hora de las macros! Estos son atajos para manejar ciertas operaciones de forma r�pida y segura.

// Esta macro nos ayuda a liberar memoria de forma segura.
// Si el puntero que le pasas no es nulo, lo libera y lo deja en nullptr.
// Esto previene errores por intentar usar punteros que ya no existen.
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

// Macro para imprimir un mensaje indicando el estado de un recurso (por ejemplo, si se cre� correctamente).
// Le pasas el nombre de la clase, el m�todo y el estado del recurso, y listo, aparece un mensaje en la consola.
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

// �Algo sali� mal? Esta macro imprime un error detallado y cierra el programa.
// Solo tienes que darle el nombre de la clase, el m�todo donde ocurri� y una descripci�n del error.
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error en los datos de los par�metros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
