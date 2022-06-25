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
4.LectorAutomatico// se cargan todas las imagenes de la direccion dada en este caso son un total de 2500 imagenes
5.Analizis// se analizan los datos del regeistro y nos da las personas que entran y salen y eliminan los datos invalidos/basura

### 2.3 Implementación

El codigo se encuentra documentado con la funcion de cada uno de ellos

## 3. Resultados obtenidos

El codigo nos otorga un resultado satisfactorio, aunque el tiempo que toma para cargar las imagenes presento ser un contratiempo, pero 
no es nada que con lo que no se puediera trabajar

## 4. Conclusiones

Se pueden ver las raizes de los lenguajes anteriormente vistos en el lenguaje c++, debido a que el lenguaje c++ trabaja a un nivel de maquina inferior
nos da mas libertades creativas para solucionar problemas, del mismo modo requiere una mayor presicion en el codigo, ya que la probabilidad de cometer
erroes durante la programacion es moderadamente alta comparada con otros lenguajes, fuera de esto a demostrado ser un lenguaje muy versatil y que posee
un gran potencial para la programacion.

# Referecia
----


