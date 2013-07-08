#include "stdafx.h"
#include "SMUManager.h"


SMUPool<HumanSMU>*    g_pHumanSMUPool = NULL;;
#ifdef __LINUX__
template <> BOOL    SMUManager<HumanSMU>::HeartBeat(UINT uTime/* =0 */)
{
    return TRUE;
}
#else
BOOL    SMUManager<HumanSMU>::HeartBeat(UINT uTime/* =0 */)
{
    return TRUE;
}
#endif



