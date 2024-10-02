#pragma once

/*
 * Prerequisites.h
 * Este archivo incluye las bibliotecas y configuraciones esenciales que se usarán en todo el proyecto.
 * Aquí también definimos algunos tipos de formas que el motor gráfico puede manejar (como círculos y triángulos)
 * y tenemos un par de macros para manejar errores y recursos de forma segura.
 */

 // Bibliotecas estándar (incluyen utilidades como manejo de cadenas, vectores y más).
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

// Librerías externas para gráficos y gestión de memoria.
#include <SFML/Graphics.hpp>
#include "../Include/Memory/TWeakPointer.h"
#include "../Include/Memory/TSharedPointer.h"
#include "../Include/Memory/TStaticPtr.h"
#include "../Include/Memory/TUniquePtr.h"

// Enumeración para los tipos de formas que se pueden crear.
enum ShapeType
{
    EMPTY = 0,    // Un tipo de forma vacía, por defecto.
    CIRCLE = 1,   // Representa un círculo.
    RECTANGLE = 2,// Representa un rectángulo.
    TRIANGLE = 3, // Representa un triángulo.
};

// ¡Hora de las macros! Estos son atajos para manejar ciertas operaciones de forma rápida y segura.

// Esta macro nos ayuda a liberar memoria de forma segura.
// Si el puntero que le pasas no es nulo, lo libera y lo deja en nullptr.
// Esto previene errores por intentar usar punteros que ya no existen.
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

// Macro para imprimir un mensaje indicando el estado de un recurso (por ejemplo, si se creó correctamente).
// Le pasas el nombre de la clase, el método y el estado del recurso, y listo, aparece un mensaje en la consola.
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

// ¿Algo salió mal? Esta macro imprime un error detallado y cierra el programa.
// Solo tienes que darle el nombre de la clase, el método donde ocurrió y una descripción del error.
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error en los datos de los parámetros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
