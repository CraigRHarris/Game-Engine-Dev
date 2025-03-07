#pragma once
#include <vector>
#include <SDL.h>
#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

struct SampleData
{
	int64_t frameTime;
	int frameReference;
};
typedef std::map<const char*, std::vector<SampleData*>> FrameMap;

class ProfilerSystem
{
public:
	static ProfilerSystem& Instance()
	{
		static ProfilerSystem INSTANCE;
		return INSTANCE;
	}

	/**
	Getting frame data for last and this frame into a map.
	*/
	ProfilerSystem();
	~ProfilerSystem();

	void StartFrame();
	/**
	store sample of frames over time. 
	*/
	void StoreSample(const char* name, int64_t elapsedTime);
	void EndFrame();

	FrameMap& GetFrameData() const
	{
		return *frameData;
	}

	int GetCurrentFrame()
	{
		return currentFrame;
	}

	FrameMap& GetLastFrameData() const
	{
		return *lastFramesFrameData;
	}

	std::vector<float>& GetFrameTimes()
	{
		return totalFrameTimes;
	}

private:
	int currentFrame;
	FrameMap* frameData;
	std::vector<float> totalFrameTimes;
	float thisFramesTotalTime = 0;
	FrameMap* thisFramesFrameData;
	FrameMap* lastFramesFrameData;
};

struct Profile
{
	Profile(const char* name)
	{
		_name = name;
		startTime = std::clock();
	}

	~Profile()
	{
		std::clock_t endTime = std::clock();
		std::clock_t elapsedTime = endTime - startTime;

		ProfilerSystem::Instance().StoreSample(_name, (1000 * elapsedTime) / CLOCKS_PER_SEC);
	}

	const char* _name;
	std::clock_t startTime;
};

struct Profiler
{
public:

	/**
	Push frame time queue to go though frames
	*/
	void push(float FrameTime);
	/**
	Average frame time
	*/
	float AverageTime();

	float CalculateFPSValue(float averageFrameTime);

	int Capacity = 240;
	std::vector<float> FrameTimeQueue;
};
#define PROFILE(name) Profile p(name)

