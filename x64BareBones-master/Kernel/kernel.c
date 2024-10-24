#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <idtLoader.h>

#define PROMPT_TEXT "User@Kernel:$> "

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;


static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}


int main()
{	
	load_idt();
	//hay que seguir esta logica pero probablemente del lado del userland
	//eliminar los while(1)
	//por ahora lo unico que hace es escribir y borrar
	int cursor[] ={0,0};
	while(1){
		print(PROMPT_TEXT, cursor);
		int *shiftFlag;
		*shiftFlag = 0;
		while(1){
			char c = getKeyPressed(shiftFlag);

			if(c == '\n')
			{
				delete(cursor);
				newline(cursor);
				print(PROMPT_TEXT, cursor);
			}
			else if(c==8){
				delete(cursor);		//borra la barra
				delete(cursor);		//borra el señalador
				drawChar('_',cursor);
			}
			else{
				delete(cursor);
				drawChar(c, cursor);
				drawChar('_',cursor);
			}
			
		}
	}

	//putPixel(0x00FF0000, 20, 20);
	//int cursor[] = {0,0};
	//print("User@Kernel:$~",cursor);
	//newline(cursor);
	//print("User@Kernel:$~",cursor);

	//while(1){
	//	  drawChar(getKeyPressed(), cursor[0], cursor[1]);
	//	  cursor[0] += 8;
	//}
	return 0;
}
