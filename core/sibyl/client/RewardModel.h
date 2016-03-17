#ifndef SIBYL_CLIENT_REWARDMODEL_H_
#define SIBYL_CLIENT_REWARDMODEL_H_

#include <vector>
#include <map>
#include <fstream>
#include <cstring>

#include "../Security.h"
#include "Portfolio.h"
#include "Model.h"
#include "Reward.h"

namespace sibyl
{

class RewardModel : public Model
{
public:  
    void SetParams(double timeConst_, double rhoWeight_, double rhoInit_);

    // for ref
    void SetRefPath(CSTR &path);
    void GetRefData();
    
    // for rnn 
    std::vector<Reward>& GetRewardVec(); // returns vec with correct size (no content)
    void                 SetRewardVec(const std::vector<Reward> &vec); // put in here after filling content

    // virtuals from Model; to be called by Trader
    void  SetStateLogPaths(CSTR &state, CSTR &log);
    CSTR& BuildMsgOut     ();
    
    RewardModel() : timeConst(0.0), // for initialization check
                    rhoWeight(0.0), rho(0.0), isFirstTick(true) {}
private:
    double timeConst;
    double rhoWeight;
    double rho;

    std::map<STR, Reward> rewards;
    void InitCodes(); // create rewards entries with codes from first msg
    
    // for ref
    STR pathData;
    std::map<STR, std::unique_ptr<FILE, int(*)(FILE*)>> mfRef; // for binary log of G values

    // for rnn
    std::vector<Reward> vecRewards;

    // for logging
    STR pathState;
    STR pathLog;
    
    bool isFirstTick;
    void InitGLogs   ();
    void WriteGLogs  (); // writes only if  log  path was set
    void WritePosGCnt(); // writes only if state path was set
    
    std::ofstream logMsgOut; // req msg
    std::ofstream logVecIn;  // G
    std::map<STR, std::unique_ptr<FILE, int(*)(FILE*)>> mfLogRef; // for binary log of G values
    
    int nMsgCurTick;
    char bufLine[1 << 10];
    bool CatReq(const char *pcMsgType, CSTR &code, INT price, INT quant, INT modprice = 0)
    {
        if (modprice > 0) sprintf(bufLine, "%s %s %d %d %d\n", pcMsgType, code.c_str(), price, quant, modprice);
        else              sprintf(bufLine, "%s %s %d %d\n"   , pcMsgType, code.c_str(), price, quant);
        msg.append(bufLine);
        if (kReqNPerTick == ++nMsgCurTick)
            return true;
        return false;        
    }
    STR msg;
};

}

#endif /* SIBYL_CLIENT_REWARDMODEL_H_ */