#pragma once

// Librerías estándar (STD)
#include <iostream>   // Manejo de entrada y salida.
#include <string>     // Manejo de cadenas de texto.
#include <sstream>    // Manipulación de flujos de entrada/salida.
#include <vector>     // Estructura de datos para listas dinámicas.
#include <thread>     // Soporte para concurrencia y programación multihilo.

// Librerías externas (Third Parties)
#include <SFML/Graphics.hpp>  // Biblioteca SFML para gráficos y manejo de ventanas.

// Punteros inteligentes personalizados del proyecto.
#include "../Include/Memory/TSharedPointer.h" // Puntero compartido para gestión de recursos.
#include "../Include/Memory/TWeakPointer.h" // Puntero débil para evitar referencias circulares.
#include "../Include/Memory/TStaticPtr.h" // Puntero estático para optimización.
#include "../Include/Memory/TUniquePtr.h" // Puntero único para garantizar propiedad exclusiva.


// Biblioteca ImGui (Interfaz gráfica de usuario).
#include "../Include/IMGUI/imgui.h"     // Biblioteca principal de ImGui.
#include "../Include/IMGUI/imgui-SFML.h"  // Integración de ImGui con SFML.

/**
 * @enum ShapeType
 * @brief Enumeración para representar los tipos de formas geométricas.
 *
 * Define los tipos de formas que se pueden crear en el motor gráfico.
 */
enum ShapeType {
    EMPTY = 0,    ///< Forma vacía, sin representación.
    CIRCLE = 1,   ///< Representa un círculo.
    RECTANGLE = 2,///< Representa un rectángulo.
    TRIANGLE = 3  ///< Representa un triángulo.
};

/**
 * @brief Macro para liberar punteros de forma segura.
 *
 * Esta macro verifica si el puntero no es nulo y luego lo libera,
 * estableciéndolo en nullptr para evitar accesos a memoria ya liberada.
 *
 * @param x Puntero a liberar.
 */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Macro para imprimir un mensaje de creación de recursos.
  *
  * Esta macro muestra un mensaje en la consola indicando si la creación de un
  * recurso fue exitosa o no, facilitando la depuración.
  *
  * @param classObj Nombre de la clase que llama a la macro.
  * @param method Nombre del método donde ocurre la creación.
  * @param state Estado de la creación del recurso.
  */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE" << ": " << state << "] \n";\
    std::cerr << os_.str();                                   \
}

  /**
   * @brief Macro para manejar errores fatales.
   *
   * Esta macro imprime un mensaje detallado en la consola cuando ocurre un error
   * en los parámetros recibidos, y termina la ejecución del programa.
   *
   * @param classObj Nombre de la clase donde ocurre el error.
   * @param method Nombre del método donde ocurre el error.
   * @param errorMSG Mensaje de error detallado.
   */
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << "  Error in data from params [" << errorMSG << "] \n";  \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
