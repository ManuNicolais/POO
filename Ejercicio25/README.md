#Ejercicio 25

Construir un nuevo proyecto que tenga un Login independiente, es decir, que no dependa de otra clase GUI.
El Login tenga un QLabel que funciona como botón que sea para registrar un nuevo usuario.
Cuando se presiona el QLabel que funciona como botón, se abrirá una ventana para dar de alta un usuario.
Usar SQLite con AdminDB como singleton.
Cuando un usuario válido ingresa correctamente se mostrará otra ventana que visualizará todos los usuarios cargados en la base.
Para la visualización de los usuarios se puede usar QTreeWidget. Agregar la funcionalidad para que en esta misma ventana se puedan editar los campos como si fuera una planilla tipo excel.
Seguir las recomendaciones que se comentaron durante el dictado de clases para construir las clases.

#modo de uso
-registrar un usuario antes de comenzar. (ya existe un usuario en la base de datos "database.sqlite" llamado "admin" con clave "1234")
-en el registro se deben completar todos los cambios
-luego de ingresar un usuario se pueden ver los usuarios cargados en la ventana "Usuarios"

#cargar datos desde terminal del sistema
1-elegir direccion del archivo.sqlite
  cd "direccion de destino"
  
2- nombre del archivo
  sqlite3 "nombre".sqlite

3- crear base de datos llamada "usuarios"
  create table usuarios (
    id integer primary key,
    usuario varchar(30),
    clave varchar(30),
    nombre varchar(50),
    apellido varchar(50),
    mail varchar(50)
  );
  
4- insertar un usuario a la base de datos
  insert into usuarios (usuario, clave,   nombre, apellido, mail) 
  values ('admin', '1234', 'administrador', 'cuenta', 'admin@gmail.com');
  
5-  verificar usuarios cargados
  select * from usuarios;
  
6- salir de la base de datos
  .exit


