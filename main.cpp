#include <iostream>
#include <vector>
using namespace std;
//CHRISTIAN PAZMINO
//PROBLEMAS DE SATISFACCION DE RESTRICCIONES TIPO CRIPTOARITMETICA - INTELIGENCIA ARTIFICIAL
//RESTRICCIONES = {TODOS DIFERENTES, F!=0}

//-----------------------------------------------------VARIABLES------------------------------------
//Vector de tipo booleano donde almacena TRUE si al correspondiente index ya esta asignado un caracter, caso contrario FALSE
//Dominio del 0 al 9
bool dominio[10];



//Estructura donde se van a guardar el correpondiente numero y su caracter
struct tablaHash{
  char letra;
  int num;
};
//---------------------------------------------------FUNCIONES---------------------------------------------
//Funcion para comprobar si es una solucion correcta
//Recibe un puntero a la estructura tablaHas, un contador, la palabra1, la palabra2, y la palabra resultante
bool esSolucion(tablaHash* tabla, const int contador, string p1, string p2, string p3){
  //Variables a utilizar
  int auxNum1=0; //Variable auxiliar que contiene el valor numerico de la primera palabra
  int auxNum2=0;
  int auxNum3=0;
  int cifra=1;

  //Calcular el valor numerico de la primera palabra en la suma
  for(int i=p1.length()-1; i>=0; i--){ //Descendente en la primera palabra
      char auxChar = p1[i];
      int j;
      for(j=0; j< contador; j++){ //Ascendente en la tablaHash
        if(tabla[j].letra == auxChar ) //Si el caracter de la palabra coincide con la letra de la tablaHash a buscar salir del bucle for
          break;
      }
      auxNum1 += cifra*tabla[j].num; //Tomamos el valor de la tabla y lo vamos sumando a la variable auxiliar
      cifra *= 10; //Lo multiplicamos por 10
  }
  //Retomamos el valor de cifra en 1
  cifra =1;

  //Calcular el valor numerico de la segunda palabra en la suma
  for(int i=p2.length()-1; i>=0; i--){ //Descendente en la palabra
      char auxChar = p2[i];
      int j;
      for(j=0; j< contador; j++){ //Ascendente en la tablaHash
        if(tabla[j].letra == auxChar ) //Si el caracter de la palabra coincide con una letra de la tablaHash salir del bucle
          break;
      }
      auxNum2 += cifra*tabla[j].num; //Tomamos el valor de la tabla
      cifra *= 10; //Lo multiplicamos por 10
  }
  cifra=1;
  //Calcular el valor numerico de la tercera palabra en la suma
  char primCharP3= p3[0]; //Letra F;
  for(int i=p3.length()-1; i>=0;i--){ //Descendente en la palabra
      char auxChar = p3[i];
      int j;
      for(j=0; j< contador; j++){ //Ascendente en la tablaHash
        if(tabla[j].letra == auxChar ) //Si el caracter de la palabra coincide con una letra de la tablaHash salir del bucle
          break;
      }
      //RESTRICCION F != 0
      //Si es dl primer caracter de la tercera palabra //Letra F
      if(tabla[j].letra==primCharP3){
          //Si es igual a 0 su valor, no es solucion
        if(tabla[j].num == 0){
          return false;
        }
      }
      auxNum3 += cifra*tabla[j].num; //Tomamos el valor de la tabla
      cifra *= 10; //Lo multiplicamos por 10
  }

  //Comprobar si la suma numericamente es correcta
  if(auxNum1 + auxNum2 == auxNum3){
    return true;
  }
  return false; //Si es falso
}


//Funcion recursiva que expande las soluciones
bool recursividad(const int contador, tablaHash* tabla, int n, string p1, string p2, string p3){
  //Caso base
  if(n ==contador-1){
    //Comprobar si aun todos los numeros no han sido usados
    for(int i=0; i<10; i++){
        if(dominio[i] == false){ //Si aun no ha sido usado
          tabla[n].num = i; //Asignar al caracter correspondiente al indice n el valor i del dominio
        }
        //Comprobamos si es solucion
        if(esSolucion(tabla, contador, p1, p2, p3) == true){
            cout << "\n*********** \tSOLUCION ENCONTRADA\t ************** \n";
            //Imprimimos solución
            for(int j=0; j< contador; j++){
                cout <<" "<<tabla[j].letra<<" -> "<<tabla[j].num<<"\n";
            }
            return true;
        }
    }
    return false;
  }
  //Si no cumple con el caso base seguimos aplicando recursividad
  //Recorremos el dominio
  for(int i=0; i<10; i++){
    if(dominio[i]== false){
      //Asignamos al caracter correspondiente al indice n el valor i del dominio
      tabla[n].num = i;
      //Quitamos del dominio el valor numerico ya utilizado y asignado
      dominio[i]=true;
      //Utilizamos recursividad
      if(recursividad(contador, tabla, n+1, p1, p2, p3)){
          //Si se encontro solucion
          return true;
      }
      dominio[i] =false;
    }
  }
  return false;
}

bool resolverCriptoaritmetica(string p1, string p2, string p3){
  //Numero de caracteres unicos
  int numCharUni = 0;
  //Vecotor para almacenar el numero de veces de cada caracter
  vector<int> vecesChar(26);
  for(int i=0;i<p1.length(); i++){
    //De la tabla ASCII cada letra tiene su equivalencia decimal => A=65, B=66 => 'B'-'A' => 66-65=1
    //Se itera en la palabra1 para almacenar el valor hexadecimal de cada letra al interior del vector vecesChar
      ++vecesChar[p1[i] - 'A'];
  }
  for(int i=0; i<p2.length(); i++){
    //Se itera en la palabra2 para almacenar el valor hexadecimal de cada letra al interior del vector vecesChar
      ++vecesChar[p2[i] - 'A'];
  }

  for(int i=0; i<p3.length(); i++){
    //Se itera en la palabra2 para almacenar el valor hexadecimal de cada letra al interior del vector vecesChar
      ++vecesChar[p3[i] - 'A'];
  }

  //Contar el numero caracteres unicos
  for( int i=0; i<vecesChar.size(); i++){
    if(vecesChar[i]>0){
      numCharUni++;
    }
  }

  //Declaracion de un array de tablas
  tablaHash tablaArray[numCharUni];

  for(int i=0,j=0; i<26; i++){
    //Si es que existe el caracter unico
    if(vecesChar[i]>0){
      //Guardar todos los caracteres unicos en el array de tabla
      tablaArray[j].letra = char(i+'A');
      j++;
    }
  }

  return recursividad(numCharUni, tablaArray, 0, p1,p2,p3);
}



int main()
{
    for(int i=0; i<10;i++){
      dominio[i]=false;
    }
    string palabra1 ="TWO";
    string palabra2 ="TWO";
    string palabra3 ="FOUR";
    if(resolverCriptoaritmetica(palabra1, palabra2, palabra3)== true){
      cout<<"\n";
    }else{
      cout<<"***********\tNO EXISTE SOLUCION\t************************";
    }
    return 0;
}
