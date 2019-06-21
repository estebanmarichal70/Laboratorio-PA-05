#include "../Headers/Comenta.h"

using namespace std;

Comenta::Comenta(){
}

Comenta::Comenta(string comentario, string user){
  this->comentario = comentario;
  this->users = user;
  comentariosResp = new OrderedDictionary();
  }

string Comenta::getComentario() const{
  return this->comentario;
}

string Comenta::getUsers() const{
  return this->users;
}

void Comenta::setComentario(string comentario){
  this->comentario = comentario;
}

void Comenta::ListarComentariosResp(ICollectible * obj){
  IIterator* i = comentariosResp->getIterator();
  if(i->hasCurrent()){
    cout << "          ========== RESPUESTAS =========="<<endl;
    while(i->hasCurrent()){
      Comenta* com = (Comenta*) i->getCurrent();
      cout <<"          "<< com->getUsers()<< ":" << "   "<< com->getComentario() << endl;
      cout <<"          -----------------" << endl;
      cout <<"          ================================"<<endl;
      i->next();
    }
    delete i;
  }
}

void Comenta::agregarRespuesta(ICollectible* obj,string nick){
  string com;
  cout << "Ingrese la respuesta al comentario seleccionado" << endl;
  cin >> com;
  StringKey* llave = new StringKey(com);
  Comenta* c = new Comenta(com,nick);
  comentariosResp->add(llave,c);
  cout << "Respuesta agregada" << endl;
}

Comenta* Comenta::BuscarRespuestas(ICollectible* objC, string com){
  StringKey* llave = new StringKey(com);
  if (comentariosResp->member(llave)){
    Comenta* c = (Comenta*) comentariosResp->find(llave);
    return c;
  }
  else{
    if(!comentariosResp->isEmpty()){
      IIterator* i = comentariosResp->getIterator();
      if(i->hasCurrent()){
        while(i->hasCurrent()){
          Comenta* come = (Comenta*) i->getCurrent();
          StringKey* llave = new StringKey (come->getComentario());
          Comenta* c =(Comenta*) comentariosResp->find(llave);
          c->BuscarRespuestas(c,com);
          i->next();
        }
        delete i;
      }
    }
  }
}

Comenta::~Comenta(){
  // ELIMINAR Comenta
}
