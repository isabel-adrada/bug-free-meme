#include "Escenario.h"
#include <iostream>

Escenario::Escenario() : fondoCargado(false) {
    // Inicializar límites por defecto
    limiteIzquierdo = 0.0f;
    limiteDerecho = 1366.0f;
    limiteSuperior = 0.0f;
    limiteInferior = 768.0f;

    // *** CAMBIO 1: Definir una altura de suelo adecuada ***
    alturaSuelo = 700.0f;  // Valor ajustado para que esté en la parte inferior

    // *** CAMBIO 2: Corregir la ruta de la imagen del fondo ***
    if (!texturaFondo.loadFromFile("escenarios/escenario1.png")) {
        std::cerr << "Error cargando imagen de fondo: escenarios/escenario1.png" << std::endl;
        // Intentar con una ruta alternativa
        if (!texturaFondo.loadFromFile("fondo.png")) {
            std::cerr << "Error cargando imagen de fondo alternativa: fondo.png" << std::endl;
        } else {
            fondoCargado = true;
        }
    } else {
        fondoCargado = true;
    }

    if (fondoCargado) {
        spriteFondo.setTexture(texturaFondo);

        // Obtener tamaño de la ventana (asumimos 1366x768 según el main.cpp)
        float ventanaAncho = 1366.0f;
        float ventanaAlto = 768.0f;

        // Obtener tamaño de la textura
        sf::Vector2u tamañoTextura = texturaFondo.getSize();

        // Calcular factores de escala para cada dimensión
        float escalaX = ventanaAncho / tamañoTextura.x;
        float escalaY = ventanaAlto / tamañoTextura.y;

        // Aplicar escala al sprite para que cubra exactamente la ventana
        spriteFondo.setScale(escalaX, escalaY);

        // Posicionar en la esquina superior izquierda
        spriteFondo.setPosition(0, 0);
    }

    // *** CAMBIO 3: Usar solo la plataforma que has definido ***
    //plataformas horizontales
    //columna 1
    agregarPlataforma(0.0f, 592.0f, 95.0f, 35.0f);
    agregarPlataforma(0.0f, 485.0f, 300.0f, 35.0f);
    agregarPlataforma(0.0f, 380.0f, 95.0f, 35.0f);
    agregarPlataforma(215.0f, 275.0f, 145.0f, 35.0f);
    agregarPlataforma(73.0f, 170.0f, 145.0f, 35.0f);

    //columna 2
    agregarPlataforma(325.0f, 592.0f, 190.0f, 35.0f);
    agregarPlataforma(515.0f, 485.0f, 190.0f, 35.0f);
    agregarPlataforma(365.0f, 380.0f, 190.0f, 35.0f);
    agregarPlataforma(560.0f, 275.0f, 45.0f, 35.0f);
    agregarPlataforma(360.0f, 170.0f, 145.0f, 35.0f);
    agregarPlataforma(505.0f, 140.0f, 145.0f, 35.0f);

    //columna 3
    agregarPlataforma(620.0f, 592.0f, 380.0f, 35.0f);
    agregarPlataforma(680.0f, 380.0f, 280.0f, 35.0f);
    agregarPlataforma(680.0f, 245.0f, 190.0f, 35.0f);
    agregarPlataforma(780.0f, 140.0f, 45.0f, 35.0f);

    //columna 4
    agregarPlataforma(1115.0f, 540.0f, 95.0f, 35.0f);
    agregarPlataforma(910.0f, 485.0f, 95.0f, 35.0f);
    agregarPlataforma(1115.0f, 425.0f, 95.0f, 35.0f);
    agregarPlataforma(960.0f, 345.0f, 95.0f, 35.0f);
    agregarPlataforma(1020.0f, 245.0f, 45.0f, 35.0f);
    agregarPlataforma(1165.0f, 245.0f, 45.0f, 35.0f);
    agregarPlataforma(1070.0f, 140.0f, 300.0f, 35.0f);







    //plataformas verticales
    //columna 2
    agregarPlataforma(472.0f, 522.0f, 40.0f, 110.0f);
    agregarPlataforma(505.0f, 70.0f, 40.0f, 105.0f);

    //columna 3
    agregarPlataforma(620.0f, 592.0f, 40.0f, 110.0f);
    agregarPlataforma(870.0f, 380.0f, 40.0f, 210.0f);
    agregarPlataforma(830.0f, 70.0f, 40.0f, 205.0f);

    //columna 4
    agregarPlataforma(1214.0f, 275.0f, 40.0f, 340.0f);




}

Escenario::~Escenario() {
    // Destructor vacío
}

void Escenario::agregarPlataforma(float x, float y, float ancho, float alto) {
    sf::RectangleShape plataforma(sf::Vector2f(ancho, alto));
    plataforma.setPosition(x, y);

    // Para plataformas visibles (durante pruebas):
    plataforma.setFillColor(sf::Color(139, 69, 19, 128));  // Marrón semi-transparente

    // Para plataformas invisibles (versión final):
    // plataforma.setFillColor(sf::Color::Transparent);

    plataformas.push_back(plataforma);
}

bool Escenario::verificarColisionPlataforma(const sf::FloatRect& objetoBounds) {
    for (const auto& plataforma : plataformas) {
        if (plataforma.getGlobalBounds().intersects(objetoBounds)) {
            return true;
        }
    }
    return false;
}

// *** CAMBIO 4: Modificar para manejar correctamente cuando no hay plataformas ***
float Escenario::getAlturaPlatformaEn(float posX) {
    // Recorremos todas las plataformas
    for (const auto& plataforma : plataformas) {
        sf::FloatRect bounds = plataforma.getGlobalBounds();

        // Si la posición X está dentro de la plataforma
        if (posX >= bounds.left && posX < bounds.left + bounds.width) {
            return bounds.top; // Devuelve la altura (coordenada Y) de la plataforma
        }
    }

    // Si no hay plataforma en esa posición, devolver la altura del suelo
    return alturaSuelo;
}

void Escenario::configurarLimites(float izq, float der, float sup, float inf) {
    limiteIzquierdo = izq;
    limiteDerecho = der;
    limiteSuperior = sup;
    limiteInferior = inf;
}

void Escenario::dibujar(sf::RenderWindow& ventana) {
    // Dibujar el fondo solo si se cargó correctamente
    if (fondoCargado) {
        ventana.draw(spriteFondo);
    }

    // Dibujar todas las plataformas
    for (const auto& plataforma : plataformas) {
        ventana.draw(plataforma);
    }
}