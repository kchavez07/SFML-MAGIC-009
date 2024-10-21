#pragma once

// Librer�as est�ndar (STD)
#include <iostream>   // Manejo de entrada y salida.
#include <string>     // Manejo de cadenas de texto.
#include <sstream>    // Manipulaci�n de flujos de entrada/salida.
#include <vector>     // Estructura de datos para listas din�micas.
#include <thread>     // Soporte para concurrencia y programaci�n multihilo.

// Librer�as externas (Third Parties)
#include <SFML/Graphics.hpp>  // Biblioteca SFML para gr�ficos y manejo de ventanas.

// Punteros inteligentes personalizados del proyecto.
#include "../Include/Memory/TSharedPointer.h" // Puntero compartido para gesti�n de recursos.
#include "../Include/Memory/TWeakPointer.h" // Puntero d�bil para evitar referencias circulares.
#include "../Include/Memory/TStaticPtr.h" // Puntero est�tico para optimizaci�n.
#include "../Include/Memory/TUniquePtr.h" // Puntero �nico para garantizar propiedad exclusiva.


// Biblioteca ImGui (Interfaz gr�fica de usuario).
#include "../Include/IMGUI/imgui.h"     // Biblioteca principal de ImGui.
#include "../Include/IMGUI/imgui-SFML.h"  // Integraci�n de ImGui con SFML.

/**
 * @enum ShapeType
 * @brief Enumeraci�n para representar los tipos de formas geom�tricas.
 *
 * Define los tipos de formas que se pueden crear en el motor gr�fico.
 */
enum ShapeType {
    EMPTY = 0,    ///< Forma vac�a, sin representaci�n.
    CIRCLE = 1,   ///< Representa un c�rculo.
    RECTANGLE = 2,///< Representa un rect�ngulo.
    TRIANGLE = 3  ///< Representa un tri�ngulo.
};

/**
 * @brief Macro para liberar punteros de forma segura.
 *
 * Esta macro verifica si el puntero no es nulo y luego lo libera,
 * estableci�ndolo en nullptr para evitar accesos a memoria ya liberada.
 *
 * @param x Puntero a liberar.
 */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /**
  * @brief Macro para imprimir un mensaje de creaci�n de recursos.
  *
  * Esta macro muestra un mensaje en la consola indicando si la creaci�n de un
  * recurso fue exitosa o no, facilitando la depuraci�n.
  *
  * @param classObj Nombre de la clase que llama a la macro.
  * @param method Nombre del m�todo donde ocurre la creaci�n.
  * @param state Estado de la creaci�n del recurso.
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
   * en los par�metros recibidos, y termina la ejecuci�n del programa.
   *
   * @param classObj Nombre de la clase donde ocurre el error.
   * @param method Nombre del m�todo donde ocurre el error.
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
