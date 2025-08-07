#include "ProfilerSystem.h"

void Profiler::push(float FrameTime)
{
	int diff = FrameTimeQueue.size() - Capacity;
	if (diff > 0)
	{
		for (int i = 0; i <= diff; i++)
		{
			FrameTimeQueue.erase(FrameTimeQueue.begin());
		}
	}

	FrameTimeQueue.push_back(FrameTime);
}

float Profiler::AverageTime()
{
	float average = 0;
	for (int i = 0; i < FrameTimeQueue.size(); i++)
		average += FrameTimeQueue[i];

	return average / FrameTimeQueue.size();
}

float Profiler::CalculateFPSValue(float averageFrameTime)//FPS Value
{
	return 1000 / averageFrameTime;
}

ProfilerSystem::ProfilerSystem()
{
	frameData = new FrameMap();
	thisFramesFrameData = new FrameMap();
	lastFramesFrameData = new FrameMap();
}

ProfilerSystem::~ProfilerSystem()
{
}

void ProfilerSystem::StartFrame()
{
	currentFrame++;
	thisFramesTotalTime = 0;
}

void ProfilerSystem::StoreSample(const char* name, int64_t elapsedTime)// store of the frames for profiler
{
	SampleData* sample = new SampleData();
	sample->frameReference = currentFrame;
	sample->frameTime = elapsedTime;

	thisFramesTotalTime += elapsedTime;

	(*frameData)[name].push_back(sample);
	(*thisFramesFrameData)[name].push_back(sample);
}

void ProfilerSystem::EndFrame()
{
	totalFrameTimes.push_back(thisFramesTotalTime);
	lastFramesFrameData = thisFramesFrameData;
	thisFramesFrameData = new FrameMap();
}
