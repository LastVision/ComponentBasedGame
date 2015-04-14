#pragma once

#include <atomic>

class Syncronizer
{
public:
	Syncronizer();
	~Syncronizer();

	void WaitForUpdate();
	void WaitForRender();
	

	void SetUpdateReady();
	void SetRenderReady();

	void ShutDownThreads();
	bool GetShutDownStatus() const;


private:
	volatile bool myUpdateDone;
	volatile bool myRenderDone;
	volatile bool myShutDown;
};