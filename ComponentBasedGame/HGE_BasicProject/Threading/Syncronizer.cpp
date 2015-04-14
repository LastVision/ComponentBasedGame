#include "Syncronizer.h"


Syncronizer::Syncronizer()
{
	myUpdateDone = false;
	myRenderDone = false;
	myShutDown = false;
}
Syncronizer::~Syncronizer()
{

}

void Syncronizer::WaitForUpdate()
{
	while (myUpdateDone == false)
		;//(Niklas): This is supposed to be an empty whileloop

	myUpdateDone = false;
}
void Syncronizer::WaitForRender()
{
	while (myRenderDone == false)
		;//(Niklas): This is supposed to be an empty whileloop

	myRenderDone = false;
}


void Syncronizer::SetUpdateReady()
{
	myUpdateDone = true;
}
void Syncronizer::SetRenderReady()
{
	myRenderDone = true;
}

void Syncronizer::ShutDownThreads()
{
	myShutDown = true;
}

bool Syncronizer::GetShutDownStatus() const
{
	return myShutDown;
}