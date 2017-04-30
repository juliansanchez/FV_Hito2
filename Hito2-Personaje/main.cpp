/*!
 * \file    main.cpp
 * \brief   move a sprite with the keyboard (http://www.lucidarme.me/?p=6127)
 * \author  Philippe Lucidarme
 * Sprite del personaje y animacion: JULIAN SANCHEZ GARCIA 
 */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor2D.h"
#include "Jugador.h"
#include "config.h"

// Sprite speed (high values = high speed)
#define SPRITE_SPEED  2
using namespace std;


int main()
{     
    // ::: VENTANA PRINCIPAL :::
    /* Por recomendacion, conviene crear el objeto en SFML
     y acceder a su posicion de memoria a través de la clase
     motor 2D, creando una única instancia de ella
     siguiendo el patron singleton */
    
    sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), "Hito 1: animacion personaje");
    // Enable vertical sync. (vsync)
    window.setVerticalSyncEnabled (true);
    window.setFramerateLimit(60);
    // When a key is pressed, sf::Event::KeyPressed will be true only once
    window.setKeyRepeatEnabled(false);

    
    // creamos el obj Motor2D para crear ventana de juego
    Motor2D*motor2D = Motor2D::Instance();
    // fijamos la ventana de juego
    motor2D->setWindow(&window);

    // variables de posicion XY
    int x = window.getSize().x/2;
    int y = window.getSize().y/2;

    Jugador *player = new Jugador(x, y);  
         
    sf::Clock reloj; // reloj para el disparo 
    sf::Clock relojSprite; // para la animacion PIERNAS personaje
    // reinicio el reloj en cada iteracion
    reloj.restart();
    relojSprite.restart();
       
    // ::: INICIO LOOP :::
    while (window.isOpen())
    {
        // LIMPIAR VENTANA
        motor2D->limpiarVentana();
        // Proceso de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar ventana
            if (event.type == sf::Event::Closed) 
                window.close();

            // Si pulsamos una tecla
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                // Para cerrar la ventana con ESC
                case sf::Keyboard::Escape: window.close(); break;
                case sf::Keyboard::W: player->setFlagW(true); break;
                case sf::Keyboard::A: player->setFlagA(true); break;
                case sf::Keyboard::S: player->setFlagS(true); break;
                case sf::Keyboard::D: player->setFlagD(true); break;
                
                // DISPAROS. Condicion de direccion de disparo 
                case sf::Keyboard::Up: player->setDirDisparo(0); break;
                case sf::Keyboard::Down: player->setDirDisparo(1); break;
                case sf::Keyboard::Left: player->setDirDisparo(2); break;
                case sf::Keyboard::Right: player->setDirDisparo(3); break;                   
                }
            }
              
            // Si no pulsamos ninguan tecla
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: player->setFlagW(false); break;
                    case sf::Keyboard::A: player->setFlagA(false); break;
                    case sf::Keyboard::S: player->setFlagS(false); break;
                    case sf::Keyboard::D: player->setFlagD(false); break;
                                        
                // Liberamos teclas bool a false en todas direcciones                             
                // release DISPARO
                    case sf::Keyboard::Up : player->decrementarBala(); break;                    
                    case sf::Keyboard::Down: player->decrementarBala(); break; 
                    case sf::Keyboard::Left:  player->decrementarBala(); break;  
                    case sf::Keyboard::Right: player->decrementarBala(); break;              
                }
            }
            
        }

       // actualizamos posiciones de los sprites
       player->mover(relojSprite);
       player->disparar(reloj);
        // Actualizar mostrar por pantalla
       motor2D->pintarVentana();
      
    }

    return 0;
}