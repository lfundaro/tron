#include "Parser.h"

Juego parse (char *archivo)
{
  Juego j;
  
  /* Comienzo Parsing de XML */
  TiXmlDocument doc(archivo);
  if (!doc.LoadFile()) return NULL;

  TiXmlHandle hDoc(&doc);
  TiXmlElement* pElem;
  TiXmlHandle hRoot(0);

  // Bloque: Proyecto
  {
    pElem = hDoc.FirstChildElement().Element();
    if (!pElem) return NULL;
    hRoot = TiXmlHandle(pElem);

    // Hijo Niveles 
    pElem = hRoot.FirstChild("niveles").Element();
    int numNiveles = atoi(pElem->GetText());
    j = Juego(numNiveles);
    
  }


  return j;
  
}
