![UCN](images/60x60-ucn-negro.png)


# Informe Técnico 
## Curso: Estructura de datos
### Contador de personas

**Alumno:**

* Blaudio Vargas (Diseñador y programador)

## Resumen 

> Para la implemetnacion del taller se asistio a las ayudantias y se descargaron los datos entregados por el docente a cargo de la asigantura(Juan Bekios)
> Se diseccionaron los codigos entregados por el profesor, tras entender parte de su funcionamiente se procedio a implemntar el codigo
> Tras pruebas y errores se consiguio que el programa pudiera hacer seguimiento a las personas una moderadamente alta taza de exito.

## 1. Introducción

En este taller se precedera a crear un codigo el cual nos permitira realziar un seguimiento a la entrada y salida de las personas de un local
actualemente se trabajo con un set de 2500 imagenes, el obhetivo apernte de este taller es poder famarializarnos con el lenguaje de C++, ademas de poder
ser capazes de trabajar con los codigos dados por otras personas para poder demostrar nuestra fluidez con el lenguaje.

### 1.1 Descripción del problema

Nuestro objetivo es poder indentificar a las personas que entran y salen de nuestro recinto, ademas debemos ser capazes de trabajar con la informacionn que tenemos.

### 1.2 Objetivos 

**Objetivo General**

Nuestra mision en este taller es ser capaz de manejar los datos entregados por el detector de personas y ser capazes de clasificar los datos de estos.

**Objetivos específicos**

1. Detectar personas
2. Agregarlas a una lista
3. Actualziar la posicion de las personas atravez del tiempo
4. Realizar un registro de personas entrando y saliendo
5. Perfeccionar el codigo
6. Presentacion final Taller

### 1.3 Solución propuesta

------

## 2. Materiales y métodos

Se implementara el codigo de deteccion de personas, luego esta informacion es agregada a una lista cuidando de evitar datos repetidos, luego se ven cuantas personas entraron y salieron

### 2.1 Instalación

Se instalarion los codigos dados por el profesor:
"Detector.cpp": usando las librerias de "opencv2" se realzia la busqueda de las personas en las imagenes dadas.
"Detector.hpp":Se guarda la estructura de la deteccion
"Persona.cpp": Se crea y obtiene los datos de la persona
"Persona.hpp":Se guarda la estructura de las personas

### 2.2 Diseño 

struct NonPC// se guardan los datos de las personas, su punto de origen y si punto final en el espacio
struct Registro// lista enlazada donde se guardan los datos de las personas

1.addNPC// se agrega una nueva persona a a lista

2.searchNPC// busca si la persona ya existe, en caso positivo acutaliza sus datos, caso contrario la añade como una nueva persona

3.deteccion// se identifican a todas las personas de la imagen

4.LectorAutomatico// se cargan todas las imagenes de la direccion en el intervalo deseado

5.Clean list// Se eliminan los datos basura y se determina si la persona esta entrando o saliendo

6.Contador// Se cuentan las personas que entran o salen

7.Flujo// Se ce el flujo de personas que entran o salen por hora

8.LectorDirigido// se determina el intervalo de lectura de las imagenes

9.menu// se muestar las opciones del programa, cada vez que inica un nuevo registro se borra el registro actual

### 2.3 Implementación

El codigo se encuentra documentado con la funcion en [Release1.0](Release1.0.cpp)

## 3. Resultados obtenidos

Tras pulir el primer codigo se mejoro los tiempos de busqueda, y con la implementacion de una interfaz se facilito la prueba del codigo para la busqueda
de errores

## 4. Conclusiones

Se pueden apreciar los resultados del refinamiento del codigo, una vez estubo listo el primer codigo y se empezo a revisarlo se pudo ver los problemas del
codigo y con su correcion se pudo apreciar las ventajas del lenguaje C++, ya que se pudienron hacer maniovras que en otros lenguajes requieren mas 
lineas de codigo para resolver esos problemas

# Referecia
----


