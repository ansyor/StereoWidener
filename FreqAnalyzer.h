#ifndef __FREQANALYZER_H__
#define __FREQANALYZER_H__


#include "juce_amalgamated.h"


// forward declarations
class MasterAndCommander;


class FreqAnalyzer  : public Component
{
public:
    FreqAnalyzer (MasterAndCommander *m);
    ~FreqAnalyzer();

    void paint (Graphics& g);
    void resized();

    void init(int gx, int gy, int ox, int oy,
              int nSlider, float fSlider, float fRate,
              int nData, float fData);

    void setLevel(float *data);
    //void setImpulse(float *data);

    juce_UseDebuggingNewOperator

private:
    MasterAndCommander *master;
    int gridX;
    int gridY;
    int offsetX;
    int offsetY;
    int numSlider;
    float freqSlider;
    float freqRate;
    int numLevel;
    float freqLevel;
    float *level;
    float fs;

    // (prevent copy constructor and operator= being generated..)
    FreqAnalyzer (const FreqPlot&);
    const FreqAnalyzer& operator= (const FreqPlot&);
};


#endif   // __FREQPLOT_H__