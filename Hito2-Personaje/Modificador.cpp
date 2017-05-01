/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Modificador.cpp
 * Author: borja
 * 
 * Created on 1 de mayo de 2017, 11:48
 */

#include "Modificador.h"
#include "Jugador.h"

Modificador::Modificador(int x, int y) {
    
    tamSprite = 32;
    radioSprite = tamSprite/2;
    escala=1.5;
    
    this->x= x;
    this->y = y;
    
    if (!texture.loadFromFile("resources/seta.png"))
    {
        std::cerr << "Error while loading texture modificador" << std::endl;
    }
    modificador.setTexture(texture);
    
    modificador.setOrigin(tamSprite/2,tamSprite/2);
    modificador.setTextureRect(sf:: IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite));
    
    
    modificador.setPosition(x, y);
    
    modificador.setScale(escala,escala);
    
}

Modificador::Modificador(const Modificador& orig) {
}

Modificador::~Modificador() {
}


void Modificador::Modificacion(Jugador* j){
    /*if(colision de hitbox){
        int num=rand()%2;
        switch (num){
                case '0': {;
                    int numero1=rand()%3;
                    j->CambiarAtaque(numero1);
                    break;
                }  
                case '1': {;
                    int numero2=rand()%3;
                    j->CambiarSpeed(numero2);  
                    break;
                }
        }
        //destruir Objeto
    //}*/
    pintar();
}

void Modificador::pintar(){
    Motor2D*motor2D = Motor2D::Instance();
    motor2D->pintarSprites(modificador);
    //motor2D->pintarHitbox(hitbox);
}