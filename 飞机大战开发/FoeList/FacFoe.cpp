#include "FacFoe.h"
#include"FoeBig.h"
#include"FoeMid.h"
#include"FoeSma.h"
#include"../Config/Config.h"
Foe* FacFoe::CreateFoe(const string& type)
{
    if (type == CREATE_FOESMA)
    {
        return new FoeSma;
    }
    else if (type == CREATE_FOEMID)
    {
        return new FoeMid;
    }
    else if (type == CREATE_FOEBIG)
    {
        return new FoeBig;
    }
    return nullptr;
}
