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
#include <iostream>
#include "Bala.h"
#include <vector>

#ifndef JUGADOR_H
#define JUGADOR_H

enum dirccionDisparo{
    Arriba = 0,
    Abajo  = 1,
    Izda = 2,
    Decha = 3,
};

class Jugador {
public:
    Jugador(int x, int y);
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    void mover(sf::Clock relojSprite);
    void setFlagW(bool f);
    void setFlagA(bool f);
    void setFlagS(bool f);
    void setFlagD(bool f);
    void disparar();
    void setDirDisparo(int e);
    void decrementarBala();
    
    
private:
    int tamSprite;
    int radioSprite;

    int ajustePierna;
    int x; //POSX
    int y;//POSY
    // para cambiar el tamaño de los sprites
    float escala;
    // variable para animar los FRAMES de piernas
    int contadorPasos;
    sf::Sprite cabeza;
    sf::Sprite piernas;
    sf::Texture texture;
    
    // avisadores de tecla pulsada MOV Jugador
    bool upFlag;
    bool downFlag;
    bool leftFlag;
    bool rightFlag;
    
    // ATRIBUTOS
    float SPRITE_SPEED;
    void animacioncaminar(sf::Clock relojSprite);
    void actualizarSprite ();
    void pintar();
    void crearbala();
    // variable y metodo para controlar el tiempo de disparo
    sf::Clock clock;
    sf::Clock getReloj();
    
    
    std::vector<Bala*> balas;
    int velx;
    int vely;
    float rangoDisparo;
    int dispara;
    int direccionDisparo;
}; 

#endif /* JUGADOR_H */