/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.h
 * Author: juli
 *
 * Created on 27 de abril de 2017, 19:28
 */
#include <SFML/Graphics.hpp>

#include "Motor2D.h"

#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
public:
    Jugador();
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    void mover(sf::Keyboard tecla);
    
private:
    int tamCabeza;
    int radioCabeza;
    int tamPiernas;
    int radioPiernas; 
    int ajustePierna;
    // para cambiar el tamaño de los sprites
    float escalCab;
    float escalPie;
    // variable para animar los FRAMES de piernas
    int contadorPasos;
    sf::Texture texture;
    
     // variables de posicion XY
    int x;
    int y;
    
    // avisadores de tecla pulsada MOV Jugador
    bool upFlag;
    bool downFlag;
    bool leftFlag;
    bool rightFlag;
    
    // ATRIBUTOS
    float SPRITE_SPEED;
    
}; 

#endif /* JUGADOR_H */

