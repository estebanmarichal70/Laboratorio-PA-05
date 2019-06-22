#include "../Headers/Pelicula.h"

using namespace std;

Pelicula::Pelicula(){
}

Pelicula::Pelicula(string titulo, string poster, string sinopsis, float puntaje){
  this->Titulo = titulo;
  this->Poster = poster;
  this->Sinopsis = sinopsis;
  this->Puntaje = puntaje;
  funciones =new OrderedDictionary();
  comentarios =new OrderedDictionary();
  opiniones =new OrderedDictionary();
}

void Pelicula::ListarComentarios(ICollectible * obj){
  IIterator* i = comentarios->getIterator();
  if(i->hasCurrent()){
    cout << "==========LISTA COMENTARIOS=========="<<endl;
    while(i->hasCurrent()){
      Comenta* com = (Comenta*) i->getCurrent();
      cout << com->getUsers()<< ": " << "   "<< com->getComentario() << endl;
      cout <<"------------------------------------------------------" << endl;
      StringKey* llave = new StringKey (com->getComentario());
      Comenta* c =(Comenta*) comentarios->find(llave);
      c->ListarComentariosResp(c);
      delete llave;
      i->next();
    }
    delete i;
  }
  else{
    delete i;
    cout << "La pelicula no tiene comentarios aun" << endl;
  }
}

void Pelicula::ListarFunciones(){
  system("clear");
  IIterator* i = funciones->getIterator();
  cout << "=================LISTA FUNCIONES================"<<endl;
  if(!funciones->isEmpty()){
      while(i->hasCurrent()){
        Funcion* fun = (Funcion*) i->getCurrent();
        DtFecha fechaF = fun->getFecha();
        int dia,mes,anio;
        time_t fecha = time(NULL);
        struct tm *tiempo = localtime(&fecha);
        dia = tiempo->tm_mday;
        mes = tiempo->tm_mon + 1;
        anio= tiempo->tm_year + 1900;
        DtFecha fechaActual = DtFecha(dia,mes,anio);
        if(fechaActual<fechaF){
          DtHora horaF = fun->getHorario();
          cout << "Numero de Funcion: " << fun->getNroFuncion() << endl;
          cout << "Numero de Sala: " << fun->getNroSala() << endl;
          cout << "Fecha de la Funcion: " << fechaF.getDia() << "/" << fechaF.getMes() << "/" << fechaF.getAnio() << endl;
          if(horaF.getMinutos()==0)
          cout << "Hora de la Funcion: " << horaF.getHora() << ":" << "00" << endl;
          else
          cout << "Hora de la Funcion: " << horaF.getHora() << ":" << horaF.getMinutos() << endl;
          cout << "==============================================="<<endl;
        }
        i->next();
      }
      delete i;
  }
  else{
    delete i;
    throw invalid_argument("No hay funciones para esta pelicula");
  }
}

void Pelicula::agregarComentario(ICollectible * obj, string nick){
  string com;
  cout <<"Elija un comentario si lo desea, de lo contrario presione 'N' " << endl;
  cin >> com;
  //StringKey* llave = new StringKey(com);
  if(com == "N" || com == "n"){
    cout << "Ingrese un nuevo comentario" << endl;
    cin >> com;
    StringKey* key = new StringKey(com);
    Comenta* c = new Comenta(com,nick);
    comentarios->add(key,c);
    cout << "Comentario agregado" << endl;
  }
  else {
    Comenta* co;
    co = BuscarComentario(obj,com);
    //if(comentarios->member(llave)){
    //Comenta* c = (Comenta*) comentarios->find(llave);
    cout <<"HOLA" << endl;
    co->agregarRespuesta(co,nick);
    /*}
    else{
      cout << "Comentario incorrecto" << endl;
    }*/
  }
}

void Pelicula::AsociarFuncion(Funcion* funcion){
  Integer* llave = new Integer(funcion->getNroFuncion());
  funciones->add(llave,funcion);
}

Comenta* Pelicula::BuscarComentario(ICollectible * objP, string com){
  StringKey* llave = new StringKey(com);
  if (comentarios->member(llave)){
    Comenta* c = (Comenta*) comentarios->find(llave);
    delete llave;
    return c;
  }
  else{
    if(!comentarios->isEmpty()){
      IIterator* i = comentarios->getIterator();
      if(i->hasCurrent()){
        while(i->hasCurrent()){
          Comenta* come = (Comenta*) i->getCurrent();
          StringKey* llave = new StringKey (come->getComentario());
          Comenta* c =(Comenta*) comentarios->find(llave);
          c->BuscarRespuestas(c,com);
          delete llave;
          i->next();
          }
          delete i;
      }
    }
    else{
      delete llave;
      throw invalid_argument("Comentario no existe");
    }
  }
}

float Pelicula::agregarPuntaje(ICollectible * objP, string user){
  IIterator* i= opiniones->getIterator();
  bool aux = false;
  string auxi;
  if(i->hasCurrent()){
        cout << "==========LISTA PUNTAJES=========="<<endl;
        while(i->hasCurrent()){
          Opinion* o = (Opinion*) i->getCurrent();
          cout <<"Usuario: "<< o->getUser() <<"/   Puntaje: " << o->getPuntaje() << endl;
          cout <<"-----------------" << endl;
          if(o->getUser() == user){
            // REMPLAZA PUNTAJE SI YA HABIA PUNTUADO;
            aux = true;
            float p;
            cout << "Ingrese el puntaje para remplazar" << endl;
            cin >> p;
            o->setPuntaje(p);
            delete i;
            return p;
          }
          i->next();
        }
        if(aux == false){
          // PUNTUACION NUEVA SI YA HAY PUNTAJES
          float p;
          cout << "Ingrese el nuevo puntaje" << endl;
          cin >> p;
          Opinion* op = new Opinion(p,user);
          StringKey* llave = new StringKey(user);
          opiniones->add(llave,op);
          delete i;
          return p;
        }
   }
   else{
    // PUNTUACION NUEVA
    cout << "La pelicula no contiene ningun puntaje aun" << endl;
    float p;
    cout << "Ingrese el nuevo puntaje" << endl;
    cin >> p;
    StringKey* llave = new StringKey(user);
    Opinion* op = new Opinion(p,user);
    opiniones->add(llave,op);
    delete i;
    return p;
    }
  return 0;
}

void Pelicula::MostrarComentariosPuntajes(ICollectible* obj, string t, float p, int cant){
  system("clear");
  cout << t << endl;
  cout << "Puntaje promedio: "<< p <<  " (" << cant << " usuarios)"<< endl;
  cout << "=================================" << endl;
  ListarComentarios(obj);
  cout << "=================================" << endl;
  cout << " PUNTAJES " << endl;
  IIterator* i= opiniones->getIterator();
  if(i->hasCurrent()){
      while(i->hasCurrent()){
      Opinion* o = (Opinion*) i->getCurrent();
      cout << o->getUser()<<":" << o->getPuntaje() << endl;
      cout <<"--------------------------------------" << endl;
      i->next();
      }
      delete i;
    }
}

DtPelicula Pelicula::getPelicula() const{
   return DtPelicula(this->Titulo, this->Poster, this->Sinopsis, this->Puntaje);
}

string Pelicula::getTitulo() const{
  return this->Titulo;
}

string Pelicula::getPoster() const{
  return this->Poster;
}

string Pelicula::getSinopsis() const{
  return this->Sinopsis;
}

float Pelicula::getPuntaje() const{
  return this->Puntaje;
}

void Pelicula::setTitulo(string titulo){
  this->Titulo = titulo;
}

void Pelicula::setPoster(string poster){
  this->Poster = poster;
}

void Pelicula::setSinopsis(string sinopsis){
  this->Sinopsis = sinopsis;
}

void Pelicula::setPuntaje(float puntaje){
  this->Puntaje = puntaje;
}

Pelicula::~Pelicula(){
  // ELIMINAR PELICULA FUNCION
}
