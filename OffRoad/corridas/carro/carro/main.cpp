#include "ODERequirements.h"
#include "ODEHeaders.h"
#include "ODETest.h"
#include "ODETestBasic.h"
#include "ODETestForces.h"
#include "ODETestCar.h"
#include "ODETestTrack.h"
#include <drawstuff/drawstuff.h>

using namespace ODE;

/// Cabeçalhos das funções
void command(int c);
void loop(int pause);
void start();



/// Variáveis
ODETest *test;



/// Função para tratar da criação de contactos nas colisões.
bool createContact(ODEContact& contact, ODEGeometry* geom1, ODEGeometry* geom2)
{
	return test->createContact(contact, geom1, geom2);
}



/// Responsável por tratar do input do teclado.
void command(int c)
{
	test->command(c);
}



/// Loop principal.
void loop(int pause)
{
	if (!pause)
	{
		test->loop();
		test->getWorld().step();
		test->draw();
	}
}



/// Inicia a visualização.
void start()
{
	dsFunctions fn;
	char *params[3];
	int param_count = 3;

	params[1] = new char[15];
	strcpy_s(params[1], 15, "-notex");
	params[2] = new char[15];
	strcpy_s(params[2], 15, "-noshadows");
	fn.version = DS_VERSION;
	fn.start = 0;
	fn.step = &loop;
	fn.command = &command;
	fn.stop = 0;
	fn.path_to_textures = "../../drawstuff/textures";
	dsSimulationLoop(param_count, params, 800, 600, &fn);
}



/// Main.
int main()
{
	/*************************************
	* Escolher o teste tirando comentários
	* (r para reset da simulação)
	*************************************/

	//test = new ODETestBasic(); // caixa e esfera
	//test = new ODETestForces(); // esfera e caixa ('w', 'a', 's', 'd' para andar com esfera)
	//test = new ODETestCar(); // carro ('a', 'z', ',', '.', ' ', 'x' - acelerar, travar, esq., dir., travão mão, reverse)
	test = new ODETestTrack();
	test->getWorld().setCreateContact(&createContact);
	test->start();
	start();

	return 0;
}
