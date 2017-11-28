
#include "Disk.h"
#include "FS.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
int main(int argc, char const *argv[])
{
	const char * path = "archivo.bin";
	Disk *disk = new Disk(path);
	disk->createDisk(20*4096);
	FS *fs = new FS(disk);
	fs->format();
	fs->mkdir("/root");
	fs->mkdir("/root/usb");
	fs->mkdir("/root/usb2");
	fs->createFile("/root/archivo.png");
	fs->ls("/root");
	cout << "size file /root/archivo.png " <<fs->getSizeFile("/root/archivo.png")<<endl;
	char *buffer = "Frente al único espejo de su casa, roto y antiguo, Jacinto se acicala. Usa el mismo peine viejo que todas las mañanas contribuye a darle a su rostro el aspecto que necesita para poder trabajar. Con un poco de agua y jabón se atreve a eliminar la pereza de una fría mañana en Lima y con sus dedos decora su piel. Con pintura blanca cubre la totalidad de su cara y una luminosa esfera roja, como cereza de torta, culmina su transformación. Como todas las mañanas se convierte en Fideíto para desafiar a un público siempre distinto.Renato lleva puesto un elegante terno de una de las mejores marcas del medio. Frente al amplio espejo de su sala que refleja el movimiento del agua en su piscina, se acomoda la corbata. Lleva unos gemelos dorados que ajusta con un estilo peculiar y culmina abrochando su fino reloj de pulsera. Mira la hora. Se despide de su esposa, quien desde el fondo de un pasadizo le corresponde y aprovecha en recordarle que debe comprar los pasajes para las próximas vacaciones familiares. Él no responde y se va presuroso.Jacinto corre la cortina de un ambiente de su humilde casa, se acerca a una tarima que sirve de cama y despierta a su hijo. Ya es hora, campeón –le dice. Es un niño de doce años que de inmediato se despierta. Lo carga y con esmerado cuidado lo sienta en una silla de ruedas. Lo lleva al baño y sobre sus piernas deja un balde con agua para que se lave la cara, le da un beso en la frente y se despide. En una pequeña mesa hay una tacita con anís recién servido y la mitad de un pan. Ya está en el baño, se está lavando, te lo dejo, mamá, debo irme –le dice Jacinto a una señora anciana que come la otra mitad del pan–. Anda con Dios – responde ella. Jacinto sale. En el barrio lo saludan como Fideíto; él siempre devuelve el gesto con su colorida sonrisa.Renato va apurado en su auto. Esa mañana se le hizo tarde viendo el noticiero. Es doctor de una prestigiosa clínica y maneja renegando por el insufrible tráfico.Jacinto sube a un micro e inicia su rutina. Cuenta algunos chistes, pocos le hacen caso. Pocos ríen, pocos lo escuchan. Luego ofrece unos caramelos y sin nunca obviar su sonrisa, agradece y abandona el vehículo para subir de inmediato a otro.En una intersección transitada, el semáforo está a punto de marcar rojo. Renato sabe que si no aprovecha la luz ámbar, demorará mucho más de lo previsto y decide acelerar. Logra cruzar con temeridad ya cuando el semáforo lo impedía.Fideíto baja del otro bus aprovechando que los vehículos se han detenido y divisa otro a mitad de la calle con muchos pasajeros. Se apresura y cruza sin reparo. En ese momento es embestido ferozmente por un vehículo que desafió la luz roja.Renato sangra de una herida en la frente. Ha bajado de su auto y ahora está delante de un hombre que ya no podrá sonreír más. Mira la irónica agonía de un payaso que no respira. Insiste en reanimarlo usando las técnicas que conoce pero sabe que es inútil. Es paradójico haber matado a un payaso. Lo queda mirando porque pudiendo salvar vidas ha eliminado una. La sangre de Jacinto tiñe de rojo su blanco rostro.Renato piensa en sus vacaciones y solloza. Bajo el cielo gris de Lima hay un médico vencido frente a un infeliz payaso mientras a lo lejos se oye venir un patrullero.";
	fs->writeFile("/root/archivo.png", 2500, buffer, strlen(buffer));
	char *buffer2=(char*)malloc(strlen(buffer));
	fs->readFile("/root/archivo.png", 2500, buffer2, strlen(buffer));
	cout<<buffer2<<endl;
	cout << "size file /root/archivo.png " << fs->getSizeFile("/root/archivo.png") << endl;
	fs->printfBlockAllocate();
	fs->deleteFile("/root/archivo.png");
	fs->ls("/root");
	fs->printfBlockAllocate();
	fs->createFile("/root/archivo.png");
	fs->ls("/root");
	fs->printfBlockAllocate();
	fs->rm("/root");
	fs->ls("/root");
	fs->printfBlockAllocate();
	disk->close();
	delete fs;
	delete disk;
	
	return 0;
}