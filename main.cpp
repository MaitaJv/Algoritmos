#include <iostream>
#include <cstring>

using namespace std;

// Struct
struct Estudiante{
    char mail[50];
    char password[15];
    int creditos;
};

struct Beneficio{
    char nombre[50];
    int valor;
};

// DECLARACION DE FUNCIONES

//  Modulos
void gestorDeEstudiantes();
void gestorDeBeneficios();
void consumidorDeBeneficios();

//  Funciones de Gestor de Estudiantes

int ValidacionDelEmail(Estudiante&);
void AsignarCreditos(Estudiante&);
void GuardarDatosArchivo(Estudiante);

//  Funciones de Gestor de Beneficios

int interface();
int cantBeneficios(FILE*);

void listar();
void modificar();
void agregar();
void eliminar();

Beneficio dameBeneficio();

//  Funciones de Consumidor de Beneficios

bool InicioSesion(Estudiante&);
void listarCB(Estudiante&);
void ConsumirBeneficio(Estudiante&);
void listarEstudiantes();

int main() {
    int modulo;

    cout << "Seleccione el modulo que desea ejecutar:" << endl;
    cout << "1 - Gestor de Beneficios" << endl;
    cout << "2 - Gestor de Estudiantes" << endl;
    cout << "3 - Consumidor de Beneficios" << endl;
    cin >> modulo;

    switch (modulo){
    case 1:
        gestorDeBeneficios();
        break;
    case 2:
        gestorDeEstudiantes();
        break;
    case 3:
        consumidorDeBeneficios();
        break;
    }


    return 0;
}

// DEFINICION DE FUNCINOES

//  Modulos
void gestorDeBeneficios(){
    int op = interface();
    int exit;

    switch (op){
        case 1:
            listar();
            break;
        case 2:
            modificar();
            break;
        case 3:
            agregar();
            break;
        case 4:
            eliminar();
            break;
    }

    cout << "Desea realizar otra funcion?" << endl;
    cout << "   0 para realizar otra funcion" << endl;
    cout << "   <OtraTecla> para terminar el programa" << endl;
    cin >> exit;

    if (exit == 0) main();
}

void gestorDeEstudiantes(){
    Estudiante estu;
    int exit;
    char mail[50];

    cout << "Ingrese su email y contraseña para obtener los créditos: ";
    cin >> estu.mail;
    cin >> estu.password;
    cout << "array ingresado: " << estu.mail << endl;

    int vali = ValidacionDelEmail(estu);
    // si la validacio de realiza correctamente vali = 0, sino vali = 1

    if (vali == 0){
        AsignarCreditos(estu);
        GuardarDatosArchivo(estu);

        cout << "Desea realizar otra funcion?" << endl;
        cout << "   0 para realizar otra funcion" << endl;
        cout << "   <OtraTecla> para terminar el programa" << endl;
        cin >> exit;
        
        if (exit == 0) main();
    }else{
        cout << "El mail no es válido" << endl;

        cout << "Desea realizar otra funcion?" << endl;
        cout << "   0 para realizar otra funcion" << endl;
        cout << "   <OtraTecla> para terminar el programa" << endl;
        cin >> exit;

        if (exit == 0) main();
    }
}

void consumidorDeBeneficios(){
    int listarEstu, exit;
    cout << "listar Estudiantes? 1" << endl;
    cin >> listarEstu;
    if (listarEstu == 1) listarEstudiantes();
    
    Estudiante alumno;
    bool sesion = InicioSesion(alumno);

    if (sesion == true){
        listarCB(alumno);
        ConsumirBeneficio(alumno);
    }else main();
    cout << "Desea realizar otra funcion?" << endl;
    cout << "   0 para realizar otra funcion" << endl;
    cout << "   <OtraTecla> para terminar el programa" << endl;
    cin >> exit;

    if (exit == 0) main();
}

//  Funcinoes del Gestor de Estudiantes

int ValidacionDelEmail(Estudiante& estudiante){
    char cond[17] = {'@','f', 'r', 'b', 'a', '.', 'u', 't', 'n', '.','e', 'd', 'u', '.', 'a', 'r'};

    for (int i = 0; i < 10; i++){

        cout << estudiante.mail[i] << endl;

        if (estudiante.mail[i] == '@'){
            int count = 0;
            int pos = i;

            for (int w = pos; w < i + 16; w++){
                if (estudiante.mail[w] == cond[count]){
                    count++;
                }else{
                    cout << "No es mail institucional" << endl;
                    return 1;
                    count++;
                }
            }
        }
    }

    // Recorrer archivo para verificar que no este el uso el mail ingresado
    //strcmp()
    
    FILE* archivo = fopen("estudiantes.dat","rb");
    if (archivo != NULL) {
        Estudiante estu;
        while (fread(&estu, sizeof(Estudiante),1,archivo)==1) {
            if (strcmp(estudiante.mail, estu.mail) == 0) {
                cout << "Error el mail ya esta en uso: " << endl;
                cout << "   mail: " << estu.mail << endl;
                cout << "   password: " << estu.password << endl;
                cout << "   creditos: " << estu.creditos << endl;
                cout << "--------------------------" << endl;
                return 1;
            }
            cout << "   mail: " << estu.mail << endl;
            cout << "   password: " << estu.password << endl;
            cout << "   creditos: " << estu.creditos << endl;
            cout << "--------------------------" << endl;
        }
    }
    fclose(archivo);
    return 0;
}

void AsignarCreditos(Estudiante& estu){ // void es el tipo de funcion (en este caso no retorna ningun valor), (Estudiante estu) es la variable que recibira la cual se llama estu y es de tipo Estudiante
    cout << "Usted fue registrado con éxito" << endl;
    cout << "1000 créditos fueron cargados a su cuenta"<<endl;
    estu.creditos = 1000;
}

void GuardarDatosArchivo(Estudiante estu){
    FILE* archivo = fopen("estudiantes.dat","ab");

    fwrite(&estu, sizeof (Estudiante),1,archivo);
    fclose(archivo);    

}

//  Funciones del Gestor de Beneficios

int interface(){
    int op;
    
    cout << "Que acción quiere realizar?" << endl;

    cout << "1 - Listar los beneficios disponibles" << endl;
    cout << "2 - Modificar un beneficio" << endl;
    cout << "3 - Agregar más beneficios" << endl;
    cout << "4 - Eliminar beneficios" << endl;

    cin >> op;

    if ((op != 1) && (op != 2) && (op != 3) && (op != 4)){
        int op2;
        cout << "Opción invalida. 1 para volver a elejir la actividad; (otro simbolo) para cerrar el programa" << endl;
        cin >> op2;
        if (op2 = 1) interface();
    }

    return op;
}

int cantBeneficios(){
    FILE* archivo = fopen("beneficios.dat", "rb+");
    Beneficio bene;
    int cant = 0;
    while (fread(&bene, sizeof(Beneficio), 1, archivo) == 1){
        cant++;
    }
    fclose(archivo);
    return cant;
}

Beneficio dameBeneficio(){
    Beneficio data;
    cout << "Ingrese los datos del benefios" << endl;
    cout << "   - nombre" << endl;
    cout << "   - valor" << endl;
    cin >> data.nombre >> data.valor;

    return data;
}

void listar(){
    FILE* archivo = fopen("beneficios.dat", "rb");
    Beneficio data;
    if (archivo != NULL){
        while ((fread(&data, sizeof(Beneficio), 1, archivo)) == 1){     // Se recorre el archivo y se muestra en terminal
            cout << "Beneficio encontrado" << endl;
            cout << "Nombre: " << data.nombre << endl;
            cout << "Valor: " << data.valor << endl;
        }
        fclose(archivo);
    }else{
        cout << "El archivo no se pudo abrir" << endl;
    }
}

void modificar(){
    FILE* archivo = fopen("beneficios.dat", "rb+");
    char nombre[50];

    cout << "Ingrese el nombre del beneficio que desea editar" << endl;
    cin >> nombre;

    if (archivo != NULL){
        Beneficio data;
        while ((fread(&data, sizeof(Beneficio), 1, archivo)) == 1){
            if (strcmp(data.nombre, nombre) == 0){                      // Se recorre el archivo y si se pregunta si hay un nombre igual al recibido
                int seleccion;

                cout << "Beneficio encontrado, selecciones el campo que desea actualizar" << endl;
                cout << "   1 - nombre" << endl;
                cout << "   2 - valor" << endl;
                cout << "   3 - ambos" << endl;

                cin >> seleccion;                                       // De ser asi se pregunta cuales valores se veran modificados

                switch (seleccion){
                    case 1:

                        cout << "Ingrese el nuevo nombre" << endl;
                        cin >> data.nombre;

                        fseek(archivo, -sizeof(Beneficio), SEEK_CUR);   // Se posiciona en el beneficio actual para sobre escribir la nueva version del mismo
                        fwrite(&data, sizeof(Beneficio), 1, archivo);
                        fclose(archivo);

                        break;
                    case 2:

                        cout << "Ingrese el nuevo valor" << endl;
                        cin >> data.valor;

                        fseek(archivo, -sizeof(Beneficio), SEEK_CUR);   // Se posiciona en el beneficio actual para sobre escribir la nueva version del mismo
                        fwrite(&data, sizeof(Beneficio), 1, archivo);
                        fclose(archivo);

                        break;
                    case 3:
                        cout << "Ingrese el nuevo nombre" << endl;
                        cin >> data.nombre;

                        cout << "Ingrese el nuevo valor" << endl;
                        cin >> data.valor;

                        fseek(archivo, -sizeof(Beneficio), SEEK_CUR);   // Se posiciona en el beneficio actual para sobre escribir la nueva version del mismo
                        fwrite(&data, sizeof(Beneficio), 1, archivo);
                        fclose(archivo);

                        break;
                }
            }
        }
    }
}

void agregar(){
    FILE* archivo = fopen("beneficios.dat", "ab");                      // "ab" agrega datos unicamente al final del archivo
    Beneficio beneficio;
    beneficio = dameBeneficio();

    if(archivo != NULL){
        fwrite(&beneficio, sizeof(Beneficio), 1, archivo);              // al ser ab fwrite agrega al final, asique unicamente se utiliza como si se creara un archivo
        fclose(archivo);
        cout << "El beneficio se agrego correctamente" << endl;
    }else{
        fwrite(&beneficio, sizeof(Beneficio), 1, archivo);
        fclose(archivo);
        cout << "El archivo se creo correctamente" << endl;
    }
}

void eliminar(){                    // En esta funcion se utilizara 2 veces el fopen, una para leer "rb+" y otra para remplazar "wb" 
    int cantBene = cantBeneficios();
    int pos = 0;
    char nombreBuscado[50];

    FILE* archivo = fopen("beneficios.dat", "rb+");

    Beneficio beneficios[cantBene - 1];                                 //se crea un array donde se guardaran todos los beneficios menos el que se quiera eliminar
    Beneficio bene;

    cout << "Ingrese el nombre del beneficio que desea eliminar" << endl;
    cin >> nombreBuscado;

    if (archivo != NULL){
        
        while((fread(&bene, sizeof(Beneficio), 1, archivo)) == 1){

            if (strcmp(bene.nombre, nombreBuscado) != 0){               // se lee el archivo y se guardan todos los beneficios en el array excepto el ingresado a eliminar

                cout << "Beneficio del archivo actual " << pos << ":" << endl;
                cout << "   nombre: " << bene.nombre << endl;
                cout << "   valor: " << bene.valor << endl;
                cout << "--------------------------" << endl;
                
                beneficios[pos] = bene;
                
                cout << "Datos guardados del Beneficio: " << pos << endl;
                cout << "   Nombre: " << beneficios[pos].nombre << endl;
                cout << "   Valor: " << beneficios[pos].valor << endl;
                cout << "--------------------------" << endl;

                pos++;
            }
        }

        for (int i = 0; i < pos; i++){                                  // se recorre el array unicamente para visualizar que es lo que subira
            if (i == 0) cout << "Recorriendo el array de beneficio que remplazara al actual" << endl;
            
            cout << "Beneficio " << i << ":" << endl;
            cout << "   nombre: " << beneficios[i].nombre << endl;
            cout << "   valor: " << beneficios[i].valor << endl;
            cout << "--------------------------" << endl;
        }

        fclose(archivo);
    }else{
        cout << "El archivo no se pudo abrir" << endl;
    }

    FILE* archivoNuevo = fopen("beneficios.dat", "wb");

    if (archivoNuevo != NULL){
        fwrite(beneficios, sizeof(Beneficio), cantBene - 1, archivo);   // se remplaza el archivo por uno nuevo sin el que se queria eliminar
    }

    fclose(archivoNuevo);
}

//  Funciones del Consumidor de Beneficios

void listarEstudiantes(){
    FILE* archivo = fopen("estudiantes.dat","rb");
    if (archivo != NULL) {
        Estudiante estu;
        while (fread(&estu, sizeof(Estudiante), 1, archivo)==1) {
            cout << "Estudiante encontrado" << endl;
            cout << "Mail: " << estu.mail << endl;
            cout << "Creditos: " << estu.creditos << endl;
        }
        fclose(archivo);
    }
}

bool InicioSesion(Estudiante& alumno) {
    Estudiante estudiante, estu;
    bool ok;

    cout << "Ingrese su email institucional y su contraseña para ver los beneficios." << endl;
    cin >> estudiante.mail;
    cin >> estudiante.password; 

    FILE* archivo = fopen("estudiantes.dat","rb");
    if (archivo != NULL) {

        while (fread(&estu, sizeof(Estudiante),1,archivo)==1) {
            if (strcmp(estudiante.mail, estu.mail) == 0 && strcmp(estudiante.password, estu.password) == 0){
                cout << estudiante.mail << " y " << estu.mail << " son iguales" << endl;
                cout << estudiante.password << " y " << estu.password << " son iguales" << endl;
                ok = true;
                alumno = estu;
                fclose(archivo);
                return ok;
            }
            else{
                cout << estudiante.mail << " y " << estu.mail << " no son iguales" << endl;
                cout << estudiante.password << " y " << estu.password << " no son iguales" << endl;
                ok = false;
                cout << "Mail/contraseña incorrecto o no registrado" << endl;
            } 
        }
        fclose(archivo);
        return ok;
    }
}

void listarCB(Estudiante& alumno){
    FILE* archivo = fopen("beneficios.dat", "rb");
    Beneficio data;
    if (archivo != NULL){
        while ((fread(&data, sizeof(Beneficio), 1, archivo)) == 1){     // Se recorre el archivo y se muestra en terminal

            if (data.valor <= alumno.creditos){
                cout << "Beneficio encontrado" << endl;
                cout << "Nombre: " << data.nombre << endl;
                cout << "Valor: " << data.valor << endl;
            }
        }
        fclose(archivo);
    }else{
        cout << "El archivo no se pudo abrir" << endl;
    }
}

void ConsumirBeneficio (Estudiante& alumno){
    char nombre[50];
    Beneficio data;
    cout << "Elija el beneficio que desea consumir:" << endl; 
    cin >> nombre;

    FILE* archivo = fopen("beneficios.dat", "rb");
    if (archivo != NULL){
        while ((fread(&data, sizeof(Beneficio), 1, archivo)) == 1){
            if (strcmp(nombre, data.nombre) == 0){
                alumno.creditos = alumno.creditos - data.valor;
                cout << "El beneficio ha sido consumido éxitosamente" << endl;
            }
        }
    }
    fclose(archivo);

    FILE* archivoEstudiante = fopen("estudiantes.dat", "rb+");
    Estudiante estu;
    while(fread(&estu, sizeof(Estudiante), 1, archivoEstudiante) == 1){
        if (strcmp(alumno.mail, estu.mail) == 0){
            cout << "Datos del estudiante actualizados" << endl;
            cout << "Mail: " << alumno.mail << endl;
            cout << "creditos: " << alumno.creditos << endl;
            fseek(archivoEstudiante, -sizeof(Estudiante), SEEK_CUR);
            fwrite(&alumno, sizeof(Estudiante), 1, archivoEstudiante);
            break;
        }
    }
    fclose(archivoEstudiante);
}