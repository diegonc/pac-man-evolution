#ifndef POSICIONGRAF_H_INCLUDED
#define POSICIONGRAF_H_INCLUDED

//Clase que representa la posicion grafica y angulo de un objetoVisual
class Posicion_Graf{
public:
  float x;
  float y;
private:
  int AngActual;
  int AngAGirar;


public:
  Posicion_Graf(){
    x=0;
    y=0;
    AngActual=0;
    AngAGirar=0;
  }

  void setAnguloActual(int AnguloActual){
      while (AnguloActual<0)
        AnguloActual+=360;

      AngActual=AnguloActual;
  }

  int getAnguloAGirar(){
    return abs(AngAGirar%360);
  }

  int getAnguloActual(){
    return abs(AngActual%360);
  }

  void girar(){
    if (getAnguloActual()!=getAnguloAGirar()){
        if ((AngActual>=0) && (AngAGirar >=0)){
                if (AngActual<AngAGirar){
                    AngActual+=1;
                }else{
                    AngActual-=1;
                }
        }
    }
  }
};

#endif // POSICIONGRAF_H_INCLUDED
