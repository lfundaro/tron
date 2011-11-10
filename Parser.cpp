#include "Parser.h"

Punto parsePunto(TiXmlHandle rootPunto)
{
  // Punto x
  TiXmlElement *pElem = rootPunto.FirstChild("x").Element();
  int x = atoi(pElem->GetText());
  // Punto y
  pElem = rootPunto.FirstChild("y").Element();
  int y = atoi(pElem->GetText());
  Punto pto(x,y);
  return pto;
}

Trayectoria parseTrayectoria(TiXmlHandle rootTrayectoria)
{
  // velocidad 
  TiXmlElement *pElem = rootTrayectoria.FirstChild("velocidad").Element();
  double vel = atof(pElem->GetText());
  // número de puntos
  pElem = rootTrayectoria.FirstChild("puntos").Element();
  int pts = atoi(pElem->GetText());
  // Procesar lista de puntos
  vector<Punto> listPts;
  int i = 0;
  for(TiXmlElement *nodoPunto = rootTrayectoria.FirstChild("punto").Element();
      i < pts; nodoPunto = nodoPunto->NextSiblingElement())
    {
      TiXmlHandle rootPunto(nodoPunto);
      Punto pt = parsePunto(rootPunto);
      listPts.push_back(pt);
      i++;
    }
  Trayectoria tr(vel,pts,listPts);
  return tr;
}

Jugador parseJugador(TiXmlHandle rootJugador) 
{
  // disparo
  TiXmlElement *pElem = rootJugador.FirstChild("disparo").Element();
  double disp = atof(pElem->GetText());
  TiXmlHandle rootTrayectoria(rootJugador.FirstChild("trayectoria").Element());
  Trayectoria tr = parseTrayectoria(rootTrayectoria);
  Jugador jug(disp,tr);
  return jug;
}

Jugador parseContrincante(TiXmlHandle rootContrincante) 
{
  return parseJugador(rootContrincante);
}

vector<Objeto> parseObjetos(TiXmlHandle rootObjetos) 
{
  // cantidad 
  TiXmlElement *pElem = rootObjetos.FirstChild("cantidad").Element();
   int cant = atoi(pElem->GetText());
  // objetos
  vector<Objeto> listObjetos;
  int i = 0;
  for(TiXmlElement *nodoObjeto = rootObjetos.FirstChild("objeto").Element();
      i < cant; nodoObjeto = nodoObjeto->NextSiblingElement())
    {
      TiXmlHandle rootObjeto(nodoObjeto);
      if ((pElem = rootObjeto.FirstChild("maya").Element()) != NULL)
        {
          TiXmlHandle rootMaya(pElem);
          // archivo
          pElem = rootMaya.FirstChild("archivo").Element();
          char *archivo = strdup(pElem->GetText());
          // x 
          pElem = rootMaya.FirstChild("x").Element();
          int x = atoi(pElem->GetText());
          // y 
          pElem = rootMaya.FirstChild("y").Element();
          int y = atoi(pElem->GetText());
          Punto pto(x,y);
          enum tipoObjeto tipo = MAYA;
          ObjetoMaya objMaya(tipo,archivo,pto);
          listObjetos.push_back(objMaya);
        }
      else if // Objeto es cubo ?
        ((pElem = rootObjeto.FirstChild("cubo").Element()) != NULL) 
        {
          pElem = rootObjeto.FirstChild("cubo").Element();
          TiXmlHandle rootCubo(pElem);
          // x
          pElem = rootCubo.FirstChild("x").Element();
          int x = atoi(pElem->GetText());
          // y 
          pElem = rootCubo.FirstChild("y").Element();
          int y = atoi(pElem->GetText());
          Punto pto(x,y);
          // tamano
          pElem = rootCubo.FirstChild("tamano").Element();
          int tam = atoi(pElem->GetText());
          enum tipoObjeto tipo = CUBO;
          ObjetoCubo objCubo(tipo,tam,pto);
          listObjetos.push_back(objCubo);
        }
      else  // Objeto es esfera
        {
          pElem = rootObjeto.FirstChild("esfera").Element();
          TiXmlHandle rootEsfera(pElem);
          // x 
          pElem = rootEsfera.FirstChild("x").Element();
          int x = atoi(pElem->GetText());
          // Y 
          pElem = rootEsfera.FirstChild("y").Element();
          int y = atoi(pElem->GetText());
          Punto pto(x,y);
          // radio
          pElem = rootEsfera.FirstChild("radio").Element();
          double rad = atof(pElem->GetText());
          enum tipoObjeto tipo = ESFERA;
          ObjetoEsfera objEsf(tipo,pto,rad);
          listObjetos.push_back(objEsf);
        }
      i++;
    }
  return listObjetos;
}

Nivel parseNivel(TiXmlHandle rootNivel)
{
  // Parsear Nivel
  // Identificador 
  TiXmlElement *pElem = rootNivel.FirstChild("id").Element();
  int ident = atoi(pElem->GetText());
  // Tiempo de juego
  pElem = rootNivel.FirstChild("tiempo_juego").Element();
  int tmpJuego = atoi(pElem->GetText());
  // Jugador 
  pElem = rootNivel.FirstChild("jugador").Element();
  TiXmlHandle rootJugador(pElem);
  Jugador jug = parseJugador(rootJugador);
  // Número de contrincantes
  pElem = rootNivel.FirstChild("contrincantes").Element();
  int numContr = atoi(pElem->GetText());
  // Iterar sobre los contrincantes 
  vector<Jugador> listaContr;
  int i = 0;
  for(TiXmlElement *nodoContrincantes = 
        rootNivel.FirstChild("contrincante").Element();
      i < numContr; nodoContrincantes = nodoContrincantes->NextSiblingElement())
    {
      TiXmlHandle rootContrincante(nodoContrincantes);
      Jugador ctr = parseContrincante(rootContrincante);
      listaContr.push_back(ctr);
      i++;
    }
  // Objetos
  // Cantidad de objetos
  pElem = rootNivel.FirstChild("objetos").FirstChild("cantidad").Element();
  int cantObjetos = atoi(pElem->GetText());
  // Lista de objetos
  pElem = rootNivel.FirstChild("objetos").Element();
  TiXmlHandle rootObjetos(pElem);
  vector<Objeto> listaObjetos = parseObjetos(rootObjetos);
  // Crear Nivel 
  Nivel nv(ident,tmpJuego,jug,numContr,listaContr,cantObjetos,listaObjetos);
  return nv;
}

Juego parse (char *archivo)
{
  Juego j;
  /* Comienzo Parsing de XML */
  TiXmlDocument doc(archivo);
  if (!doc.LoadFile()) return j;

  TiXmlHandle hDoc(&doc);
  TiXmlElement* pElem;
  TiXmlHandle hRoot(0);

  pElem = hDoc.FirstChildElement().Element();
  hRoot = TiXmlHandle(pElem);

  // Bloque: Proyecto
  pElem = hRoot.FirstChild("niveles").Element();
  // Número de niveles
  int numNiveles = atoi(pElem->GetText());
  // Iterar sobre lista de niveles
  vector<Nivel> lstNivel;
  for(TiXmlElement *nodoNivel = hRoot.FirstChild("nivel").Element();
      nodoNivel; nodoNivel = nodoNivel->NextSiblingElement()) 
    {
      TiXmlHandle rootNivel(nodoNivel);
      Nivel niv = parseNivel(rootNivel);
      lstNivel.push_back(niv);
    }
  j = Juego(numNiveles, lstNivel);
  return j;
  
}
