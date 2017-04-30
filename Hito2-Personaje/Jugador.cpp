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

using namespace std;
Jugador::Jugador(int x, int y) {
    
    // variable tamaño sprites personaje
    tamSprite = 32;
    radioSprite = tamSprite/2;
   
    ajustePierna = 12;
    // para cambiar el tamaño de los sprites
    escala = 1.5;
     
    // variable para animar los FRAMES de piernas
    contadorPasos = 0;
    this->x= x;
    this->y = y;
    
    // ATRIBUTOS
    SPRITE_SPEED = 2;
    
    // ::: Creamos y cargamos las texturas :::
    
    if (!texture.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error while loading texture ISAAC" << std::endl;
    }
    
    //SPRITE JUGADOR 
    cabeza.setTexture(texture);
    piernas.setTexture(texture);
    
    //Le pongo el centroide donde corresponde
    cabeza.setOrigin(tamSprite/2,tamSprite/2);
    piernas.setOrigin(tamSprite/2,tamSprite/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf:: IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite));
    piernas.setTextureRect(sf:: IntRect (0*tamSprite, 1*tamSprite, tamSprite, tamSprite));
    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(x, y);
    piernas.setPosition(x, y+radioSprite);
    // tamaño de los esprites
    cabeza.setScale(escala,escala);
    piernas.setScale(escala,escala);
    
    // avisadores de tecla pulsada MOV Jugador
    upFlag = false;
    downFlag = false;
    leftFlag = false;
    rightFlag = false;
    
    crearbala();
}

void Jugador::crearbala(){
    // velocidad de bala
    velx = 0;
    vely = 0;
    
    // distancia a la dispara 
    rangoDisparo = 1.5;  
    // centinela para conocer direccion de disparo
    dispara = 0;
    // control direccion de disparo
    direccionDisparo=Decha;
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

void Jugador::animacioncaminar(sf::Clock relojSprite){
    if(relojSprite.getElapsedTime().asSeconds()> .1 && (upFlag==true || downFlag==true || leftFlag==true || rightFlag==true)){
        contadorPasos++;
        if(contadorPasos == 8) {contadorPasos = 0;}       
        // control de la posicion 
        if(upFlag == true){
            piernas.setTextureRect(sf::IntRect(contadorPasos*tamSprite,1*tamSprite, tamSprite, tamSprite));
            piernas.setScale(-escala,escala);
        }
        if(downFlag == true){
            piernas.setTextureRect(sf::IntRect(contadorPasos*tamSprite,1*tamSprite, tamSprite, tamSprite));
            piernas.setScale(escala,escala);
        }
        if(leftFlag==true){
            piernas.setTextureRect(sf::IntRect(contadorPasos*tamSprite,2*tamSprite, tamSprite, tamSprite));
            piernas.setScale(-escala,escala);
        }
        if(rightFlag==true){
            piernas.setTextureRect(sf::IntRect(contadorPasos*tamSprite,2*tamSprite, tamSprite, tamSprite));
            piernas.setScale(escala,escala);
        }
        relojSprite.restart();
    }
}

void Jugador::actualizarSprite(){
     if(upFlag == true){
        cabeza.setTextureRect(sf::IntRect(5*tamSprite, 0*tamSprite, tamSprite, tamSprite));
    }
    else if(downFlag == true){
        cabeza.setTextureRect(sf::IntRect(1*tamSprite, 0*tamSprite, tamSprite, tamSprite));
    }
    else if(leftFlag==true){
        cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite));
        //Reflejo vertical
        cabeza.setScale(-escala,escala);
    }
    else if(rightFlag==true){
        cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite));
        //Escala por defecto
        cabeza.setScale(escala,escala);                 
    }
    // posicion del personaje NEUTRA
    else{
        cabeza.setTextureRect(sf::IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite)); 
    }
}

void Jugador::pintar(){
    Motor2D*motor2D = Motor2D::Instance();
    motor2D->pintarSprites(piernas);
    motor2D->pintarSprites(cabeza);
}

void Jugador::mover(sf::Clock relojSprite){
   
    actualizarSprite ();
    animacioncaminar (relojSprite);

    if(upFlag==false && downFlag==false && leftFlag==false && rightFlag==false){
        cabeza.setTextureRect(sf::IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite));
        piernas.setTextureRect(sf::IntRect(0*tamSprite, 1*tamSprite, tamSprite, tamSprite));
        //Escala por defecto
        cabeza.setScale(escala,escala);             
    }
    
    if (leftFlag) x-=SPRITE_SPEED;
    if (rightFlag) x+=SPRITE_SPEED;
    if (upFlag) y-=SPRITE_SPEED;
    if (downFlag) y+=SPRITE_SPEED;
    

// Fijamos las posiciones de los sprites
    cabeza.setPosition(x,y);
    piernas.setPosition(x,y+(ajustePierna)*escala); // valor para ajustar cuerpo a cabeza
    
}

void Jugador::disparar(sf::Clock reloj){
 
    if(dispara !=0 ){
            int velx = 0;
            int vely = 0;
            // variables para disparo diagonal 
            if (leftFlag) velx = -3;
            else if(rightFlag) velx = 3;
            if (upFlag) vely = -3;
            else if(downFlag) vely = 3;
            
            // comprobamos direccion de disparo y cargamos posicion de textura
            switch (direccionDisparo){
                case Arriba:
                    cabeza.setTextureRect(sf::IntRect(5*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                    // separacion entre bolas en el disparo
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        // creamos una nueva bala y la metemos en el vector
                        balas.push_back(new Bala(x,y-30,velx,-3,rangoDisparo));
                        reloj.restart(); 
                    }
                break;
                
                case Abajo:
                    cabeza.setTextureRect(sf::IntRect(1*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y+50,velx,3,rangoDisparo));
                        reloj.restart();
                    }
                break;
                case Decha:
                    cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite)); 
                    cabeza.setScale(escala,escala);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x+35,y,3,vely,rangoDisparo));
                        reloj.restart();
                    }
                break;
                case Izda:
                    cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                    //Reflejo vertical
                    cabeza.setScale(-escala,escala);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x-35,y,-3,vely,rangoDisparo));
                        reloj.restart();
                    }
                break;
            }
        }
    
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
    // pintamos las balas
    Motor2D*motor2D = Motor2D::Instance();
        for(int i = 0 ; i<balas.size(); i++){
            if(balas.at(i)){
                motor2D->pintarSprites(balas.at(i)->getSprite());
                
            }
            
        }
    
    pintar();
    
    }

void Jugador::setDirDisparo(int e){
    if (e==0) direccionDisparo = Arriba;
    else if (e==1) direccionDisparo = Abajo;
    else if (e==2) direccionDisparo = Izda;
    else if (e==3) direccionDisparo = Decha;
    dispara++;
}

void Jugador::decrementarBala(){dispara--;}
void Jugador::setFlagA(bool f){leftFlag = f;}
void Jugador::setFlagW(bool f){upFlag = f;}
void Jugador::setFlagD(bool f){rightFlag = f;}
void Jugador::setFlagS(bool f){downFlag = f;}