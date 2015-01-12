//
//  loadMusic.h
//  Final
//
//  Created by Uriana on 13-12-4.
//  Copyright (c) 2013 Uriana. All rights reserved.
//

#ifndef __Final__loadMusic__
#define __Final__loadMusic__

#include <SimpleFMOD.h>

#include <queue>
 
using namespace SFMOD;

class loadMusic {
	private:
	//
	char* track;
	// FMOD
	SimpleFMOD fmod;
	Song song;

	// Normalization toggle and sample size
	bool enableNormalize;
	

	// Beat detection parameters
	float beatThresholdVolume;
	int beatThresholdBar;
	unsigned int beatSustain;
	unsigned int beatPostIgnore;

	int beatLastTick;
	int beatIgnoreLastTick;

	// List of how many ms ago the last beats were
	std::queue<int> beatTimes;
	unsigned int beatTrackCutoff;

	// When the music was last unpaused
	int musicStartTick;

public:
	loadMusic(char* track);
	void FrequencyAnalysis();

	virtual bool OnKeyCharacter(int, int, bool, bool);
	bool beat;
	float *specLeft, *specRight, *spec;
	int sampleSize;
	float bpmEstimate;
};
#endif /* defined(__Final__loadMusic__) */
