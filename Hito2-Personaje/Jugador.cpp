/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.cpp
 * Author: juli
 * 
 * Created on 27 de abril de 2017, 19:28
 */

#include "Jugador.h"

Jugador::Jugador() {
    
    // variable tamaño sprites personaje
    tamCabeza = 32;
    radioCabeza = tamCabeza/2;
    tamPiernas = 32;
    radioPiernas = tamPiernas/2; 
    ajustePierna = 12;
    // para cambiar el tamaño de los sprites
    escalCab = 1;
    escalPie = 1;
     
    // variable para animar los FRAMES de piernas
    contadorPasos = 0;
    
    
    // ATRIBUTOS
    SPRITE_SPEED = 2;
    
    // ::: Creamos y cargamos las texturas :::
    
    
    if (!texture.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error while loading texture ISAAC" << std::endl;
        return -1;
    }
    
    //SPRITE JUGADOR   
    sf::Sprite cabeza(texture);
    sf::Sprite piernas(texture);
    
    //Le pongo el centroide donde corresponde
    cabeza.setOrigin(tamCabeza/2,tamCabeza/2);
    piernas.setOrigin(tamPiernas/2,tamPiernas/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf:: IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    piernas.setTextureRect(sf:: IntRect (0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(anchoPantalla/2, altoPantalla/2);
    piernas.setPosition(anchoPantalla/2, altoPantalla/2+radioPiernas);
    // tamaño de los esprites
    cabeza.setScale(escalCab,escalCab);
    piernas.setScale(escalPie,escalPie);
    
    x = window.getSize().x/2;
    y = window.getSize().y/2;
    
    // avisadores de tecla pulsada MOV Jugador
    upFlag = false;
    downFlag = false;
    leftFlag = false;
    rightFlag = false;
    
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}


void Jugador::mover(sf::Keyboard tecla){
    
  
      // Actalizamos coordenadas
        if (leftFlag) x-=SPRITE_SPEED;
        if (rightFlag) x+=SPRITE_SPEED;
        if (upFlag) y-=SPRITE_SPEED;
        if (downFlag) y+=SPRITE_SPEED;
    
    // posicion de las texturas Personaje segun movimiento
    if(upFlag == true){
        cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    }
    else if(downFlag == true){
        cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    }
    else if(leftFlag==true){
        cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
        //Reflejo vertical
        cabeza.setScale(-escalCab,escalCab);
    }
    else if(rightFlag==true){
        cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
        //Escala por defecto
        cabeza.setScale(escalCab,escalCab);                 
    }
    // posicion del personaje NEUTRA
    else{
        cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza)); 
    }
}

// animacion de los PASOS del PERSONAJE
if(relojSprite.getElapsedTime().asSeconds()> .1 && (upFlag==true || downFlag==true 
        || leftFlag==true || rightFlag==true)){
    contadorPasos++;
    if(contadorPasos == 8){
        contadorPasos = 0;
    }
    // control de la posicion 
    if(upFlag == true){
        piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
        piernas.setScale(-escalPie,escalPie);
    }
    if(downFlag == true){
        piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
        piernas.setScale(escalPie,escalPie);
    }
    if(leftFlag==true){
        piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
        piernas.setScale(-escalPie,escalPie);
    }
    if(rightFlag==true){
        piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
        piernas.setScale(escalPie,escalPie);
    }

    relojSprite.restart();
}
    
    // Si pulsamos una tecla
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        // Para cerrar la ventana con ESC
        case  sf::Keyboard::Escape : window.close(); break;

        // MOV del personaje
        case sf::Keyboard::W : // ARRIBA     
            upFlag=true; 
            break;

        case sf::Keyboard::S:// ABAJO
            downFlag=true;
            break;
        break;

        case sf::Keyboard::A: // IZDA   
            leftFlag=true; 
        break;

        case sf::Keyboard::D: // DERECHA
            rightFlag=true;                  
        break;
        }
    }
    
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        // Liberamos teclas
        case sf::Keyboard::W : // ARRIBA     
            upFlag=false;break;                    
        case sf::Keyboard::S:  // ABAJO  
            downFlag=false; break;
        case sf::Keyboard::A:  // IZDA  
            leftFlag=false; break;
        case sf::Keyboard::D:  // DERECHA
            rightFlag=false; break;
        }
    }
    

// posicion NEUTRA PERSONAJE
if(upFlag==false && downFlag==false && leftFlag==false && rightFlag==false){
    cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
    //Escala por defecto
    cabeza.setScale(escalCab,escalCab);             
}
if (leftFlag) x-=SPRITE_SPEED;
if (rightFlag) x+=SPRITE_SPEED;
if (upFlag) y-=SPRITE_SPEED;
if (downFlag) y+=SPRITE_SPEED;


// Fijamos las posiciones de los sprites
cabeza.setPosition(x,y);
piernas.setPosition(x,y+(ajustePierna)*escalPie); // valor para ajustar cuerpo a cabeza


}
