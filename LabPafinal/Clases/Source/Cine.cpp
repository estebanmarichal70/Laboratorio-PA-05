#include "../Headers/Cine.h"

using namespace std;

Cine::Cine(){
}

Cine::Cine(int nro, string dir){
  this->NroCine = nro;
  this->Dir = dir;
  salas = new OrderedDictionary();
  funciones = new OrderedDictionary();
  peliculas = new OrderedDictionary();
}

void Cine::agregarSalas(int nro, int cap){
    Integer* llave = new Integer(nro);
    if(!salas->member(llave)){
      Sala* s = new Sala(nro,cap);
      salas->add(llave,s);
    }
    else{
      delete llave;
      throw invalid_argument ("\nLa sala ya existe");
    }
}

void Cine::agregarFinanciera(string, float){
  // FALTA
}

ICollection* Cine::ListarSalas(){
  system("clear");
  IIterator* i = salas->getIterator();
  ICollection * res = new List();
  while(i->hasCurrent()){
    Sala* s = (Sala*) i->getCurrent();
    DtSala* sala = new DtSala(s->getNroSala(),s->getCapacidad());
    res->add(sala);
    i->next();
  }
  delete i;
  return res;
}

Sala* Cine::seleccionarSala(int NroSala){
  Integer* llave = new Integer(NroSala);
  if(!salas->member(llave)){
    delete llave;
    throw invalid_argument("\nEste cine no contiene este numero de sala");
  }
  Sala* sala = (Sala*) salas->find(llave);
  delete llave;
  return sala;
}

Funcion* Cine::seleccionarFuncion(int NroFuncion){
  Integer* llave = new Integer(NroFuncion);
  if(!funciones->member(llave)){
    delete llave;
    throw invalid_argument("\nEste cine no contiene esta funcion");
  }
  Funcion* funcion = (Funcion*) funciones->find(llave);
  delete llave;
  return funcion;
}

void Cine::agregarPelicula(string Titulo, Pelicula* peli){
  StringKey* llave = new StringKey(Titulo);
  if(!peliculas->member(llave)){
      peliculas->add(llave,peli);
  }
  else{
    delete llave;
    throw invalid_argument("\nEste cine ya contiene esta pelicula");
  }
}

void Cine::agregarFuncion(Pelicula* peli, int NroFuncion, int NroSala, DtFecha *fecha, DtHora *hora){
  Integer* llave = new Integer(NroFuncion);
  if(!funciones->find(llave)){
    Integer* llaveSala = new Integer(NroSala);
    Sala* sala = (Sala*) salas->find(llaveSala);
    IIterator* i = funciones->getIterator();
    while(i->hasCurrent()){
      Funcion* f = (Funcion*) i->getCurrent();
      if(f->VerificarSalaFecha(NroSala,fecha,hora))
      return;
      i->next();
    }
    delete i;
    DtFecha f = DtFecha(fecha->getDia(),fecha->getMes(),fecha->getAnio());
    DtHora h = DtHora(hora->getHora(),hora->getMinutos());
    Funcion* fun = new Funcion(NroFuncion,NroSala,f,h);
    peli->AsociarFuncion(fun);
    fun->AsociarSala(sala);
    funciones->add(llave,fun);
  }
  else{
    delete llave;
    cout << endl << "Ya existe una funcion con ese numero registrado" << endl;
  }
}

bool Cine::verificarPelicula(string Titulo){
  StringKey* llave = new StringKey(Titulo);
  if(!peliculas->member(llave)){
    delete llave;
    return true;
  }
  else{
    delete llave;
    return false;
  }
}

void Cine::EliminarPelicula(Pelicula* peli){

  StringKey* llave = new StringKey(peli->getTitulo());
  peliculas->remove(llave);
  delete peli;
}

int Cine::CantFunciones(){
  return funciones->getSize();
}

DtCine Cine::getCine() const{
  return DtCine (this->NroCine,this->Dir);
}

int Cine::getNroCine() const{
  return this->NroCine;
}

int Cine::getPrecioEntrada() const{
  return this->PrecioEntrada;
}

string Cine::getDir() const{
  return this->Dir;
}

void Cine::setNroCine(int nro){
  this->NroCine = nro;
}

void Cine::setDir(string dir){
  this->Dir = dir;
}

void Cine::setPrecioEntrada(int precio){
  this->PrecioEntrada = precio;
}

Cine::~Cine(){

}
