/*!
 * \file    main.cpp
 * \brief   move a sprite with the keyboard (http://www.lucidarme.me/?p=6127)
 * \author  Philippe Lucidarme
 * Sprite del personaje y animacion: JULIAN SANCHEZ GARCIA 
 */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bala.h"
#include "Motor2D.h"
#include <vector>
#include <config.h>
#include "Jugador.h"

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
    int x=window.getSize().x/2;
    int y=window.getSize().y/2;
    
    // vector de balas 
    std::vector<Bala*> balas;
    // velocidad de bala
    int velx = 0;
    int vely = 0;
    
    // distancia a la dispara 
    float rangoDisparo = 1.5;  
    // centinela para conocer direccion de disparo
    int dispara = 0;
    // control direccion de disparo
    int direccionDisparo=Decha;
    
         
    sf::Clock reloj; // reloj para el disparo 
    sf::Clock relojSprite; // para la animacion PIERNAS personaje
    // reinicio el reloj en cada iteracion
    reloj.restart();
    relojSprite.restart();

       
    // ::: INICIO LOOP :::
    while (window.isOpen())
    {
        // considicion
        if(dispara !=0 ){
            int velx = 0;
            int vely = 0;
            // variables para disparo diagonal 
            /*if (leftFlag) velx = -3;
            else if(rightFlag) velx = 3;
            if (upFlag) vely = -3;
            else if(downFlag) vely = 3;*/
            // comprobamos direccion de disparo y cargamos posicion de textura
            switch (direccionDisparo){
                case Arriba:
                    /*cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    // separacion entre bolas en el disparo
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        // creamos una nueva bala y la metemos en el vector
                        balas.push_back(new Bala(x,y,velx,-3,rangoDisparo));
                        reloj.restart();
                    }*/
                break;
                
                case Abajo:
                    /*cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,velx,3,rangoDisparo));
                        reloj.restart();
                    }*/
                break;
                case Decha:
                    /*cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza)); 
                    cabeza.setScale(escalCab,escalCab);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,3,vely,rangoDisparo));
                        reloj.restart();
                    }*/
                break;
                case Izda:
                    /*cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Reflejo vertical
                    cabeza.setScale(-escalCab,escalCab);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,-3,vely,rangoDisparo));
                        reloj.restart();
                    }*/
                break;
            }
        }else{// posicion de las texturas Personaje segun movimiento
            
            
            
            
            
            
                // posicion del personaje NEUTRA
            
        }
        
        // animacion de los PASOS del PERSONAJE
        
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
                case  sf::Keyboard::Escape : window.close(); break;

                // MOV del personaje
                
                
                
                // DISPAROS. Condicion de direccion de disparo 
                case sf::Keyboard::Up: // Arriba
                    direccionDisparo=Arriba;
                    dispara++; 
                break;
                case sf::Keyboard::Down: // Abajo  
                    direccionDisparo=Abajo;
                    dispara++;
                 break;
                case sf::Keyboard::Left: // Letf
                    direccionDisparo=Izda;
                    dispara++;
                break;
                case sf::Keyboard::Right: // Arriba              
                    direccionDisparo=Decha;
                    dispara++;
                break;                    
                default : break;
                }
            }
              
            // Si no pulsamos ninguan tecla
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                // Liberamos teclas bool a false en todas direcciones
               
               
                // release DISPARO
                case sf::Keyboard::Up : // Up     
                    dispara--; break;                    
                case sf::Keyboard::Down:  // Down  
                    dispara--; break;
                case sf::Keyboard::Left:  // Izda  
                    dispara--; break;
                case sf::Keyboard::Right: // Dech
                    dispara--; break;
                default : break;
                
                }
            }

            // posicion NEUTRA PERSONAJE
            
        }

        // Actalizamos coordenadas
        

        // Controlar colisión con paredes
        /* if (x<0) 
            x=radioCabeza;
        if (x>(int)window.getSize().x) 
            x=window.getSize().x-radioCabeza;
        if (y<0) 
            y=radioCabeza;
        if (y>(int)window.getSize().y) 
            y=window.getSize().y-radioCabeza; */

        // actualizo posicion de la bala
        for(int i = 0 ; i<balas.size(); i++){
            if(balas.at(i)){
                balas.at(i)->actualiza(); // actualizo posicion de la bala
                if(balas.at(i)->destruirBala){
                    delete balas.at(i); // borramos la bala del vector
                    balas.erase(balas.begin()+i); // libero memoria de pos del vector
                }        
            }
        }
        
        // LIMPIAR VENTANA
        motor2D->limpiarVentana();
        // Fijamos las posiciones de los sprites
        
          
        // pintamos las balas
        for(int i = 0 ; i<balas.size(); i++){
            if(balas.at(i)){
                window.draw(*balas.at(i));
            }
        }
        
       
       
       //motor2D->pintarSprites(piernas);
       //motor2D->pintarSprites(cabeza);
        // Actualizar mostrar por pantalla
       motor2D->pintarVentana();
      
    }
    
    // Limpiamos la ventana y aplicamos un color de fondo 
    
    
   
    
    return 0;
}
